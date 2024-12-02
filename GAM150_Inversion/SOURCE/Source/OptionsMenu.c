//------------------------------------------------------------------------------
//
// File Name:	OptionsMenu.c
// Author(s):	Alex Phillips 
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//dont forget to free the mesh

#include "stdafx.h"
#include "AEEngine.h"
#include "OptionsMenu.h"
#include "Player.h"
#include "Commandlist.h"
#include "Soundfunctions.h"
#include "Trace.h"
#pragma warning(push)
#pragma warning(disable : 4201)
//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------
static  AEGfxVertexList *MainMenuNamenewMesh;
static AEGfxTexture *MainMenuNamenewTexture;
static struct AEGfxVertexList *MainMenuSoundsMesh;
static AEGfxTexture *MainMenuSoundsTexture;
static struct AEGfxVertexList *MainMenuSoundsPMesh;
static AEGfxTexture *MainMenuSoundsPTexture;
static struct AEGfxVertexList *MainMenuQuitMesh;
static AEGfxTexture *MainMenuQuitTexture;
static struct AEGfxVertexList *MainMenuQuitPMesh;
static AEGfxTexture *MainMenuQuitPTexture;
static struct AEGfxVertexList *MainMenuMMMesh;
static AEGfxTexture *MainMenuMMTexture;
static struct AEGfxVertexList *MainMenuMMPMesh;
static AEGfxTexture *MainMenuMMPTexture;
static struct AEGfxVertexList *MainMenuUNpauseMesh;
static AEGfxTexture *MainMenuUNpauseTexture;
static struct AEGfxVertexList *MainMenuUNpausePMesh;
static AEGfxTexture *MainMenuUNpausePTexture;
static struct AEGfxVertexList *MainMenuSoundoptionsMesh;
static AEGfxTexture *MainMenuSoundoptionsTexture;
//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
typedef struct point
{
	float mouseX ;
	float mouseY;

}pppp ;
//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
static pppp Cursorpoint = { 0,0 };
static int pressed = 0;
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------
static void screencurcorpressed();
// Initialize the ...

