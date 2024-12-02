//------------------------------------------------------------------------------
//
// File Name:	MainMenu.c
// Author(s):	Deni Van Winkle, Alex Phillips
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "GameStateManager.h"
#include "Trace.h"
#include "Commandlist.h"
#include "Soundfunctions.h"
#include "SnowEffect.h"
#include "OptionsMenu.h"
#include "Camera.h"
// ------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------
static struct AEGfxVertexList *MainMenuMesh;
static AEGfxTexture *MainMenuTexture;
static struct AEGfxVertexList *MainMenuTopMesh;
static AEGfxTexture *MainMenuTopTexture;
static struct AEGfxVertexList *MainMenuNameMesh;
static AEGfxTexture *MainMenuNameTexture;
static struct AEGfxVertexList *MainMenuNamenewMesh;
static AEGfxTexture *MainMenuNamenewTexture;
static struct AEGfxVertexList *MainMenuQuitMesh;
static AEGfxTexture *MainMenuQuitTexture;
static struct AEGfxVertexList *MainMenuQuitPMesh;
static AEGfxTexture *MainMenuQuitPTexture;
static struct AEGfxVertexList *MainMenuOptionsMesh;
static AEGfxTexture *MainMenuOptionsTexture;
static struct AEGfxVertexList *MainMenuOptionsPMesh;
static AEGfxTexture *MainMenuOptionsPTexture;
static struct AEGfxVertexList *MainMenuCreditsMesh;
static AEGfxTexture *MainMenuCreditsTexture;
static struct AEGfxVertexList *MainMenuCreditsPMesh;
static AEGfxTexture *MainMenuCreditsPTexture;
//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
float transparency = 1.0f;
static int  selectflag = 0;
static bool  paused = false;
static bool checkpaused = false;
static int pressed = 0;
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

void MainMenuLoad()
{
	transparency = 1.0f;
	TraceMessage("MainMenu: Load");
	//playmusicBGMPause(SongDigipenlogo);
//	optionsmenuinit();
	playmusicBGMMainmenu();
	CameraResetOrigin();
}


