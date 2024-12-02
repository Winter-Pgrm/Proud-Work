//------------------------------------------------------------------------------
//
// File Name:	Gfx.h
// Author(s):	Ian Gaither, Brian Lu, Alex Phillips
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "AEEngine.h"
#include "Player.h"
#include "LevelManager.h"
#include "GameStateLevel.h"
#include "Hook.h"
#include "CheckpointFlag.h"
#include "random.h"
#include "Coin.h"
#include "physics.h"
#include "Death.h"
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

static float BGWidth;
static float BGHeight;	
static AEGfxVertexList * BGMesh;				// Pointer to Mesh (Model)
static AEGfxVertexList * PlayerMesh;
static AEGfxVertexList * HookMesh;
static AEGfxVertexList ** LightningMesh;

static AEGfxTexture * BGTextureRed;					// Pointer to Texture (Image)
static AEGfxTexture * BGTextureBlue;
static AEGfxTexture * currentBG;
static AEGfxTexture * RopeTexture;
static AEGfxTexture * LightningTexture;
static int prev = 0;

static float LightningTimer = 0;
static float LightningTextureOffset = 0;

bool drawHook;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void BGInit();
static void BGUpdate();
static void PlayerInit();
static void PlayerUpdate(PlayerPtr player);
static void HookInit();
static void HookGfxUpdate(PlayerPtr player, AEVec2 hookLocation, float radius);
static void LightningInit();
static void LightningUpdate(float dt);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

void GfxInversion()
{
	if (currentBG == BGTextureRed)
	{
		currentBG = BGTextureBlue;
	}
	else if(currentBG == BGTextureBlue)
	{
		currentBG = BGTextureRed;
	}
}

void HookInAir(bool isInAir)
{
	drawHook = isInAir;
}

// Initialize the ...
void GfxInit()
{
	drawHook = false;
	BGInit();
	PlayerInit();
	FlagInit();
	FlagInit2();
	deathInit();

	RopeTexture = AEGfxTextureLoad("Assets/Rope.png");
	LightningTexture = AEGfxTextureLoad("Assets/Lightning.png");
}

// Update the ...
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GfxUpdate(PlayerPtr player, float dt)
{
	BGUpdate();
	if (CharacterGetLives(PlayerGetCharacter(player)) == 1)
	{
		PlayerUpdate(player);
	}
	else
	{
		deathUpdate(player);
	}
	if (drawHook)
	{
		HookInit();
		float x = currentHookX();
		float y = currentHookY();
		AEVec2 hookloc;
		hookloc.x = x;
		hookloc.y = y;

	
		HookGfxUpdate(player, hookloc, currentHookRad());
	}
	LightningUpdate(dt);
}

void GfxChangeLevel()
{
	AEGfxMeshFree(BGMesh);
	if (LightningMesh)
	{
		free(LightningMesh);
	}
	BGInit();
}