void optionsmenuinit()
{

	MainMenuSoundoptionsTexture = AEGfxTextureLoad("Assets\\sounds menu.png");
	AEGfxMeshStart();


	AEGfxTriAdd(
		-150, -150, 0x00FF00FF, 0.0f, 1.0f,
		150, -150, 0x00FFFF00, 1.0f, 1.0f,
		-150, 150, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		150, -150, 0x00FFFFFF, 1.0f, 1.0f,
		150, 150, 0x00FFFFFF, 1.0f, 0.0f,
		-150, 150, 0x00FFFFFF, 0.0f, 0.0f);

	MainMenuSoundoptionsMesh = AEGfxMeshEnd();


	MainMenuNamenewTexture = AEGfxTextureLoad("Assets\\options menu.png");
	AEGfxMeshStart();


	AEGfxTriAdd(
		-400, -350, 0x00FF00FF, 0.0f, 1.0f,
		400, -350, 0x00FFFF00, 1.0f, 1.0f,
		-400, 350, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		400, -350, 0x00FFFFFF, 1.0f, 1.0f,
		400, 350, 0x00FFFFFF, 1.0f, 0.0f,
		-400, 350, 0x00FFFFFF, 0.0f, 0.0f);

	MainMenuNamenewMesh = AEGfxMeshEnd();
//	AE_ASSERT_MESG(MainMenuNamenewMesh, "Failed to create LogoMesh!!");


	//button meshs
	MainMenuSoundsTexture = AEGfxTextureLoad("Assets\\menubutton2.png");
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

	MainMenuSoundsMesh = AEGfxMeshEnd();

	MainMenuSoundsPTexture = AEGfxTextureLoad("Assets\\menubutton2pressed.png");
	AEGfxMeshStart();
//	AE_ASSERT_MESG(MainMenuSoundsMesh, "Failed to create LogoMesh!!");
	AEGfxTriAdd(
		-130, -50, 0x00FF00FF, 0.0f, 1.0f,
		130, -50, 0x00FFFF00, 1.0f, 1.0f,
		-130, 50, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		130, -50, 0x00FFFFFF, 1.0f, 1.0f,
		130, 50, 0x00FFFFFF, 1.0f, 0.0f,
		-130, 50, 0x00FFFFFF, 0.0f, 0.0f);

	MainMenuSoundsPMesh = AEGfxMeshEnd();
//	AE_ASSERT_MESG(MainMenuSoundsPMesh, "Failed to create LogoMesh!!");


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

//	AE_ASSERT_MESG(MainMenuQuitMesh, "Failed to create LogoMesh!!");
	AEGfxTriAdd(
		-130, -50, 0x00FF00FF, 0.0f, 1.0f,
		130, -50, 0x00FFFF00, 1.0f, 1.0f,
		-130, 50, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		130, -50, 0x00FFFFFF, 1.0f, 1.0f,
		130, 50, 0x00FFFFFF, 1.0f, 0.0f,
		-130, 50, 0x00FFFFFF, 0.0f, 0.0f);

	MainMenuQuitPMesh = AEGfxMeshEnd();
//	AE_ASSERT_MESG(MainMenuQuitPMesh, "Failed to create LogoMesh!!");



	MainMenuMMTexture = AEGfxTextureLoad("Assets\\menubutton1.png");
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

	MainMenuMMMesh = AEGfxMeshEnd();


	MainMenuMMPTexture = AEGfxTextureLoad("Assets\\menubutton1pressed.png");
	AEGfxMeshStart();
//	AE_ASSERT_MESG(MainMenuMMPMesh, "Failed to create LogoMesh!!");
	AEGfxTriAdd(
		-130, -50, 0x00FF00FF, 0.0f, 1.0f,
		130, -50, 0x00FFFF00, 1.0f, 1.0f,
		-130, 50, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		130, -50, 0x00FFFFFF, 1.0f, 1.0f,
		130, 50, 0x00FFFFFF, 1.0f, 0.0f,
		-130, 50, 0x00FFFFFF, 0.0f, 0.0f);

	MainMenuMMPMesh = AEGfxMeshEnd();
//	AE_ASSERT_MESG(MainMenuMMPMesh, "Failed to create LogoMesh!!");

	MainMenuUNpauseTexture = AEGfxTextureLoad("Assets\\menubutton9.png");
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

	MainMenuUNpauseMesh = AEGfxMeshEnd();


	MainMenuUNpausePTexture = AEGfxTextureLoad("Assets\\menubutton9pressed.png");
	AEGfxMeshStart();
//	AE_ASSERT_MESG(MainMenuUNpauseMesh, "Failed to create LogoMesh!!");
	AEGfxTriAdd(
		-130, -50, 0x00FF00FF, 0.0f, 1.0f,
		130, -50, 0x00FFFF00, 1.0f, 1.0f,
		-130, 50, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		130, -50, 0x00FFFFFF, 1.0f, 1.0f,
		130, 50, 0x00FFFFFF, 1.0f, 0.0f,
		-130, 50, 0x00FFFFFF, 0.0f, 0.0f);

	MainMenuUNpausePMesh = AEGfxMeshEnd();
//	AE_ASSERT_MESG(MainMenuUNpauseMesh, "Failed to create LogoMesh!!");

}

void optionsMMinit()
{

	MainMenuNamenewTexture = AEGfxTextureLoad("Assets\\options menu.png");
	AEGfxMeshStart();


	AEGfxTriAdd(
		-400, -350, 0x00FF00FF, 0.0f, 1.0f,
		400, -350, 0x00FFFF00, 1.0f, 1.0f,
		-400, 350, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		400, -350, 0x00FFFFFF, 1.0f, 1.0f,
		400, 350, 0x00FFFFFF, 1.0f, 0.0f,
		-400, 350, 0x00FFFFFF, 0.0f, 0.0f);

	MainMenuNamenewMesh = AEGfxMeshEnd();
	//	AE_ASSERT_MESG(MainMenuNamenewMesh, "Failed to create LogoMesh!!");


	//button meshs
	MainMenuSoundsTexture = AEGfxTextureLoad("Assets\\menubutton11.png");
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

	MainMenuSoundsMesh = AEGfxMeshEnd();

	MainMenuSoundsPTexture = AEGfxTextureLoad("Assets\\menubutton11pressed.png");
	AEGfxMeshStart();
	//	AE_ASSERT_MESG(MainMenuSoundsMesh, "Failed to create LogoMesh!!");
	AEGfxTriAdd(
		-130, -50, 0x00FF00FF, 0.0f, 1.0f,
		130, -50, 0x00FFFF00, 1.0f, 1.0f,
		-130, 50, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		130, -50, 0x00FFFFFF, 1.0f, 1.0f,
		130, 50, 0x00FFFFFF, 1.0f, 0.0f,
		-130, 50, 0x00FFFFFF, 0.0f, 0.0f);

	MainMenuSoundsPMesh = AEGfxMeshEnd();
	//	AE_ASSERT_MESG(MainMenuSoundsPMesh, "Failed to create LogoMesh!!");





}





