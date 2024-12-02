//------------------------------------------------------------------------------
//
// File Name:	Collision.h
// Author(s):	Ian Gaither ian.gaither
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

#include "LevelManager.h"

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Player.h"

//------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
	/* Assume C declarations for C++ */
#endif

	//------------------------------------------------------------------------------
	// Public Consts:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Structures:
	//------------------------------------------------------------------------------

	typedef struct CollisionData
	{
		bool up;
		bool down;
		bool left;
		bool right;
		int yColVel;
		int xColVel;
		bool hitLightning;
	} CollisionData;

	//------------------------------------------------------------------------------
	// Public Variables:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	void CollisionInit();

	void Inversion(PlayerPtr player);

	void PlayerCollision(PlayerPtr player, float xvelocity, float yvelocity, CollisionData * finalData);

	void HookCollision(float currentHookPositionX, float currentHookPositionY, float hookSpeedX, float hookSpeedY, CollisionData * finalData);

	/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

