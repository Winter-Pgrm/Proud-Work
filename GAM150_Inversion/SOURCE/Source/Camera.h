//------------------------------------------------------------------------------
//
// File Name:	Camera.c
// Author(s):	Brian Lu, Fengchao Xie
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright � 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

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

	//------------------------------------------------------------------------------
	// Public Variables:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Save initial camera position
	void CameraInit(PlayerPtr player);

	// Update the camera
	void CameraUpdate(float playerX, float playerY);

	// Reset the camera to the initial position (for reseting game)
	void CameraReset();

	void CameraResetOrigin();

	void CameraGetDelta(f32 * deltaCamX, f32 * deltaCamY);

	/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

