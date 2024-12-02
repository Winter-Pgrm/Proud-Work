
//------------------------------------------------------------------------------
//
// File Name:	Timer.c
// Author(s):	Brian Lu
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "Timer.h"

#define TIMEDURATION 8.6f //1 second

typedef struct
{
	float mX;
	float mY;

}TextureOffset;

TextureOffset textureOffsets[10];

AEGfxVertexList  *timerMeshSec;
AEGfxTexture  *timerTexSec;

AEGfxVertexList  *timerMeshTens;
AEGfxTexture  *timerTexTens;

AEGfxVertexList  *timerMeshHundreds;
AEGfxTexture  *timerTexHundreds;

AEGfxVertexList  *timerMeshThousands;
AEGfxTexture  *timerTexThousands;

AEGfxVertexList  *colonMesh;
AEGfxTexture  *colonTex;

AEGfxVertexList  *timerBackMesh;
AEGfxTexture  *timerBackTex;

unsigned int currentTextureOffsetSec = 0; //ones
unsigned int currentTextureOffsetTens = 0; //tens
unsigned int currentTextureOffsetHundreds = 0; //hundreds
unsigned int currentTextureOffsetThousands = 0; //thousands

float duration = TIMEDURATION;

static float ScoreAnimation = 16.0f;
static float scale = 0;
static float x = 0;
static float y = 0;
static bool ScoreFinal = FALSE;


static int highScoreMin = 59;
static int highScoreSec = 59;
static int scoreMin;
static int scoreSec;
static int firstCheck = 0;

static int level = 1;

float camX, camY;

void TimerInit()
{
	textureOffsets[0].mX = 0.0f;			textureOffsets[0].mY = 0.0f;
	textureOffsets[1].mX = 0.1f;			textureOffsets[1].mY = 0.0f;
	textureOffsets[2].mX = 0.2f;			textureOffsets[2].mY = 0.0f;
	textureOffsets[3].mX = 0.3f;			textureOffsets[3].mY = 0.0f;
	textureOffsets[4].mX = 0.4f;			textureOffsets[4].mY = 0.0f;
	textureOffsets[5].mX = 0.5f;			textureOffsets[5].mY = 0.0f;
	textureOffsets[6].mX = 0.6f;			textureOffsets[6].mY = 0.0f;
	textureOffsets[7].mX = 0.7f;			textureOffsets[7].mY = 0.0f;
	textureOffsets[8].mX = 0.8f;			textureOffsets[8].mY = 0.0f;
	textureOffsets[9].mX = 0.9f;			textureOffsets[9].mY = 0.0f;

	AEGfxMeshStart();

	AEGfxTriAdd(
		-80.0f, -80.0f, 0x00FF00FF, 0.0f, 1.0f,
		80.0f, -80.0f, 0x00FFFF00, 0.1f, 1.0f,
		-80.0f, 80.0f, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		80.0f, -80.0f, 0x00FFFFFF, 0.1f, 1.0f,
		80.0f, 80.0f, 0x00FFFFFF, 0.1f, 0.0f,
		-80.0f, 80.0f, 0x00FFFFFF, 0.0f, 0.0f);

	timerMeshSec = AEGfxMeshEnd();
	AE_ASSERT_MESG(timerMeshSec, "Failed to create timerMesh!");

	timerTexSec = AEGfxTextureLoad("Assets/timer.png");

	AEGfxMeshStart();

	AEGfxTriAdd(
		-80.0f, -80.0f, 0x00FF00FF, 0.0f, 1.0f,
		80.0f, -80.0f, 0x00FFFF00, 0.1f, 1.0f,
		-80.0f, 80.0f, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		80.0f, -80.0f, 0x00FFFFFF, 0.1f, 1.0f,
		80.0f, 80.0f, 0x00FFFFFF, 0.1f, 0.0f,
		-80.0f, 80.0f, 0x00FFFFFF, 0.0f, 0.0f);

	timerMeshTens = AEGfxMeshEnd();
	AE_ASSERT_MESG(timerMeshTens, "Failed to create timerMesh!");

	timerTexTens = AEGfxTextureLoad("Assets/timer.png");

	AEGfxMeshStart();

	AEGfxTriAdd(
		-80.0f, -80.0f, 0x00FF00FF, 0.0f, 1.0f,
		80.0f, -80.0f, 0x00FFFF00, 0.1f, 1.0f,
		-80.0f, 80.0f, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		80.0f, -80.0f, 0x00FFFFFF, 0.1f, 1.0f,
		80.0f, 80.0f, 0x00FFFFFF, 0.1f, 0.0f,
		-80.0f, 80.0f, 0x00FFFFFF, 0.0f, 0.0f);

	timerMeshHundreds = AEGfxMeshEnd();
	AE_ASSERT_MESG(timerMeshHundreds, "Failed to create timerMesh!");

	timerTexHundreds = AEGfxTextureLoad("Assets/timer.png");

	AEGfxMeshStart();

	AEGfxTriAdd(
		-80.0f, -80.0f, 0x00FF00FF, 0.0f, 1.0f,
		80.0f, -80.0f, 0x00FFFF00, 0.1f, 1.0f,
		-80.0f, 80.0f, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		80.0f, -80.0f, 0x00FFFFFF, 0.1f, 1.0f,
		80.0f, 80.0f, 0x00FFFFFF, 0.1f, 0.0f,
		-80.0f, 80.0f, 0x00FFFFFF, 0.0f, 0.0f);

	timerMeshThousands = AEGfxMeshEnd();
	AE_ASSERT_MESG(timerMeshThousands, "Failed to create timerMesh!");

	timerTexThousands = AEGfxTextureLoad("Assets/timer.png");

	AEGfxMeshStart();

	AEGfxTriAdd(
		-20.0f, -20.0f, 0x00FF00FF, 0.0f, 1.0f,
		20.0f, -20.0f, 0x00FFFF00, 1.0f, 1.0f,
		-20.0f, 20.0f, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		20.0f, -20.0f, 0x00FFFFFF, 1.0f, 1.0f,
		20.0f, 20.0f, 0x00FFFFFF, 1.0f, 0.0f,
		-20.0f, 20.0f, 0x00FFFFFF, 0.0f, 0.0f);

	colonMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(colonMesh, "Failed to create colonMesh!");

	colonTex = AEGfxTextureLoad("Assets/Colon.png");

	AEGfxMeshStart();

	AEGfxTriAdd(
		-160.0f, -120.0f, 0x00FF00FF, 0.0f, 1.0f,
		160.0f, -120.0f, 0x00FFFF00, 1.0f, 1.0f,
		-160.0f, 120.0f, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		160.0f, -120.0f, 0x00FFFFFF, 1.0f, 1.0f,
		160.0f, 120.0f, 0x00FFFFFF, 1.0f, 0.0f,
		-160.0f, 120.0f, 0x00FFFFFF, 0.0f, 0.0f);

	timerBackMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(timerBackMesh, "Failed to create backgroundMesh!");

	timerBackTex = AEGfxTextureLoad("Assets/TimerBackground.png");
}
//Changing mesh + keeping up with the camera

