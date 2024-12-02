//------------------------------------------------------------------------------
//
// File Name:	GameStateTable.h
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

//------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{	/* Assume C declarations for C++ */
#endif

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

typedef enum
{
	/* Special Game States */
	GsPause = -4,
	GsQuit = -3,
	GsRestart = -2,
	GsInvalid = -1,
	

	/* Normal Game States: */
	//GsStub,			// This is here as a placeholder only.
	// TODO: Add new game states here.
	GsLogo,
	GsMainMenu,
	GsLevel1,
	GsCredits,
	/* Bookkeeping States: */
	GsNum,
	GsLast = GsNum - 1,

	/* Specify the initial game state */
	GsInitial = GsLogo,

} GameStates;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Determine if the game state is valid.
extern bool GameStateIsValid(GameStates gameState);

// Determine if the game state is a "special" game state.
extern bool GameStateIsSpecial(GameStates gameState);

// Execute the Load function for the current game state.
extern void GameStateExecuteLoad(GameStates gameState);

// Execute the Init function for the current game state.
extern void GameStateExecuteInit(GameStates gameState);

// Execute the Update function for the current game state.
extern void GameStateExecuteUpdate(GameStates gameState, float dt);

// Execute the Shutdown function for the current game state.
extern void GameStateExecuteShutdown(GameStates gameState);

// Execute the Unload function for the current game state.
extern void GameStateExecuteUnload(GameStates gameState);

//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

