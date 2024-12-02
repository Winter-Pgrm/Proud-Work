//------------------------------------------------------------------------------
//
// File Name:	Death.c
// Author(s):	Brian Lu
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "AEEngine.h"
#include "Death.h"
#include "Player.h"
#include "Checkpoint.h"
#include "Hook.h"
#include "Gfx.h"


static int previous = 0;

static AEGfxVertexList * DeathMesh;

static AEGfxTexture * DeathTexture;

void deathCheck(PlayerPtr player, float x, float y, float dt)
{
	
	if (CharacterGetLives(PlayerGetCharacter(player)) == 0) //checks if the penguin has fallen and can't get up
	{														//should try life alert, I hear that helps sometimes
		PlayerSetDeathDuration(player, PlayerGetDeathDuration(player) - dt);
		HookReset();
		
		deathAnimation(player);

		if (PlayerGetDeathDuration(player) < 0)
		{
			//checkpoint
			PlayerSetXcoordinate(player, x);
			PlayerSetYcoordinate(player, y);

			PlayerSetDeathDuration(player, 15.0f); //resets deathduration
			CharacterSetLives(PlayerGetCharacter(player), 1); //rests to alive
			
			if (CharacterGetPrev(PlayerGetCharacter(player)) == 0) //blue
			{
				CharacterSetTexture(PlayerGetCharacter(player), "Assets/PenguinFramesBlue.png");
			}
			else if (CharacterGetPrev(PlayerGetCharacter(player)) == 1) //red
			{
				CharacterSetTexture(PlayerGetCharacter(player), "Assets/PenguinFrames.png");
			}
			
			HookReset();
		}
	}
}

void deathAnimation(PlayerPtr player)
{
	float flight = PlayerGetYcoordinate(player);
	flight += 2.0f; //movement up

	PlayerSetYcoordinate(player, flight);
	
}

void deathInit()
{
	AEGfxMeshStart();

	AEGfxTriAdd(
		-55.0f, -45.0f, 0x00FF00FF, 0.0f, 1.0f,
		55.0f, -45.0f, 0x00FFFF00, 1.0f, 1.0f,
		-55.0f, 45.0f, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		55.0f, -45.0f, 0x00FFFFFF, 1.0f, 1.0f,
		55.0f, 45.0f, 0x00FFFFFF, 1.0f, 0.0f,
		-55.0f, 45.0f, 0x00FFFFFF, 0.0f, 0.0f);

	DeathMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(DeathMesh, "Failed to create DeathMesh!");

	DeathTexture = AEGfxTextureLoad("Assets/NormalPenguin.png");
}

void deathUpdate(PlayerPtr player)
{
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTransparency(1.0f);
	AEGfxSetFullTransformWithZOrder(PlayerGetXcoordinate(player), PlayerGetYcoordinate(player), 2.0f, 0.0f, 1.0f, 1.0f);
	AEGfxTextureSet(DeathTexture, 0, 0);
	AEGfxMeshDraw(DeathMesh, AE_GFX_MDM_TRIANGLES);
}

void deathShutdown()
{
	AEGfxMeshFree(DeathMesh);
}

//creates a mesh
//get x and  y
//stop drawing player
//dt then stop drawing death and draw player