//can return int array to get time
void TimerUpdate(float dt)
{
	AEGfxSetTransparency(1.0f);
	AEGfxGetCamPosition(&camX, &camY);
	// Drawing object
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	camX += 640;
	camY += 400;
	//background for timer
	if (ScoreFinal == FALSE)
	{
		AEGfxSetFullTransformWithZOrder(camX - 120.0f, camY - 35.0f, 2.0f, 0.0f, 1.0f, 1.0f);
		AEGfxTextureSet(timerBackTex, 0, 0);
		AEGfxMeshDraw(timerBackMesh, AE_GFX_MDM_TRIANGLES);

		AEGfxSetFullTransformWithZOrder(camX - 40.0f, camY - 40.0f, 3.0f, 0.0f, 1.0f, 1.0f);
		AEGfxTextureSet(timerTexSec, textureOffsets[currentTextureOffsetSec].mX, textureOffsets[currentTextureOffsetSec].mY);
		AEGfxMeshDraw(timerMeshSec, AE_GFX_MDM_TRIANGLES);

		AEGfxSetFullTransformWithZOrder(camX - 80.0f, camY - 40.0f, 3.0f, 0.0f, 1.0f, 1.0f);
		AEGfxTextureSet(timerTexTens, textureOffsets[currentTextureOffsetTens].mX, textureOffsets[currentTextureOffsetTens].mY);
		AEGfxMeshDraw(timerMeshTens, AE_GFX_MDM_TRIANGLES);

		AEGfxSetFullTransformWithZOrder(camX - 160.0f, camY - 40.0f, 3.0f, 0.0f, 1.0f, 1.0f);
		AEGfxTextureSet(timerTexHundreds, textureOffsets[currentTextureOffsetHundreds].mX, textureOffsets[currentTextureOffsetHundreds].mY);
		AEGfxMeshDraw(timerMeshHundreds, AE_GFX_MDM_TRIANGLES);

		AEGfxSetFullTransformWithZOrder(camX - 200.0f, camY - 40.0f, 3.0f, 0.0f, 1.0f, 1.0f);
		AEGfxTextureSet(timerTexThousands, textureOffsets[currentTextureOffsetThousands].mX, textureOffsets[currentTextureOffsetThousands].mY);
		AEGfxMeshDraw(timerMeshThousands, AE_GFX_MDM_TRIANGLES);

		AEGfxSetFullTransformWithZOrder(camX - 120.0f, camY - 40.0f, 3.0f, 0.0f, 1.0f, 1.0f);
		AEGfxTextureSet(colonTex, 0, 0);
		AEGfxMeshDraw(colonMesh, AE_GFX_MDM_TRIANGLES);
	}
	else if (ScoreFinal == TRUE)
	{
		TimerAnimation(dt);
	}

	duration -= dt;

	if (duration <= 0)
	{
		currentTextureOffsetSec++;

		if (currentTextureOffsetSec > 9) //seconds
		{
			currentTextureOffsetSec = 0;
			currentTextureOffsetTens++;

			if (currentTextureOffsetTens > 5) // 60 seconds
			{
				currentTextureOffsetTens = 0;
				currentTextureOffsetHundreds++;

				if (currentTextureOffsetHundreds > 9) //minutes
				{
					currentTextureOffsetHundreds = 0;
					currentTextureOffsetThousands++;
				}
			}
		}

		duration = TIMEDURATION;
	}
}
//resets the timer to 00:00
void TimerReset()
{
	currentTextureOffsetSec = 0;
	currentTextureOffsetTens = 0;
	currentTextureOffsetHundreds = 0;
	currentTextureOffsetThousands = 0;
}

