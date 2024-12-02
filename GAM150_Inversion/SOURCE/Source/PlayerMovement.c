//------------------------------------------------------------------------------
//
// File Name:	PlayerMovement.c
// Author(s):	Brian Lu
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "AEEngine.h"
#include "stdafx.h"
#include "Player.h"
#include "Physics.h"
#include "PlayerMovement.h"

static float frameDelay = 5.0f;
static int previousFrame = 0;
static int frameDirection = 1; //1 or -1

void PlayerMovement(PlayerPtr player, float dt)
{
	int OffSet = PlayerGetCurrentTextureOffset(player);

	frameDelay -= dt;

	if (frameDelay <= 0)
	{
		if (getXVelocity() == 0.0f || getYVelocity() != 0.0f)
		{
			frameDirection = 1;
			PlayerSetCurrentTextureOffset(player, 2); //idle frame
		}
		else if (OffSet == 4)
		{
			frameDirection = -1;
			PlayerSetCurrentTextureOffset(player, 3);
		}
		else if (OffSet == 0)
		{
			frameDirection = 1;
			PlayerSetCurrentTextureOffset(player, 1);
		}
		else
		{
			PlayerSetCurrentTextureOffset(player, frameDirection + OffSet);
		}

		frameDelay = 5.0f;
	}
}