//------------------------------------------------------------------------------
//
// File Name:	GameStateManager.h
// Author(s):	Doug Schilling (dschilling)
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

#include "GameStateTable.h"

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

// Initialize the game state manager.
extern void GameStateManagerInit();

// Update the game state manager.
extern void GameStateManagerUpdate(float dt);

// Shutdown the game state manager.
extern void GameStateManagerShutdown();

// Determine if the current game state is being restarted.
extern bool GameStateManagerIsRestarting();

// Determine if the game is still running.
extern bool GameStateManagerIsRunning();

// Set the next game state to run.
extern void GameStateManagerSetNextState(GameStates nextState);

//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

