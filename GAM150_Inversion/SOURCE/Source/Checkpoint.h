//------------------------------------------------------------------------------
//
// File Name:	Checkpoint.h
// Author(s):	Alex Phillips
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "Player.h"
//------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
	/* Assume C declarations for C++ */
#endif

	//------------------------------------------------------------------------------
	// Public Consts:
	//------------------------------------------------------------------------------
	// Pointer to a SpriteSource structure.

	//------------------------------------------------------------------------------
	// Public Structures:
	//------------------------------------------------------------------------------
	typedef struct Checkpointpoint
	{


		// The time remaining for the current frame.
		float x;

		// The amount of time to display each frame.
		// (Used only when playing simple animations (0 .. numFrame).)
		float y;



	}CPPoint;
	//------------------------------------------------------------------------------
	// Public Variables:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Initialize the ...
	CPPoint  Makecheckpoint(const float CurrentX, const float CurrentY);


	CPPoint  Checkpointlocationcheck(float CurrentX, float CurrentY, const float * checkpointarray, CPPoint  current);
	float getpointx(CPPoint  holder);
	float getpointy(CPPoint  holder);
	int goalpoint();
	AEVec2 *checkifcheckpointertriggered(float CurrentX, float CurrentY, float *checkpointarray, PlayerPtr player);
	void checkthecheckpoints(float *checkpointarray);
	bool checkifgoalpoiunt(float CurrentX, float CurrentY);
	void flagsbuilder(float *checkpointarray);
	/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

