//------------------------------------------------------------------------------
//
// File Name:	GameOver.c
// Author(s):	Deni Van Winkle
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "AEEngine.h"
#include "GameStateManager.h"
#include "Trace.h"
#include "Mesh.h"
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
static struct AEGfxVertexList *GameOverMesh;
static AEGfxTexture *GameOverTexture;;
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

void GameOverLoad()
{
	TraceMessage("GameOver: Load");
}


void GameOverInit()
{
	TraceMessage("GameOver: Init");

	// Needs the art for this
	GameOverTexture = AEGfxTextureLoad("Assets/GameOver.jpg");
	AEGfxMeshStart();

	// This shape has 2 triangles

	AEGfxTriAdd(
		-640, -400, 0x00FF00FF, 0.0f, 1.0f,
		640, -400, 0x00FFFF00, 1.0f, 1.0f,
		-640, 400, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		640, -400, 0x00FFFFFF, 1.0f, 1.0f,
		640, 400, 0x00FFFFFF, 1.0f, 0.0f,
		-640, 400, 0x00FFFFFF, 0.0f, 0.0f);

	GameOverMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(GameOverMesh, "Failed to create LogoMesh!!");
}

void GameOverUpdate(float dt)
{
	TraceMessage("GameOver: Update");
	AESysFrameStart();
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetFullTransformWithZOrder(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	AEGfxTextureSet(GameOverTexture, 0, 0);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(GameOverMesh, AE_GFX_MDM_TRIANGLES);
	AESysFrameEnd();



}

void GameOverShutdown()
{
	TraceMessage("GameOver: Shutdown");
	AEGfxMeshFree(GameOverMesh);
	AEGfxTextureUnload(GameOverTexture);
}


void GameOverUnLoad()
{
	TraceMessage("GameOver: Unload");
}


//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

