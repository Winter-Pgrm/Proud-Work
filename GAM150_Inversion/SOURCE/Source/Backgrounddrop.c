//------------------------------------------------------------------------------
//
// File Name:	Stub.c
// Author(s):	Doug Schilling (dschilling)
// Project:		MyGame
// Course:		GAM150S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Backgrounddrop.h"
#include "AEEngine.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------
static struct AEGfxVertexList *LogoMesh;
static AEGfxTexture *LogoTexture;


//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Initialize the ...
void makebackdrop()
{
	LogoTexture = AEGfxTextureLoad("Assets/backdrop.bmp");
	AEGfxMeshStart();

	// This shape has 2 triangles

	AEGfxTriAdd(
		-10000, -6000, 0x00FF00FF, 0.0f, 1.0f,
		10000, -6000, 0x00FFFF00, 1.0f, 1.0f,
		-10000, 6000, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		10000, -6000, 0x00FFFFFF, 1.0f, 1.0f,
		10000, 6000, 0x00FFFFFF, 1.0f, 0.0f,
		-10000, 6000, 0x00FFFFFF, 0.0f, 0.0f);

	LogoMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(LogoMesh, "Failed to create LogoMesh!!");

	AESysFrameStart();
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetFullTransformWithZOrder(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	AEGfxTextureSet(LogoTexture, 0, 0);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(LogoMesh, AE_GFX_MDM_TRIANGLES);
	AESysFrameEnd();

}
void BGIcleear()
{
	AEGfxMeshFree(LogoMesh);
	AEGfxTextureUnload(LogoTexture);
}


//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

