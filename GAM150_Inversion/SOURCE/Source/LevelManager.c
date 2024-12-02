

//------------------------------------------------------------------------------
//
// File Name:	LevelManager.c
// Author(s):	Ian Gaither ian.gaither
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "AEEngine.h"
#include "LevelManager.h"
#include "Collision.h"
#include "Gfx.h"
#include "LevelManager.h"
#include "Vector2D.h"
#include "CheckpointFlag.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

// Add levels without file extension and increase the level count (ex. "Level1")
const char * LevelNames[] = { "LevelO", "Level3", "Level8", "yesaa1"/*, "Level2"*/ };
const unsigned numLevels = 4;

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct LevelData 
{
	char * LevelName;						// name of the level
	char * LevelRedImageName;				// image displayed when red is transparent
	char * LevelBlueImageName;				// image displayed when blue is transparent
	FILE * LevelCollisionImage;				// pointer to image with collision data
	BitmapHeader LevelCollisionImageHeader; // header info for collision image
	PixelData ** LevelCollisionPixelData;   // pixel data for collision detection
	AEVec2 startLocation;					// pixel for start location
	AEVec2 endLocation;						// pixel for end location
	float checkPointLocations[8];			// check1originx,y,check1,endx,y,check2...
	float * boundLines;
	int numLines;
	LightningData * lightningData;

}LevelData;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

LevelData * Levels;

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

unsigned currentLevelIndex = 0;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void BuildLevelStrings(LevelData * levelData, unsigned levelNum);
static void ReadLevelPixelData(LevelData * levelData);
static void FindStartPoint(LevelData * levelData);
static void FindEndPoint(LevelData * levelData);
static void FindCheckPoints(LevelData * levelData);
static void FindBoundLines(LevelData * levelData);
static void FreeLevelData();
static void BuildLevelData();
static void getLine(LevelData * levelData, float startX, float startY, Vector2D * lineEnd);
static void GenerateLightningData(LevelData * levelData);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Initialize the ...
void LevelManagerInit(PlayerPtr player)
{
	Levels = malloc(sizeof(LevelData) * numLevels);
	BuildLevelData();
	PlayerSetXcoordinate(player, Levels[currentLevelIndex].startLocation.x);
	PlayerSetYcoordinate(player, Levels[currentLevelIndex].startLocation.y);
	CollisionInit();
	GfxInit();
	currentLevelIndex = 0;
}

void LevelManagerChangeLevel(PlayerPtr player, unsigned newIndex)
{
	currentLevelIndex = newIndex;
	GfxChangeLevel();
	CollisionInit();
	PlayerSetXcoordinate(player, Levels[currentLevelIndex].startLocation.x);
	PlayerSetYcoordinate(player, Levels[currentLevelIndex].startLocation.y);
	PlayerSetCurrentTextureOffset(player, 2);
	SetFlag1Unclear();
	SetFlag2Unclear();
	SetPlayertriggered1stcheckpoint(player, 0);
	SetPlayertriggered2ndcheckpoint(player, 0);
}

const char * GetBlueImageName()
{
	return Levels[currentLevelIndex].LevelBlueImageName;
}


const char * GetRedImageName()
{
	return Levels[currentLevelIndex].LevelRedImageName;
}

const PixelData *** GetCurrentLevelCollisionData()
{
	return &Levels[currentLevelIndex].LevelCollisionPixelData;
}

const BitmapHeader * GetCurrentLevelImageHeader()
{
	return &Levels[currentLevelIndex].LevelCollisionImageHeader;
}

unsigned GetCurrentLevelIndex()
{
	return currentLevelIndex;
}

const AEVec2* GetStartPoint()
{
	return &Levels[currentLevelIndex].startLocation;
}

const AEVec2* GetEndPoint()
{
	return &Levels[currentLevelIndex].endLocation;
}

float * GetCheckpoints()
{
	return Levels[currentLevelIndex].checkPointLocations;
}

float * GetLineBounds()
{
	return Levels[currentLevelIndex].boundLines;
}

int GetLevelNumLines()
{
	return Levels[currentLevelIndex].numLines;
}

