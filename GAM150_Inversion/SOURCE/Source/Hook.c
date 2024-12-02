//------------------------------------------------------------------------------
//
// File Name:	Hook.c
// Author(s):	Ian Gaither (ian.gaither)
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "AEEngine.h"
#include "Player.h"
#include "Collision.h"
#include "Gfx.h"
#include "Camera.h"
#include "Hook.h"

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

static float currentHookPositionX = 0;
static float currentHookPositionY = 0;

static float hookDestinationX = 0;
static float hookDestinationY = 0;

static float currentHookRadius = 0;

static const float hookTravelVelocity = 10.0f;

static bool hookIsActive = false;
static bool isAnchored = false;


//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

void HookBegin(PlayerPtr player)
{
	s32 mouseX = 0;
	s32 mouseY = 0;
	AEInputGetCursorPosition(&mouseX, &mouseY);

	AEGfxConvertScreenCoordinatesToWorld((float)mouseX, (float)mouseY, &hookDestinationX, &hookDestinationY);
	currentHookPositionX = PlayerGetXcoordinate(player);
	currentHookPositionY = PlayerGetYcoordinate(player);
	hookIsActive = true;
	HookInAir(true);
	if (hookDestinationY < PlayerGetYcoordinate(player))
	{
		HookReset();
	}
}

void HookReset()
{
	hookIsActive = false;
	isAnchored = false;
	HookInAir(false);
	currentHookPositionX = 0;
	currentHookPositionY = 0;
	hookDestinationX = 0;
	hookDestinationY = 0;
	currentHookRadius = 0;
}

void HookPhysicsUpdate(PlayerPtr player)
{
	float x = hookDestinationX - PlayerGetXcoordinate(player);
	float y = hookDestinationY - PlayerGetYcoordinate(player);
	AEVec2 playerDiffWorld;
	playerDiffWorld.x = x;
	playerDiffWorld.y = y;


	// normalize the direction vector
	float magnitudePlayerDiffWorld = sqrtf((playerDiffWorld.x * playerDiffWorld.x) + (playerDiffWorld.y * playerDiffWorld.y));

	float xx = playerDiffWorld.x / magnitudePlayerDiffWorld;
	float yy = playerDiffWorld.y / magnitudePlayerDiffWorld;
	AEVec2 normalizedPlayerDiffWorld;
	normalizedPlayerDiffWorld.x = xx;
	normalizedPlayerDiffWorld.y = yy;

	if (isAnchored == false)
	{
		// scale by the hook velocity

		float xxx = normalizedPlayerDiffWorld.x * hookTravelVelocity;
		float yyy = normalizedPlayerDiffWorld.y * hookTravelVelocity;
		AEVec2 hookSpeed;
		hookSpeed.x = xxx;
		hookSpeed.y = yyy;


		CollisionData finalData;
		HookCollision(currentHookPositionX, currentHookPositionY, hookSpeed.x, hookSpeed.y, &finalData);

		if (finalData.down == true)
		{
			hookSpeed.y = (f32)finalData.yColVel;
			hookSpeed.x = 0;
			isAnchored = true;
		}
		else if (finalData.up == true)
		{
			hookSpeed.y = (f32)finalData.yColVel;
			hookSpeed.x = 0;
			isAnchored = true;
		}

		if (finalData.left == true || finalData.right == true)
		{
			hookSpeed.x = (f32)finalData.xColVel;
			isAnchored = true;
		}

		currentHookPositionX += hookSpeed.x;
		currentHookPositionY += hookSpeed.y;
	}
	

	// update radius
	float xxxx = currentHookPositionX - PlayerGetXcoordinate(player);
	float yyyy = currentHookPositionY - PlayerGetYcoordinate(player);
	AEVec2 playerDiffWorldRadiusStuff;
	playerDiffWorldRadiusStuff.x = xxxx;
	playerDiffWorldRadiusStuff.y = yyyy;
	
	float magnitudePlayerDiffWorldRadius = sqrtf((playerDiffWorldRadiusStuff.x * playerDiffWorldRadiusStuff.x) + (playerDiffWorldRadiusStuff.y * playerDiffWorldRadiusStuff.y));
	currentHookRadius = magnitudePlayerDiffWorldRadius;
	if (currentHookRadius > 500)
	{
		HookReset();
	}
}

void HookMapToRadius(PlayerPtr player, float * velocityX, float * velocityY)
{
	//shift to zero
	float playerX = PlayerGetXcoordinate(player) - currentHookPositionX;
	float playerY = PlayerGetYcoordinate(player) - currentHookPositionY;

	//projected location
	playerX += *velocityX;
	playerY += *velocityY;

	//normalize projected location
	float normal = sqrtf(playerX * playerX + playerY * playerY);
	playerX /= normal;
	playerY /= normal;

	//scale by radius
	playerX *= currentHookRadius;
	playerY *= currentHookRadius;

	//shift back
	playerX += currentHookPositionX - PlayerGetXcoordinate(player);
	playerY += currentHookPositionY - PlayerGetYcoordinate(player);

	*velocityX = playerX;
	*velocityY = playerY;
}

float currentHookX()
{
	return currentHookPositionX;
}

float currentHookY()
{
	return currentHookPositionY;
}

float currentHookRad()
{
	return currentHookRadius;
}

bool hookActiveStatus()
{
	return hookIsActive;
}

bool hookAnchorStatus()
{
	return isAnchored;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