void MainMenuInit()
{
	pressed = 0;
	SnowInit();
	TraceMessage("MainMenu: Init");
	paused = false;
	 checkpaused = false;
	MainMenuTexture = AEGfxTextureLoad("Assets\\bgwabordered.png");
	AEGfxMeshStart();

	// This shape has 2 triangles

	AEGfxTriAdd(
		-640, -500, 0x00FF00FF, 0.0f, 1.0f,
		640, -500, 0x00FFFF00, 1.0f, 1.0f,
		-640, 500, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		640, -500, 0x00FFFFFF, 1.0f, 1.0f,
		640, 500, 0x00FFFFFF, 1.0f, 0.0f,
		-640, 500, 0x00FFFFFF, 0.0f, 0.0f);

	MainMenuMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(MainMenuMesh, "Failed to create LogoMesh!!");

	//button meshs
	MainMenuTopTexture = AEGfxTextureLoad("Assets\\menubutton3.png");
	AEGfxMeshStart();

	// This shape has 2 triangles

	AEGfxTriAdd(
		-130, -50, 0x00FF00FF, 0.0f, 1.0f,
		130, -50, 0x00FFFF00, 1.0f, 1.0f,
		-130,50, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		130, -50, 0x00FFFFFF, 1.0f, 1.0f,
		130, 50, 0x00FFFFFF, 1.0f, 0.0f,
		-130, 50, 0x00FFFFFF, 0.0f, 0.0f);

	MainMenuTopMesh = AEGfxMeshEnd();

	MainMenuNameTexture = AEGfxTextureLoad("Assets\\menubutton3pressed.png");
	AEGfxMeshStart();
	AE_ASSERT_MESG(MainMenuMesh, "Failed to create LogoMesh!!");
	AEGfxTriAdd(
		-130, -50, 0x00FF00FF, 0.0f, 1.0f,
		130, -50, 0x00FFFF00, 1.0f, 1.0f,
		-130, 50, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		130, -50, 0x00FFFFFF, 1.0f, 1.0f,
		130, 50, 0x00FFFFFF, 1.0f, 0.0f,
		-130, 50, 0x00FFFFFF, 0.0f, 0.0f);

	MainMenuNameMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(MainMenuMesh, "Failed to create LogoMesh!!");


	MainMenuQuitTexture = AEGfxTextureLoad("Assets\\menubutton5.png");
	AEGfxMeshStart();

	// This shape has 2 triangles

	AEGfxTriAdd(
		-130, -50, 0x00FF00FF, 0.0f, 1.0f,
		130, -50, 0x00FFFF00, 1.0f, 1.0f,
		-130, 50, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		130, -50, 0x00FFFFFF, 1.0f, 1.0f,
		130, 50, 0x00FFFFFF, 1.0f, 0.0f,
		-130, 50, 0x00FFFFFF, 0.0f, 0.0f);

	MainMenuQuitMesh = AEGfxMeshEnd();

	
	MainMenuQuitPTexture = AEGfxTextureLoad("Assets\\menubutton5pressed.png");
	AEGfxMeshStart();
	AE_ASSERT_MESG(MainMenuMesh, "Failed to create LogoMesh!!");
	AEGfxTriAdd(
		-130, -50, 0x00FF00FF, 0.0f, 1.0f,
		130, -50, 0x00FFFF00, 1.0f, 1.0f,
		-130, 50, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		130, -50, 0x00FFFFFF, 1.0f, 1.0f,
		130, 50, 0x00FFFFFF, 1.0f, 0.0f,
		-130, 50, 0x00FFFFFF, 0.0f, 0.0f);

	MainMenuQuitPMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(MainMenuMesh, "Failed to create LogoMesh!!");

	
	
	MainMenuOptionsTexture = AEGfxTextureLoad("Assets\\menubutton2.png");
	AEGfxMeshStart();

	// This shape has 2 triangles

	AEGfxTriAdd(
		-130, -50, 0x00FF00FF, 0.0f, 1.0f,
		130, -50, 0x00FFFF00, 1.0f, 1.0f,
		-130, 50, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		130, -50, 0x00FFFFFF, 1.0f, 1.0f,
		130, 50, 0x00FFFFFF, 1.0f, 0.0f,
		-130, 50, 0x00FFFFFF, 0.0f, 0.0f);

	MainMenuOptionsMesh = AEGfxMeshEnd();


	MainMenuOptionsPTexture = AEGfxTextureLoad("Assets\\menubutton2pressed.png");
	AEGfxMeshStart();
	AE_ASSERT_MESG(MainMenuMesh, "Failed to create LogoMesh!!");
	AEGfxTriAdd(
		-130, -50, 0x00FF00FF, 0.0f, 1.0f,
		130, -50, 0x00FFFF00, 1.0f, 1.0f,
		-130, 50, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		130, -50, 0x00FFFFFF, 1.0f, 1.0f,
		130, 50, 0x00FFFFFF, 1.0f, 0.0f,
		-130, 50, 0x00FFFFFF, 0.0f, 0.0f);

	MainMenuOptionsPMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(MainMenuMesh, "Failed to create LogoMesh!!");

	MainMenuCreditsTexture = AEGfxTextureLoad("Assets\\menubutton4.png");
	AEGfxMeshStart();

	// This shape has 2 triangles

	AEGfxTriAdd(
		-130, -50, 0x00FF00FF, 0.0f, 1.0f,
		130, -50, 0x00FFFF00, 1.0f, 1.0f,
		-130, 50, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		130, -50, 0x00FFFFFF, 1.0f, 1.0f,
		130, 50, 0x00FFFFFF, 1.0f, 0.0f,
		-130, 50, 0x00FFFFFF, 0.0f, 0.0f);

	MainMenuCreditsMesh = AEGfxMeshEnd();


	MainMenuCreditsPTexture = AEGfxTextureLoad("Assets\\menubutton4pressed.png");
	AEGfxMeshStart();
	AE_ASSERT_MESG(MainMenuMesh, "Failed to create LogoMesh!!");
	AEGfxTriAdd(
		-130, -50, 0x00FF00FF, 0.0f, 1.0f,
		130, -50, 0x00FFFF00, 1.0f, 1.0f,
		-130, 50, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		130, -50, 0x00FFFFFF, 1.0f, 1.0f,
		130, 50, 0x00FFFFFF, 1.0f, 0.0f,
		-130, 50, 0x00FFFFFF, 0.0f, 0.0f);

	MainMenuCreditsPMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(MainMenuMesh, "Failed to create LogoMesh!!");

	MainMenuNamenewTexture = AEGfxTextureLoad("Assets\\MM.png");
	AEGfxMeshStart();

	AE_ASSERT_MESG(MainMenuMesh, "Failed to create LogoMesh!!");
	AEGfxTriAdd(
		-400, -350, 0x00FF00FF, 0.0f, 1.0f,
		400, -350, 0x00FFFF00, 1.0f, 1.0f,
		-400, 350, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		400, -350, 0x00FFFFFF, 1.0f, 1.0f,
		400, 350, 0x00FFFFFF, 1.0f, 0.0f,
		-400, 350, 0x00FFFFFF, 0.0f, 0.0f);

	MainMenuNamenewMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(MainMenuMesh, "Failed to create LogoMesh!!");
}