int Pausedstate(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	

	f32 camX, camY;
	AEGfxGetCamPosition(&camX, &camY);
	//AEGfxConvertScreenCoordinatesToWorld(camX, camY, &Pwordx, &Pwordy);

//	AESysFrameStart();
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	
	screencurcorpressed();

	//create mesh is causing to much memory to be alloced 

	
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetFullTransformWithZOrder(camX, camY, 0.0f, 0.0f, 1.0f, 1.0f);
	AEGfxTextureSet(MainMenuNamenewTexture, 0, 0);
	AEGfxSetTransparency(1.0f);


	
//	if ((Cursorpoint.mouseX >= camX - 400.0f && Cursorpoint.mouseX <= camX + 400.0f) && (Cursorpoint.mouseY >= camY - 350.0f && Cursorpoint.mouseY <= camY + 350.0f) )
	//{
	//	AEGfxSetTransparency(0.0f);
		
	//}
//	else
	//{
		

	//}
	AEGfxMeshDraw(MainMenuNamenewMesh, AE_GFX_MDM_TRIANGLES);
	if (((Cursorpoint.mouseX > camX - 350.0f  && Cursorpoint.mouseX < camX - 70.0f) && (Cursorpoint.mouseY > camY -50.0f  && Cursorpoint.mouseY <  camY + 50.0f )) || pressed == 1)
	{

		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetFullTransformWithZOrder(camX -200.0f, camY, 0.0f, 0.0f, 1.0f, 1.0f);
		AEGfxTextureSet(MainMenuUNpausePTexture, 0, 0);
		AEGfxSetTransparency(1.0f);
		AEGfxMeshDraw(MainMenuUNpausePMesh, AE_GFX_MDM_TRIANGLES);
		if (AEInputCheckTriggered(VK_LBUTTON) )
		{
			
			return false;

		
		}
		AEInputUpdate();
	}
	else
	{
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetFullTransformWithZOrder(camX - 200.0f, camY, 0.0f, 0.0f, 1.0f, 1.0f);
		AEGfxTextureSet(MainMenuUNpauseTexture, 0, 0);
		AEGfxSetTransparency(1.0f);
		AEGfxMeshDraw(MainMenuUNpauseMesh, AE_GFX_MDM_TRIANGLES);
	}


	if (((Cursorpoint.mouseX > camX + 70.0f  && Cursorpoint.mouseX < camX + 350.0f) && (Cursorpoint.mouseY > camY - 50.0f  && Cursorpoint.mouseY <  camY + 50.0f)) || pressed == 1)
	{

		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetFullTransformWithZOrder(camX + 200.0f, camY, 0.0f, 0.0f, 1.0f, 1.0f);
		AEGfxTextureSet(MainMenuSoundsPTexture, 0, 0);
		AEGfxSetTransparency(0.0f);
		AEGfxMeshDraw(MainMenuSoundsPMesh, AE_GFX_MDM_TRIANGLES);
		
	
	}
	else
	{
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetFullTransformWithZOrder(camX + 200.0f, camY, 0.0f, 0.0f, 1.0f, 1.0f);
		AEGfxTextureSet(MainMenuSoundsTexture, 0, 0);
		AEGfxSetTransparency(0.0f);
		AEGfxMeshDraw(MainMenuSoundsMesh, AE_GFX_MDM_TRIANGLES);
	}


	if (((Cursorpoint.mouseX > camX - 350.0f  && Cursorpoint.mouseX < camX - 70.0f) && (Cursorpoint.mouseY > camY - 240.0f  && Cursorpoint.mouseY <  camY - 140.0f)) || pressed == 1)
	{

		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetFullTransformWithZOrder(camX - 200.0f, camY - 190.0f, 0.0f, 0.0f, 1.0f, 1.0f);
		AEGfxTextureSet(MainMenuMMPTexture, 0, 0);
		AEGfxSetTransparency(1.0f);
		AEGfxMeshDraw(MainMenuUNpausePMesh, AE_GFX_MDM_TRIANGLES);
		if (AEInputCheckTriggered(VK_LBUTTON))
		{

			return 3;//returns that we want to retrun to MM 


		}
		AEInputUpdate();
	}
	else
	{
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetFullTransformWithZOrder(camX - 200.0f, camY - 190.0f, 0.0f, 0.0f, 1.0f, 1.0f);
		AEGfxTextureSet(MainMenuMMTexture, 0, 0);
		AEGfxSetTransparency(1.0f);
		AEGfxMeshDraw(MainMenuUNpauseMesh, AE_GFX_MDM_TRIANGLES);
	}

	if (((Cursorpoint.mouseX > camX + 70.0f  && Cursorpoint.mouseX < camX + 350.0f) && (Cursorpoint.mouseY > camY - 240.0f  && Cursorpoint.mouseY <  camY - 140.0f)) || pressed == 1)
	{

		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetFullTransformWithZOrder(camX + 200.0f, camY - 190.0f, 0.0f, 0.0f, 1.0f, 1.0f);
		AEGfxTextureSet(MainMenuQuitPTexture, 0, 0);
		AEGfxSetTransparency(1.0f);
		AEGfxMeshDraw(MainMenuQuitPMesh, AE_GFX_MDM_TRIANGLES);
		if (AEInputCheckTriggered(VK_LBUTTON))
		{

			return 4;//returns that we want to retrun to MM 


		}
		AEInputUpdate();
	}
	else
	{
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetFullTransformWithZOrder(camX + 200.0f, camY - 190.0f, 0.0f, 0.0f, 1.0f, 1.0f);
		AEGfxTextureSet(MainMenuQuitTexture, 0, 0);
		AEGfxSetTransparency(1.0f);
		AEGfxMeshDraw(MainMenuQuitMesh, AE_GFX_MDM_TRIANGLES);
	}


	
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetFullTransformWithZOrder(camX + 200.0f, camY + 100.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	AEGfxTextureSet(MainMenuSoundoptionsTexture, 0, 0);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(MainMenuSoundoptionsMesh, AE_GFX_MDM_TRIANGLES);
	if (AEInputCheckTriggered(VK_LEFT))
	{

	//	AEGfxMeshFree(MainMenuNamenewMesh);
	//	AEGfxTextureUnload(MainMenuNamenewTexture);
		return false;
	}
	else if (AEInputCheckTriggered(VK_DOWN))
	{


		return false;
	}
	else if (AEInputCheckTriggered('1'))
	{
		Musiccontrol(-.10f);
	}
	else if (AEInputCheckTriggered('2'))
	{

		Musiccontrol(-.01f);
	}
	else if (AEInputCheckTriggered('3'))
	{
		Musiccontrol(+.01f);
	}
	else if (AEInputCheckTriggered('4'))
	{
		Musiccontrol(+.10f);
	}
	else if (AEInputCheckTriggered('5'))
	{
		soundcontrol(-.10f);
	}
	else if (AEInputCheckTriggered('6'))
	{
		soundcontrol(-.01f);
	}
	else if (AEInputCheckTriggered('7'))
	{
		soundcontrol(.01f);
	}
	else if (AEInputCheckTriggered('8'))
	{
		soundcontrol(.10f);
	}
	else if (AEInputCheckTriggered('0'))
	{
		Pauseallsounds();
	}
	else
	{
		
	}
	return true;
}

void screencurcorpressed()
{
	s32 mouseX = 0;
	s32 mouseY = 0;
	AEInputGetCursorPosition(&mouseX, &mouseY);

	AEGfxConvertScreenCoordinatesToWorld((float)mouseX, (float)mouseY, &Cursorpoint.mouseX, &Cursorpoint.mouseY);

}

void freeoptions()
{
	
	pressed = 0;

	AEGfxTextureUnload(MainMenuSoundsTexture);
	AEGfxMeshFree(MainMenuSoundsMesh);
	AEGfxTextureUnload(MainMenuSoundsPTexture);
	AEGfxMeshFree(MainMenuSoundsPMesh);

	AEGfxTextureUnload(MainMenuNamenewTexture);
	AEGfxMeshFree(MainMenuNamenewMesh);
	AEGfxTextureUnload(MainMenuUNpauseTexture);
	AEGfxMeshFree(MainMenuUNpauseMesh);
	AEGfxTextureUnload(MainMenuUNpausePTexture);
	AEGfxMeshFree(MainMenuUNpausePMesh);
	AEGfxTextureUnload(MainMenuQuitTexture);
	AEGfxMeshFree(MainMenuQuitMesh);
	AEGfxTextureUnload(MainMenuQuitPTexture);
	AEGfxMeshFree(MainMenuQuitPMesh);
	AEGfxTextureUnload(MainMenuMMTexture);
	AEGfxMeshFree(MainMenuMMMesh);
	AEGfxTextureUnload(MainMenuMMPTexture);
	AEGfxMeshFree(MainMenuMMPMesh);
	AEGfxTextureUnload(MainMenuSoundoptionsTexture);
	AEGfxMeshFree(MainMenuSoundoptionsMesh);

}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