// Shutdown the ...
void GfxShutdown()
{
	AEGfxMeshFree(BGMesh);
	AEGfxMeshFree(PlayerMesh);
	FlagShutDown();
	CoinShutDown();
	deathShutdown();
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

static void BGInit()
{
	BGWidth = (float)GetCurrentLevelImageHeader()->Width;
	BGHeight = (float)GetCurrentLevelImageHeader()->Height;

	BGTextureRed = AEGfxTextureLoad(GetRedImageName());
	BGTextureBlue = AEGfxTextureLoad(GetBlueImageName());
	currentBG = BGTextureBlue;

	// This shape has 2 triangles

	AEGfxTriAdd(
		-BGWidth, -BGHeight, 0x00FF00FF, 0.0f, 1.0f,
		BGWidth, -BGHeight, 0x00FFFF00, 1.0f, 1.0f,
		-BGWidth, BGHeight, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		BGWidth, -BGHeight, 0x00FFFFFF, 1.0f, 1.0f,
		BGWidth, BGHeight, 0x00FFFFFF, 1.0f, 0.0f,
		-BGWidth, BGHeight, 0x00FFFFFF, 0.0f, 0.0f);

	BGMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(BGMesh, "Failed to create BGMesh!!");

	LightningInit();
}

static void BGUpdate()
{
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetFullTransformWithZOrder(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	AEGfxTextureSet(currentBG, 0, 0);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(BGMesh, AE_GFX_MDM_TRIANGLES);
}

static void PlayerInit()
{
	
	AEGfxMeshStart();

	AEGfxTriAdd(
		-30.0f, -30.0f, 0x00FF00FF, 0.0f, 1.0f,
		30.0f, -30.0f, 0x00FFFF00, 0.19f, 1.0f,
		-30.0f, 45.0f, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		30.0f, -30.0f, 0x00FFFFFF, 0.19f, 1.0f,
		30.0f, 45.0f, 0x00FFFFFF, 0.19f, 0.0f,
		-30.0f, 45.0f, 0x00FFFFFF, 0.0f, 0.0f);

	PlayerMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(PlayerMesh, "Failed to create PlayerMesh!!");
}


static void PlayerUpdate(PlayerPtr player)
{
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	
	if (getXVelocity() > 0)
	{
		AEGfxSetFullTransformWithZOrder(PlayerGetXcoordinate(player), PlayerGetYcoordinate(player), 0.0f, 0.0f, 1.0f, 1.0f);
		prev = 0;
	}
	else if (getXVelocity() < 0)
	{
		AEGfxSetFullTransformWithZOrder(PlayerGetXcoordinate(player), PlayerGetYcoordinate(player), 0.0f, 0.0f, -1.0f, 1.0f);
		prev = 1;
	}
	else
	{
		if (prev == 0)
		{
			AEGfxSetFullTransformWithZOrder(PlayerGetXcoordinate(player), PlayerGetYcoordinate(player), 0.0f, 0.0f, 1.0f, 1.0f);
		}
		else if (prev == 1)
		{
			AEGfxSetFullTransformWithZOrder(PlayerGetXcoordinate(player), PlayerGetYcoordinate(player), 0.0f, 0.0f, -1.0f, 1.0f);
		}
	}
	AEGfxTextureSet(CharacterGetTexture(PlayerGetCharacter(player)), PlayerGetFrameIndexX(player), PlayerGetFrameIndexY(player));
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(PlayerMesh, AE_GFX_MDM_TRIANGLES);
}

static void HookInit()
{
	AEGfxMeshStart();

	float CorrectForScale = currentHookRad(); // this should be the current length of the rope
	CorrectForScale /= 64.0f;  // basically divide by texture width

	AEGfxTriAdd(
		0.0f, -0.5f, 0x00FFFFFF, 0.0f, 1.0f,
		1.0f, -0.5f, 0x00FFFFFF, CorrectForScale, 1.0f,
		0.0f, 0.5f, 0x00FFFFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		1.0f, -0.5f, 0x00FFFFFF, CorrectForScale, 1.0f,
		1.0f, 0.5f, 0x00FFFFFF, CorrectForScale, 0.0f,
		0.0f, 0.5f, 0x00FFFFFF, 0.0f, 0.0f);

	HookMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(HookMesh, "Failed to create HookMesh!!");
}

static void HookGfxUpdate(PlayerPtr player, AEVec2 hookLocation, float radius)
{
	UNREFERENCED_PARAMETER(radius);
	float hookAngle = (180/PI) * atan2f(hookLocation.y - PlayerGetYcoordinate(player), hookLocation.x - PlayerGetXcoordinate(player));
	//float playerX = PlayerGetXcoordinate(player);
	//float playerY = PlayerGetYcoordinate(player);
	float diffRopeX = hookLocation.x - PlayerGetXcoordinate(player);
	float diffRopeY = hookLocation.y - PlayerGetYcoordinate(player);
	float scaleRope = sqrtf(diffRopeX * diffRopeX + diffRopeY * diffRopeY);

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetFullTransform(PlayerGetXcoordinate(player), PlayerGetYcoordinate(player), hookAngle, scaleRope, 20/*thickness of rope*/);
	AEGfxTextureSet(RopeTexture, 0, 0);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(HookMesh, AE_GFX_MDM_TRIANGLES);

	AEGfxMeshFree(HookMesh);
}

static void LightningInit()
{
	int numLines = GetLevelNumLines();
//	float * lines = GetLineBounds();
	LightningMesh = malloc(sizeof(AEGfxVertexList *) * numLines);

	for (int i = 0; i < numLines; ++i)
	{
		AEGfxMeshStart();

		AEGfxTriAdd(
			-0.5, -0.5, 0x00FF00FF, 0.0f, 1.0f,
			0.5, -0.5, 0x00FFFF00, 1.0f, 1.0f,
			-0.5, 0.5, 0x00F00FFF, 0.0f, 0.0f);

		AEGfxTriAdd(
			0.5, -0.5, 0x00FFFFFF, 1.0f, 1.0f,
			0.5, 0.5, 0x00FFFFFF, 1.0f, 0.0f,
			-0.5, 0.5, 0x00FFFFFF, 0.0f, 0.0f);

		LightningMesh[i] = AEGfxMeshEnd();
		AE_ASSERT_MESG(LightningMesh, "Failed to create LightningMesh!!");
	}
}

static void LightningUpdate(float dt)
{
	int numLines = GetLevelNumLines();
//	float * lines = GetLineBounds();
	LightningTimer += dt;
	if (LightningTimer > 0.5f)
	{
		LightningTextureOffset = randomfloatrange(0, 1200);
		LightningTimer = 0;
	}
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTransparency(1.0f);
	for (int i = 0; i < numLines; ++i)
	{
		LightningData * currData = GetLightningData();
		AEGfxSetFullTransform(currData[i].centerX, currData[i].centerY, currData[i].rotation, currData[i].length, 100/*thickness of rope*/);
		AEGfxTextureSet(LightningTexture, LightningTextureOffset, 0);
		AEGfxMeshDraw(LightningMesh[i], AE_GFX_MDM_TRIANGLES);
	}
}