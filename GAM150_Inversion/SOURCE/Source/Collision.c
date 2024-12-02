//------------------------------------------------------------------------------
//
// File Name:	Collision.c
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
#include "Player.h"
#include "Gfx.h"
#include "Soundfunctions.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

static int BGWidth;
static int BGHeight;
static bool (*collisionFunction)(int xObjectColPoint, int yObjectColPoint);
static const PixelData ** pixData;
const static AEVec2 playerLowerYBounds[4] = { { -23, -30 },{ -10, -30 },{ 10, -30 },{ 23, -30 } };
const static AEVec2 playerUpperYBounds[4] = { { -23, 30 },{ -10, 30 },{ 10, 30 },{ 23, 30 } };
const static AEVec2 playerLeftXBounds[4] = { { -23, -30 },{ -23, -15 },{ -23, 15 },{ -23, 30 } };
const static AEVec2 playerRightXBounds[4] = { { 23, -30 },{ 23, -15 },{ 23, 15 },{ 23, 30 } };


//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static bool CollisionLightning(int xObjectColPoint, int yObjectColPoint);

//Collision is based off RED pixels
static bool CollisionRed(int xObjectColPoint, int yObjectColPoint);

//Collision is based off BLUE pixels
static bool CollisionBlue(int xObjectColPoint, int yObjectColPoint);


static void CoordPlayerToWorld(const float playerX, const float playerY, int * newX, int * newY);

static void CheckCollision(CollisionData * data, float playerX, float playerY, float velX, float velY);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Initialize Collision for current level
void CollisionInit()
{
	BGWidth = GetCurrentLevelImageHeader()->Width;
	BGHeight = GetCurrentLevelImageHeader()->Height;
	pixData = *GetCurrentLevelCollisionData();
	collisionFunction = CollisionRed;
}

//Changes which color is being used to detect collision
void Inversion(PlayerPtr player)
{
	if (collisionFunction == CollisionRed)
	{
		collisionFunction = CollisionBlue;
		CharacterSetTexture(PlayerGetCharacter(player), "Assets/PenguinFramesBlue.png");
		CharacterSetPrev(PlayerGetCharacter(player), 0);
		playsoundInversionBlue(); //sound not tested - alex 
	}
	else
	{
		collisionFunction = CollisionRed;
		CharacterSetTexture(PlayerGetCharacter(player), "Assets/PenguinFrames.png");
		CharacterSetPrev(PlayerGetCharacter(player), 1);
		playsoundInversionRed();  //sound not tested - alex 
	}
	GfxInversion();
}

//Collision for player object
void PlayerCollision(PlayerPtr player, float xvelocity, float yvelocity, CollisionData * finalData)
{
	memset(finalData, FALSE, sizeof(CollisionData));

	finalData->xColVel = (int)xvelocity;
	finalData->yColVel = (int)yvelocity;

	float x, y;
	x = PlayerGetXcoordinate(player);
	y = PlayerGetYcoordinate(player);

	CollisionData collision;
	int i;

	if (xvelocity > 0)
	{
		for (i = 0; i < 4; i++)
		{
			CheckCollision(&collision, x + playerRightXBounds[i].x, y + playerRightXBounds[i].y, xvelocity, yvelocity);
			
			if (collision.hitLightning)
			{
				CharacterSetLives(PlayerGetCharacter(player), 0);
			}

			if (collision.right == true && collision.xColVel < finalData->xColVel)
			{
				finalData->right = true;
				finalData->xColVel = collision.xColVel;
				finalData->xColVel = 0;
			}
		}
	}
	//left
	else if (xvelocity < 0)
	{
		for (i = 0; i < 4; i++)
		{
			CheckCollision(&collision, x + playerLeftXBounds[i].x, y + playerLeftXBounds[i].y, xvelocity, yvelocity);

			if (collision.hitLightning)
			{
				CharacterSetLives(PlayerGetCharacter(player), 0);
			}

			if (collision.left == true && collision.xColVel > finalData->xColVel)
			{
				finalData->left = true;
				finalData->xColVel = collision.xColVel;
				finalData->xColVel = 0;
			}
		}
	}

	if (yvelocity > 0)
	{
		for (i = 0; i < 4; i++)
		{
			CheckCollision(&collision, x + playerUpperYBounds[i].x, y + playerUpperYBounds[i].y, xvelocity, yvelocity);

			if (collision.hitLightning)
			{
				CharacterSetLives(PlayerGetCharacter(player), 0);
			}

			if (collision.up == true && collision.yColVel < finalData->yColVel)
			{
				finalData->up = true;
				finalData->yColVel = collision.yColVel;
				finalData->yColVel = 0;
			}
		}
	}
	else if (yvelocity < 0)
	{
		for (i = 0; i < 4; i++)
		{
			CheckCollision(&collision, x + playerLowerYBounds[i].x, y + playerLowerYBounds[i].y, xvelocity, yvelocity);

			if (collision.hitLightning)
			{
				CharacterSetLives(PlayerGetCharacter(player), 0);
			}

			if (collision.down == true)
			{
				finalData->down = true;
				if (collision.yColVel > finalData->yColVel)
				{
					finalData->yColVel = collision.yColVel;
				}
			}
		}
	}
}