LightningData * GetLightningData()
{
	return Levels[currentLevelIndex].lightningData;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

static void BuildLevelData()
{
	unsigned i;

	//
	Levels = malloc(sizeof(LevelData) * numLevels);

	for (i = 0; i < numLevels; ++i)
	{
		BuildLevelStrings(&Levels[i], i);
		ReadLevelPixelData(&Levels[i]);
		FindStartPoint(&Levels[i]);
		FindEndPoint(&Levels[i]);
		FindCheckPoints(&Levels[i]);
		FindBoundLines(&Levels[i]);
	}
}

static void BuildLevelStrings(LevelData * levelData, unsigned levelNum)
{
	//6 for folder name, 7 for levelname, 4 for file extension, 1 for null term.
	levelData->LevelName = malloc(18);

	//6 for folder name, 7 for levelname, 4 for "blue", 4 for file extension, 1 for null term.
	levelData->LevelBlueImageName = malloc(22);

	//7 for folder name, 7 for levelname, 3 for "red", 4 for file extension, 1 for null term.
	levelData->LevelRedImageName = malloc(21);

	strcpy_s(levelData->LevelName, 19, "Levels/");
	strcpy_s(levelData->LevelBlueImageName, 23, "Levels/");
	strcpy_s(levelData->LevelRedImageName, 22, "Levels/");

	//add level name
	strcat_s(levelData->LevelName, 19, LevelNames[levelNum]);
	strcat_s(levelData->LevelBlueImageName, 23, LevelNames[levelNum]);
	strcat_s(levelData->LevelRedImageName, 22, LevelNames[levelNum]);

	//add color
	strcat_s(levelData->LevelBlueImageName, 23, "Blue");
	strcat_s(levelData->LevelRedImageName, 22, "Red");

	//add file extension
	strcat_s(levelData->LevelName, 19, ".bmp");
	strcat_s(levelData->LevelBlueImageName, 23, ".bmp");
	strcat_s(levelData->LevelRedImageName, 22, ".bmp");
}

static void ReadLevelPixelData(LevelData * levelData)
{
	fopen_s(&levelData->LevelCollisionImage, levelData->LevelName, "rb");
	if (levelData->LevelCollisionImage)
	{
		int i, j;

		//Read image file header
		fread(&levelData->LevelCollisionImageHeader, sizeof(BitmapHeader), 1, levelData->LevelCollisionImage);

		//Allocate memory for pixel data//

		//Allocate memory for pointers to first dimension of pixel data
		levelData->LevelCollisionPixelData = malloc(levelData->LevelCollisionImageHeader.Height * sizeof(PixelData *));

		//Allocate memory for each pixel data and assign to the array
		for (i = 0; i < levelData->LevelCollisionImageHeader.Height; i++)
		{
			levelData->LevelCollisionPixelData[i] = malloc(levelData->LevelCollisionImageHeader.Width * sizeof(PixelData));
		}

		for (i = 0; i < levelData->LevelCollisionImageHeader.Height; i++)
		{
			for (j = 0; j < levelData->LevelCollisionImageHeader.Width; j++)
			{
				fread(&levelData->LevelCollisionPixelData[i][j], 1, sizeof(PixelData), levelData->LevelCollisionImage);
			}
		}

		fclose(levelData->LevelCollisionImage);
	}
}

static void FindStartPoint(LevelData * levelData)
{
	int i, j;

	for (i = 0; i < levelData->LevelCollisionImageHeader.Height; i++)
	{
		for (j = 0; j < levelData->LevelCollisionImageHeader.Width; j++)
		{
			if (levelData->LevelCollisionPixelData[i][j].G == 150)
			{
				levelData->startLocation.x = (float)j;
				levelData->startLocation.y = (float)i;

				levelData->startLocation.x *= 2;
				levelData->startLocation.y *= 2;

				levelData->startLocation.x -= Levels[currentLevelIndex].LevelCollisionImageHeader.Width;
				levelData->startLocation.y -= Levels[currentLevelIndex].LevelCollisionImageHeader.Height;

				return;
			}
		}
	}
	AESysPrintf("Error: Start Point not found.");
}

static void FindEndPoint(LevelData * levelData)
{
	int i, j;

	for (i = 0; i < levelData->LevelCollisionImageHeader.Height; i++)
	{
		for (j = 0; j < levelData->LevelCollisionImageHeader.Width; j++)
		{
			if (levelData->LevelCollisionPixelData[i][j].G == 100)
			{
				levelData->endLocation.x = (float)j;
				levelData->endLocation.y = (float)i;

				levelData->endLocation.x *= 2;
				levelData->endLocation.y *= 2;

				levelData->endLocation.x -= Levels[currentLevelIndex].LevelCollisionImageHeader.Width;
				levelData->endLocation.y -= Levels[currentLevelIndex].LevelCollisionImageHeader.Height;

				return;
			}
		}
	}
	AESysPrintf("Error: End Point not found.");
}

static void FindBoundLines(LevelData * levelData)
{
	int i, j;
	levelData->numLines = 0;

	for (i = 0; i < levelData->LevelCollisionImageHeader.Height; i++)
	{
		for (j = 0; j < levelData->LevelCollisionImageHeader.Width; j++)
		{
			if (levelData->LevelCollisionPixelData[i][j].G == 50)
			{
				// memory management for any number of lines
				if (levelData->numLines == 0)
				{
					levelData->boundLines = malloc(sizeof(float) * 4);
				}
				else
				{
					float * temp = malloc(sizeof(float) * 4 * levelData->numLines);
					for (int k = 0; k < levelData->numLines; ++k)
					{
						temp[k * 4] = levelData->boundLines[k * 4];
						temp[(k * 4) + 1] = levelData->boundLines[(k * 4) + 1];
					}
					free(levelData->boundLines);
					levelData->boundLines = temp;
				}


				levelData->boundLines[levelData->numLines * 4] = (float)j;
				levelData->boundLines[(levelData->numLines * 4) + 1] = (float)i;


				Vector2D lineEnd = { 0,0 };
				getLine(levelData, levelData->boundLines[levelData->numLines * 4], levelData->boundLines[(levelData->numLines * 4) + 1], &lineEnd);

				levelData->boundLines[levelData->numLines * 4] *= 2;
				levelData->boundLines[(levelData->numLines * 4) + 1] *= 2;

				levelData->boundLines[levelData->numLines * 4] -= Levels[currentLevelIndex].LevelCollisionImageHeader.Width;
				levelData->boundLines[(levelData->numLines * 4) + 1] -= Levels[currentLevelIndex].LevelCollisionImageHeader.Height;

				levelData->boundLines[(levelData->numLines * 4) + 2] = lineEnd.x;
				levelData->boundLines[(levelData->numLines * 4) + 3] = lineEnd.y;

				levelData->boundLines[(levelData->numLines * 4) + 2] *= 2;
				levelData->boundLines[(levelData->numLines * 4) + 3] *= 2;

				levelData->boundLines[(levelData->numLines * 4) + 2] -= Levels[currentLevelIndex].LevelCollisionImageHeader.Width;
				levelData->boundLines[(levelData->numLines * 4) + 3] -= Levels[currentLevelIndex].LevelCollisionImageHeader.Height;

				++levelData->numLines;
			}
		}
	}

	GenerateLightningData(levelData);
}

static void getLine(LevelData * levelData, float startX, float startY, Vector2D * lineEnd)
{
	if (levelData && lineEnd)
	{
		int direction;
		int indexX = (int)startX;
		int indexY = (int)startY;
		if (levelData->LevelCollisionPixelData[indexY][indexX + 1].G == 49)
		{
			direction = 1;
		}
		else if (levelData->LevelCollisionPixelData[indexY][indexX - 1].G == 49)
		{
			direction = -1;
		}
		else
		{
			AESysPrintf("Error: Line must start either left or right of line start point.\n");
			return;
		}

		bool hasLine = true;
		bool findNewY;
		while (hasLine)
		{
			findNewY = false;
			if (levelData->LevelCollisionPixelData[indexY][indexX + direction].G == 49)
			{
				indexX += direction;
			}
			else
			{
				findNewY = true;
			}

			if (findNewY)
			{
				bool foundUp = false;
				int Ymod = 1;
				while (levelData->LevelCollisionPixelData[indexY + Ymod][indexX].G == 49)
				{
					if (levelData->LevelCollisionPixelData[indexY + Ymod][indexX + direction].G == 49)
					{
						foundUp = true;
						indexY += Ymod;
						break;
					}
					else
					{
						++Ymod;
					}
				}

				if (foundUp == false)
				{
					bool foundDown = false;
					Ymod = -1;
					while (levelData->LevelCollisionPixelData[indexY + Ymod][indexX].G == 49)
					{
						if (levelData->LevelCollisionPixelData[indexY + Ymod][indexX + direction].G == 49)
						{
							foundDown = true;
							indexY += Ymod;
							break;
						}
						else
						{
							--Ymod;
						}
					}

					//if no next pixel is found this is the end of line
					if (foundDown == false)
					{
						lineEnd->x = (float)indexX;
						lineEnd->y = (float)indexY;
						hasLine = false;
					}
				}
			}
		}
	}
}

static void GenerateLightningData(LevelData * levelData)
{
	levelData->lightningData = malloc(sizeof(LightningData) * levelData->numLines);
	for (int i = 0; i < levelData->numLines; ++i)
	{
		Vector2D startPoint = { 0,0 };
		Vector2D endPoint = { 0,0 };
		Vector2D length = { 0,0 };
		Vector2D normal = { 0,0 };
		Vector2D horizAxis = { 1, 0 };

		startPoint.x = levelData->boundLines[i * 4];
		startPoint.y = levelData->boundLines[(i * 4) + 1];
		endPoint.x = levelData->boundLines[(i * 4) + 2];
		endPoint.y = levelData->boundLines[(i * 4) + 3];

		Vector2DSub(&length, &endPoint, &startPoint);
		levelData->lightningData[i].length = Vector2DLength(&length);
		
		
		Vector2DNormalize(&normal, &length);
		levelData->lightningData[i].rotation = Vector2DDotProduct(&normal, &horizAxis) / (Vector2DLength(&normal) * Vector2DLength(&horizAxis));
		levelData->lightningData[i].rotation = acosf(levelData->lightningData[i].rotation);
		levelData->lightningData[i].rotation *= 180.0f / PI;

		

		Vector2DScale(&length, &length, 0.5f);
		levelData->lightningData[i].centerX = startPoint.x + length.x;
		levelData->lightningData[i].centerY = startPoint.y + length.y;
	}
}

static void FindCheckPoints(LevelData * levelData)
{
	int i, j;
	int checkpoint = 0;

	for (i = 0; i < levelData->LevelCollisionImageHeader.Height; i++)
	{
		for (j = 0; j < levelData->LevelCollisionImageHeader.Width; j++)
		{
			if (levelData->LevelCollisionPixelData[i][j].G == 200)
			{
				levelData->checkPointLocations[0 + checkpoint] = (float)j;
				levelData->checkPointLocations[1 + checkpoint] = (float)i;

				levelData->checkPointLocations[0 + checkpoint] *= 2;
				levelData->checkPointLocations[1 + checkpoint] *= 2;

				levelData->checkPointLocations[0 + checkpoint] -= Levels[currentLevelIndex].LevelCollisionImageHeader.Width;
				levelData->checkPointLocations[1 + checkpoint] -= Levels[currentLevelIndex].LevelCollisionImageHeader.Height;

				int k = 0;
				while (levelData->LevelCollisionPixelData[i][k + j].G == 200)
				{
					++k;
				}

				levelData->checkPointLocations[2 + checkpoint] = (float)(j + k);
				levelData->checkPointLocations[3 + checkpoint] = (float)i;

				levelData->checkPointLocations[2 + checkpoint] *= 2;
				levelData->checkPointLocations[3 + checkpoint] *= 2;

				levelData->checkPointLocations[2 + checkpoint] -= Levels[currentLevelIndex].LevelCollisionImageHeader.Width;
				levelData->checkPointLocations[3 + checkpoint] -= Levels[currentLevelIndex].LevelCollisionImageHeader.Height;

				j += ++k;
				checkpoint += 4;
			}
		}
	}
}

static void FreeLevelData()
{
	unsigned i;
	int j;

	for (i = 0; i < numLevels; ++i)
	{
		for (j = 0; j < Levels[i].LevelCollisionImageHeader.Height; ++j)
		{
			free(Levels[i].LevelCollisionPixelData[j]);
		}
		free(Levels[i].LevelCollisionPixelData);
		free(Levels[i].LevelName);
		free(Levels[i].LevelBlueImageName);
		free(Levels[i].LevelRedImageName);
		free(Levels[i].boundLines);
		free(Levels[i].lightningData);
		free(&Levels[i]);
	}
}