void TimerAnimation(float dt)
{
	AEGfxGetCamPosition(&camX, &camY);

	ScoreAnimation -= dt;
	scale += 0.05f;
	x += 5.2f;
	y += 3.6f;

	AEGfxSetFullTransformWithZOrder(camX - 120.0f - x, camY - 35.0f - y, 10.0f, 0.0f, scale, scale);
	AEGfxTextureSet(timerBackTex, 0, 0);
	AEGfxMeshDraw(timerBackMesh, AE_GFX_MDM_TRIANGLES);

	AEGfxSetFullTransformWithZOrder(camX - 40.0f - x, camY - 40.0f - y, 10.0f, 0.0f, scale, scale);
	AEGfxTextureSet(timerTexSec, textureOffsets[currentTextureOffsetSec].mX, textureOffsets[currentTextureOffsetSec].mY);
	AEGfxMeshDraw(timerMeshSec, AE_GFX_MDM_TRIANGLES);

	AEGfxSetFullTransformWithZOrder(camX - 80.0f - x, camY - 40.0f - y, 10.0f, 0.0f, scale, scale);
	AEGfxTextureSet(timerTexTens, textureOffsets[currentTextureOffsetTens].mX, textureOffsets[currentTextureOffsetTens].mY);
	AEGfxMeshDraw(timerMeshTens, AE_GFX_MDM_TRIANGLES);

	AEGfxSetFullTransformWithZOrder(camX - 160.0f - x, camY - 40.0f - y, 10.0f, 0.0f, scale, scale);
	AEGfxTextureSet(timerTexHundreds, textureOffsets[currentTextureOffsetHundreds].mX, textureOffsets[currentTextureOffsetHundreds].mY);
	AEGfxMeshDraw(timerMeshHundreds, AE_GFX_MDM_TRIANGLES);

	AEGfxSetFullTransformWithZOrder(camX - 200.0f - x, camY - 40.0f - y, 10.0f, 0.0f, scale, scale);
	AEGfxTextureSet(timerTexThousands, textureOffsets[currentTextureOffsetThousands].mX, textureOffsets[currentTextureOffsetThousands].mY);
	AEGfxMeshDraw(timerMeshThousands, AE_GFX_MDM_TRIANGLES);

	AEGfxSetFullTransformWithZOrder(camX - 120.0f - x, camY - 40.0f - y, 10.0f, 0.0f, scale, scale);
	AEGfxTextureSet(colonTex, 0, 0);
	AEGfxMeshDraw(colonMesh, AE_GFX_MDM_TRIANGLES);

	if (ScoreAnimation < 0)
	{
		ScoreFinal = FALSE;
	}
}

bool GetFinalScore()
{
	return ScoreFinal;
}

void SetFinalScore(bool final)
{
	ScoreFinal = final;
}

void UpdateScore(void)
{
	char title[256];
	if (highScoreMin < 10)
	{
		if (highScoreSec > 10)
		{
			sprintf_s(title, sizeof(title), "Inversion, Fastest Time = 0%d:%d", highScoreMin, highScoreSec);
		}
		else
		{
			sprintf_s(title, sizeof(title), "Inversion, Fastest Time = 0%d:0%d", highScoreMin, highScoreSec);
		}
	}
	else if (highScoreSec < 10)
	{
		if (highScoreMin < 10)
		{
			sprintf_s(title, sizeof(title), "Inversion, Fastest Time = 0%d:0%d", highScoreMin, highScoreSec);
		}
		else
		{
			sprintf_s(title, sizeof(title), "Inversion, Fastest Time = %d:0%d", highScoreMin, highScoreSec);
		}
	}
	else
	{
		sprintf_s(title, sizeof(title), "Inversion, Fastest Time = %d:%d", highScoreMin, highScoreSec);
	}
	AESysSetWindowTitle(title);
}

void ScoreInit()
{
	if (scoreMin < highScoreMin) //checks for fastest time
	{
		highScoreMin = scoreMin;
		highScoreSec = scoreSec;

	}
	else if (scoreMin == highScoreMin)
	{
		if (scoreSec < highScoreSec)
		{
			highScoreMin = scoreMin;
			highScoreSec = scoreSec;
		}
	}
	scoreMin = 0;
	scoreSec = 0;

	level = 1;
}

void nextLevel()
{
	++level;
}

void getFastestTime()
{
	scoreMin = currentTextureOffsetThousands * 10 + currentTextureOffsetHundreds;
	scoreSec = currentTextureOffsetTens * 10 + currentTextureOffsetSec;
}