void HookCollision(float currentHookPositionX, float currentHookPositionY, float hookSpeedX, float hookSpeedY, CollisionData * finalData)
{
	CheckCollision(finalData, currentHookPositionX, currentHookPositionY, hookSpeedX, hookSpeedY);
}


//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

static bool CollisionLightning(int xObjectColPoint, int yObjectColPoint)
{
	//Check collision
	if (xObjectColPoint > 0 && xObjectColPoint < BGWidth && yObjectColPoint > 0 && yObjectColPoint < BGHeight)
	{
		if (pixData[yObjectColPoint][xObjectColPoint].G == 49)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

static bool CollisionRed(int xObjectColPoint, int yObjectColPoint)
{
	//Check collision
	if (xObjectColPoint > 0 && xObjectColPoint < BGWidth && yObjectColPoint > 0 && yObjectColPoint < BGHeight)
	{
		if (pixData[yObjectColPoint][xObjectColPoint].B < 255)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

static bool CollisionBlue(int xObjectColPoint, int yObjectColPoint)
{
	//Check collision
	if (xObjectColPoint > 0 && xObjectColPoint < BGWidth && yObjectColPoint > 0 && yObjectColPoint < BGHeight)
	{
		if (pixData[yObjectColPoint][xObjectColPoint].R < 255)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

static void CoordPlayerToWorld(const float playerX, const float playerY, int * newX, int * newY)
{
	// Modify coordinate system
	*newX = (int)playerX + BGWidth;
	*newY = (int)playerY + BGHeight;

	*newX /= 2;
	*newY /= 2;
}

static void CheckCollision(CollisionData * data, float playerX, float playerY, float velX, float velY)
{
	memset(data, FALSE, sizeof(CollisionData));
	// Cast coordinates
	int shiftedX = 0;
	int shiftedY = 0;
	CoordPlayerToWorld(playerX, playerY, &shiftedX, &shiftedY);

	data->hitLightning = CollisionLightning(shiftedX, shiftedY - 1);

	// Check to make sure player is in level
	if (shiftedX >= BGWidth || shiftedY >= BGHeight || shiftedX < 0 || shiftedY < 0)
	{
		AESysPrintf("Out of map\n");
		return;
	}
	else
	{
		//casted for index usage
		int Xvelocity, Yvelocity;

		//x
		if (velX > 0 && velX < 1)
		{
			Xvelocity = 1;
		}
		else if (velX < 0 && velX > -1)
		{
			Xvelocity = -1;
		}
		else
		{
			Xvelocity = (int)velX;
		}

		//y
		if (velY > 0 && velY < 1)
		{
			Yvelocity = 1;
		}
		else if (velY < 0 && velY > -1)
		{
			Yvelocity = -1;
		}
		else
		{
			Yvelocity = (int)velY;
		}
		//

		if (Xvelocity > 0)
		{
			int i;
			for (i = 1; i <= Xvelocity; ++i)
			{
				data->right = collisionFunction(shiftedX + i, shiftedY);
				if (data->right)
				{
					AESysPrintf("COLLIDED right\n");
					data->xColVel = i - 1;
					break;
				}
			}
		}
		else if (Xvelocity < 0)
		{
			int i;
			for (i = -1; i >= Xvelocity; --i)
			{
				data->left = collisionFunction(shiftedX + i, shiftedY);
				if (data->left)
				{
					AESysPrintf("COLLIDED left\n");
					data->xColVel = i + 1;
					break;
				}
			}
		}

		if (Yvelocity > 0)
		{
			int i;
			for (i = 1; i <= Yvelocity; ++i)
			{
				data->up = collisionFunction(shiftedX, shiftedY + i);
				if (data->up)
				{
					AESysPrintf("COLLIDED up\n");
					data->yColVel = i - 1;
					break;
				}
			}
		}
		else if (Yvelocity < 0)
		{
			int i;
			for (i = -1; i >= Yvelocity; --i)
			{
				data->down = collisionFunction(shiftedX, shiftedY + i);
				if (data->down)
				{
					AESysPrintf("COLLIDED down\n");
					data->yColVel = i + 1;
					break;
				}
			}
		}
	}
}
