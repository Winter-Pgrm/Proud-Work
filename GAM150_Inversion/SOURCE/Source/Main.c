//------------------------------------------------------------------------------
//
// File Name:	Stub.c
// Author(s):	Alexander Phillips
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Engine.h"
#include "GameStateManager.h"

//------------------------------------------------------------------------------
// Main Function:
//------------------------------------------------------------------------------

int main(void)
{
	// Change in time (in seconds) since the last game loop.
	// A framerate controller is not required for this assignment.
	float dt = .16f;

	// Initialize the game engine.
	EngineInit();

	// MAIN LOOP: Do not exit until instructed to do so by the game state manager (GSM).
	while (GameStateManagerIsRunning())
	{
		// Update the game engine.
		EngineUpdate(dt);
	}

	// Shutdown the game engine.
	EngineShutdown();

	return 0;
}