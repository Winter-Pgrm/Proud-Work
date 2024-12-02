//------------------------------------------------------------------------------
//
// File Name:	DigipenLogo.c
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
#include "Soundfunctions.h"
#include "Cenematic.h"
#include "SnowEffect.h"

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
static struct AEGfxVertexList *LogoMesh;
static AEGfxTexture *LogoTexture;
static float LogoTimer = 3.0f;
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

void DigipenLogoLoad()
{
	TraceMessage("DigiPenLogo: Load");

	//playmusicBGMDigipenscreen();
}


void DigipenLogoInit()
{
	TraceMessage("DigiPenLogo: Init");

	LogoTexture = AEGfxTextureLoad("Assets/DigipenLogo.jpg");
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

	LogoMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(LogoMesh, "Failed to create LogoMesh!!");

	SnowInit();
}

void DigipenLogoUpdate(float dt)
{
	TraceMessage("DigiPenLogo: Update");
	AESysFrameStart();
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetFullTransformWithZOrder(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	AEGfxTextureSet(LogoTexture, 0, 0);
	AEGfxSetTransparency(LogoTimer);
	AEGfxMeshDraw(LogoMesh, AE_GFX_MDM_TRIANGLES);
	SnowEffect(dt);
	AESysFrameEnd();

	LogoTimer -= 0.01f;
	if (LogoTimer <= 0)
	{
		GameStateManagerSetNextState(GsMainMenu);
	}

}

void DigipenLogoShutdown()
{
	TraceMessage("DigiPenLogo: Shutdown");
	AEGfxMeshFree(LogoMesh);
	AEGfxTextureUnload(LogoTexture);
	Text1();
	SnowFree();
}


void DigipenLogoUnLoad()
{
	TraceMessage("DigiPenLogo: Unload");
}


//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

