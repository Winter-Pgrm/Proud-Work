//------------------------------------------------------------------------------
//
// File Name:	CheckpointFlag.c
// Author(s):	Brian Lu
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "CheckpointFlag.h"

static AEGfxVertexList * FlagMesh;
static AEGfxVertexList * FlagMesh2;
static AEGfxTexture * FlagTexture;
static AEGfxTexture * FlagTexture2;

void FlagInit()
{
	AEGfxMeshStart();

	AEGfxTriAdd(
		-120.0f, -57.0f, 0x00FF00FF, 0.0f, 1.0f,
		120.0f, -57.0f, 0x00FFFF00, 1.0f, 1.0f,
		-120.0f, 60.0f, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		120.0f, -57.0f, 0x00FFFFFF, 1.0f, 1.0f,
		120.0f, 60.0f, 0x00FFFFFF, 1.0f, 0.0f,
		-120.0f, 60.0f, 0x00FFFFFF, 0.0f, 0.0f);

	FlagMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(FlagMesh, "Failed to create FlagMesh!");

	FlagTexture = AEGfxTextureLoad("Assets/flag.png");
}

void FlagInit2()
{
	AEGfxMeshStart();

	AEGfxTriAdd(
		-120.0f, -57.0f, 0x00FF00FF, 0.0f, 1.0f,
		120.0f, -57.0f, 0x00FFFF00, 1.0f, 1.0f,
		-120.0f, 60.0f, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		120.0f, -57.0f, 0x00FFFFFF, 1.0f, 1.0f,
		120.0f, 60.0f, 0x00FFFFFF, 1.0f, 0.0f,
		-120.0f, 60.0f, 0x00FFFFFF, 0.0f, 0.0f);

	FlagMesh2 = AEGfxMeshEnd();
	AE_ASSERT_MESG(FlagMesh2, "Failed to create FlagMesh2!");

	FlagTexture2 = AEGfxTextureLoad("Assets/flag.png");

}

void SetFlag1Unclear()
{
	FlagTexture = AEGfxTextureLoad("Assets/flag.png");
}

void SetFlag2Unclear()
{
	FlagTexture2 = AEGfxTextureLoad("Assets/flag.png");
}

void SetFlag1Clear()
{
	FlagTexture = AEGfxTextureLoad("Assets/flagClear.png");
}

void SetFlag2Clear()
{
	FlagTexture2 = AEGfxTextureLoad("Assets/flagClear.png");
}

void SetFlag1Update(float x, float y)
{
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetFullTransformWithZOrder(x, y, 1.0f, 0.0f, 1.0f, 1.0f);
	AEGfxTextureSet(FlagTexture, 0, 0);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(FlagMesh, AE_GFX_MDM_TRIANGLES);
}

void SetFlag2Update(float x, float y)
{
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetFullTransformWithZOrder(x, y, 1.0f, 0.0f, 1.0f, 1.0f);
	AEGfxTextureSet(FlagTexture2, 0, 0);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(FlagMesh2, AE_GFX_MDM_TRIANGLES);
}

void FlagShutDown()
{
	AEGfxMeshFree(FlagMesh);
	AEGfxMeshFree(FlagMesh2);
}