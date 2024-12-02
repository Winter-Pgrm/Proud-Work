//------------------------------------------------------------------------------
//
// File Name:	Coin.c
// Author(s):	Brian Lu
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Coin.h"
#include "AEEngine.h"
#include "LevelManager.h"

typedef struct
{
	float mX;
	float mY;

}TextureOffset;

TextureOffset textureOffsetsCoin[10];

static AEGfxVertexList * CoinMesh;

static AEGfxTexture * CoinTexture;

static float coinDelay = 5.0f;
static int currentCoinTextureOffset = 0;

void CoinInit()
{
	textureOffsetsCoin[0].mX = 0.0f;			textureOffsetsCoin[0].mY = 0.0f;
	textureOffsetsCoin[1].mX = 0.34f;			textureOffsetsCoin[1].mY = 0.0f;
	textureOffsetsCoin[2].mX = 0.66f;			textureOffsetsCoin[2].mY = 0.0f;
	textureOffsetsCoin[3].mX = 0.0f;			textureOffsetsCoin[3].mY = 0.334f;
	textureOffsetsCoin[4].mX = 0.33f;			textureOffsetsCoin[4].mY = 0.334f;
	textureOffsetsCoin[5].mX = 0.66f;			textureOffsetsCoin[5].mY = 0.334f;
	textureOffsetsCoin[6].mX = 0.0f;			textureOffsetsCoin[6].mY = 0.66f;
	textureOffsetsCoin[7].mX = 0.33f;			textureOffsetsCoin[7].mY = 0.66f;
	textureOffsetsCoin[8].mX = 0.66f;			textureOffsetsCoin[8].mY = 0.66f;

	AEGfxMeshStart();

	AEGfxTriAdd(
		-30.0f, -30.0f, 0x00FF00FF, 0.0f, 0.33f,
		30.0f, -30.0f, 0x00FFFF00, 0.33f, 0.33f,
		-30.0f, 30.0f, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		30.0f, -30.0f, 0x00FFFFFF, 0.33f, 0.33f,
		30.0f, 30.0f, 0x00FFFFFF, 0.33f, 0.0f,
		-30.0f, 30.0f, 0x00FFFFFF, 0.0f, 0.0f);

	CoinMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(CoinMesh, "Failed to create CoinMesh!");

	CoinTexture = AEGfxTextureLoad("Assets/New Piskel.png");

}

void CoinUpdate(float dt)
{
	AEVec2 startLocation = *GetEndPoint();
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTransparency(1.0f);

	coinDelay -= dt;

	AEGfxSetFullTransformWithZOrder(startLocation.x, startLocation.y, 1.0f, 0.0f, 1.0f, 1.0f);
	AEGfxTextureSet(CoinTexture, textureOffsetsCoin[currentCoinTextureOffset].mX, textureOffsetsCoin[currentCoinTextureOffset].mY);
	AEGfxMeshDraw(CoinMesh, AE_GFX_MDM_TRIANGLES);


	if (coinDelay <= 0)
	{
		++currentCoinTextureOffset;

		if (currentCoinTextureOffset > 8)
		{
			currentCoinTextureOffset = 0;
		}

		coinDelay = 5.0f;
	}
}

void CoinShutDown()
{
	AEGfxMeshFree(CoinMesh);
}