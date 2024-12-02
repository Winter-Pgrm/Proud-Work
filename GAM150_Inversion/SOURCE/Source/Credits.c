//------------------------------------------------------------------------------
//
// File Name:	Credits.c
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
static struct AEGfxVertexList *CreditsMesh;
static AEGfxTexture *CreditsTexture;
float Timer = 0;
int CurrentCredit = 1;
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

void CreditsLoad()
{
	playmusicBGMPause(SongMainMenu);
	TraceMessage("Credits: Load");
}


void CreditsInit()
{
	TraceMessage("Credits: Init");

	// Needs the art for this
	CreditsTexture = AEGfxTextureLoad("Assets/Credits1.PNG");
	AEGfxMeshStart();

	// This shape has 2 triangles

	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00FF00FF, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00FFFF00, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00FFFFFF, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00FFFFFF, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00FFFFFF, 0.0f, 0.0f);

	CreditsMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(CreditsMesh, "Failed to create LogoMesh!!");
	SnowInit();
}

void CreditsUpdate(float dt)
{
	TraceMessage("Credits: Update");
	AESysFrameStart();
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetFullTransformWithZOrder(0.0f, 0.0f, 0.0f, 0.0f, 2 * AEGfxGetWinMaxX(), 2 * AEGfxGetWinMaxY());
	AEGfxTextureSet(CreditsTexture, 0, 0);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(CreditsMesh, AE_GFX_MDM_TRIANGLES);
	SnowEffect(dt);
	AESysFrameEnd();
	
	AEInputUpdate();

	if (Timer > 15 && CurrentCredit == 1)
	{
		AEGfxTextureUnload(CreditsTexture);
		CreditsTexture = AEGfxTextureLoad("Assets/Credits2.PNG");
		++CurrentCredit;
	}
	if (Timer > 30 && CurrentCredit == 2)
	{
		AEGfxTextureUnload(CreditsTexture);
		CreditsTexture = AEGfxTextureLoad("Assets/Credits3.PNG");
		++CurrentCredit;
	}
	if (Timer > 45 && CurrentCredit == 3)
	{
		AEGfxTextureUnload(CreditsTexture);
		CreditsTexture = AEGfxTextureLoad("Assets/Credits4.PNG");
		++CurrentCredit;
	}
	if (Timer > 60 && CurrentCredit == 4)
	{
		AEGfxTextureUnload(CreditsTexture);
		CreditsTexture = AEGfxTextureLoad("Assets/Credits5.PNG");
		++CurrentCredit;
	}
	if (Timer > 80 && CurrentCredit == 5)
	{
		AEGfxTextureUnload(CreditsTexture);
		CreditsTexture = AEGfxTextureLoad("Assets/Ending.PNG");
		++CurrentCredit;
	}
	if (Timer > 95 && CurrentCredit == 6 || AEInputCheckTriggered(VK_LBUTTON) || AEInputCheckTriggered(' ') || AEInputCheckTriggered(VK_RETURN))
	{
		GameStateManagerSetNextState(GsMainMenu);
		++CurrentCredit;
		Timer = 0;
	}

	Timer += dt * 0.5f;
}

void CreditsShutdown()
{
	TraceMessage("Credits: Shutdown");
	AEGfxMeshFree(CreditsMesh);
	AEGfxTextureUnload(CreditsTexture);
	CurrentCredit = 1;
	SnowFree();
}


void CreditsUnLoad()
{
	TraceMessage("Credits: Unload");
}


//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