void MainMenuUpdate(float dt)
{

	TraceMessage("MainMenu: Update");
	TraceMessage("DigiPenLogo: Update");
	
	AESysFrameStart();
	AEInputUpdate();
	s32 x, y; 
	AEInputGetCursorPosition(&x, &y);

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetFullTransformWithZOrder(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	AEGfxTextureSet(MainMenuTexture, 0, 0);
	AEGfxSetTransparency(transparency);
	AEGfxMeshDraw(MainMenuMesh, AE_GFX_MDM_TRIANGLES);


	SnowEffect(dt);


	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetFullTransformWithZOrder(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	AEGfxTextureSet(MainMenuNamenewTexture, 0, 0);
	AEGfxSetTransparency(transparency);
	AEGfxMeshDraw(MainMenuNamenewMesh, AE_GFX_MDM_TRIANGLES);


	
	
	if (checkpaused == FALSE)
	{


		paused = FALSE;

		if (((x > 310 && x < 570) && (y > 330 && y < 460)) || pressed == 1)
		{

			AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
			AEGfxSetFullTransformWithZOrder(-200.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f);
			AEGfxTextureSet(MainMenuNameTexture, 0, 0);
			AEGfxSetTransparency(transparency);
			AEGfxMeshDraw(MainMenuNameMesh, AE_GFX_MDM_TRIANGLES);
			if (AEInputCheckTriggered(VK_LBUTTON) || transparency < 1)
			{
				pressed = 1;
				if (selectflag == 0)
				{
					selectflag = 1;
					playsoundMainMenuselectiontop();
				}
				if (transparency <= 0)
				{
					GameStateManagerSetNextState(GsLevel1);
					selectflag = 0;
				}

				transparency -= 0.01f;
			}
		}
		else
		{
			AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
			AEGfxSetFullTransformWithZOrder(-200.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f);
			AEGfxTextureSet(MainMenuTopTexture, 0, 0);
			AEGfxSetTransparency(transparency);
			AEGfxMeshDraw(MainMenuTopMesh, AE_GFX_MDM_TRIANGLES);
		}
		if (((x > 710 && x < 970) && (y > 330 && y < 460)) || pressed == 2)
		{
			AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
			AEGfxSetFullTransformWithZOrder(200.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f);
			AEGfxTextureSet(MainMenuQuitPTexture, 0, 0);
			AEGfxSetTransparency(transparency);
			AEGfxMeshDraw(MainMenuQuitPMesh, AE_GFX_MDM_TRIANGLES);

			if (AEInputCheckTriggered(VK_LBUTTON))
			{
				GameStateManagerSetNextState(GsQuit);
			}
		}
		else
		{
			AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
			AEGfxSetFullTransformWithZOrder(200.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f);
			AEGfxTextureSet(MainMenuQuitTexture, 0, 0);
			AEGfxSetTransparency(transparency);
			AEGfxMeshDraw(MainMenuQuitMesh, AE_GFX_MDM_TRIANGLES);
		}


		

		if (((x > 710 && x < 970) && (y > 520 && y < 650)) || pressed == 4)
		{
			AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
			AEGfxSetFullTransformWithZOrder(200.0f, -190.0f, 0.0f, 0.0f, 1.0f, 1.0f);
			AEGfxTextureSet(MainMenuCreditsPTexture, 0, 0);
			AEGfxSetTransparency(transparency);
			AEGfxMeshDraw(MainMenuCreditsPMesh, AE_GFX_MDM_TRIANGLES);
			if (AEInputCheckTriggered(VK_LBUTTON))
			{
				GameStateManagerSetNextState(GsCredits);//for credits 
			}
		}
		else
		{
			AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
			AEGfxSetFullTransformWithZOrder(200.0f, -190.0f, 0.0f, 0.0f, 1.0f, 1.0f);
			AEGfxTextureSet(MainMenuCreditsTexture, 0, 0);
			AEGfxSetTransparency(transparency);
			AEGfxMeshDraw(MainMenuCreditsMesh, AE_GFX_MDM_TRIANGLES);
		}
	}

	if (paused == TRUE)
	{

		checkpaused = Pausedstate(dt);
		if (checkpaused == FALSE)
			pressed = 0;
	}
	AESysFrameEnd();

}

void MainMenuShutdown()
{
	TraceMessage("MainMenu: Shutdown");
	AEGfxMeshFree(MainMenuMesh);
	AEGfxTextureUnload(MainMenuTexture);
	AEGfxMeshFree(MainMenuTopMesh);
	AEGfxTextureUnload(MainMenuNameTexture);
	AEGfxMeshFree(MainMenuNameMesh);
	AEGfxTextureUnload(MainMenuTopTexture);
	AEGfxMeshFree(MainMenuNamenewMesh);
	AEGfxTextureUnload(MainMenuNamenewTexture);
	
	AEGfxTextureUnload(MainMenuQuitTexture);
	AEGfxMeshFree(MainMenuQuitMesh);
	AEGfxTextureUnload(MainMenuQuitPTexture);
	AEGfxMeshFree(MainMenuQuitPMesh);
	AEGfxTextureUnload(MainMenuOptionsTexture);
	AEGfxMeshFree(MainMenuOptionsMesh);
	AEGfxTextureUnload(MainMenuOptionsPTexture);
	AEGfxMeshFree(MainMenuOptionsPMesh);
	AEGfxTextureUnload(MainMenuCreditsTexture);
	AEGfxMeshFree(MainMenuCreditsMesh);
	AEGfxTextureUnload(MainMenuCreditsPTexture);
	AEGfxMeshFree(MainMenuCreditsPMesh);
	transparency = 1;
	//freeoptions();

	SnowFree();
}


void MainMenuUnLoad()
{
	TraceMessage("MainMenu: Unload");

}


//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------