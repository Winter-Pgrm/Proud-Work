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

#include "stdafx.h"
#include "GameStateManager.h"
#include "GameStateTable.h"

/* Include all game state headers here. */
#include "DigipenLogo.h"
#include "MainMenu.h"
#include "GameStateLevel.h"
#include "Credits.h"
//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef void(*GameStateVoidFunctionPtr)();
typedef void(*GameStateDtFunctionPtr)(float dt);

typedef struct
{
	GameStateVoidFunctionPtr	gameStateLoad;		/* Pointer to a game state load function. */
	GameStateVoidFunctionPtr	gameStateInit;		/* Pointer to a game state initialization function. */
	GameStateDtFunctionPtr		gameStateUpdate;	/* Pointer to a game state update function. */
	GameStateVoidFunctionPtr	gameStateShutdown;	/* Pointer to a game state shutdown function. */
	GameStateVoidFunctionPtr	gameStateUnload;	/* Pointer to a game state unload function. */
	
} GameStateTableEntry;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

static const GameStateTableEntry GameStateTab[GsNum] =
{
	// Stub Game State - This is here as a placeholder only.
	//{ GameStateStubLoad, GameStateStubInit, GameStateStubUpdate, GameStateStubShutdown, GameStateStubUnload },

	// TODO: Add new game states here
	{ DigipenLogoLoad, DigipenLogoInit, DigipenLogoUpdate, DigipenLogoShutdown, DigipenLogoUnLoad },
	{ MainMenuLoad, MainMenuInit, MainMenuUpdate, MainMenuShutdown, MainMenuUnLoad },
    { GameStateLevelLoad, GameStateLevelInit, GameStateLevelUpdate, GameStateLevelShutdown, GameStateLevelUnload },
	{ CreditsLoad, CreditsInit, CreditsUpdate, CreditsShutdown, CreditsUnLoad },
};

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Determine if the game state is valid.
bool GameStateIsValid(GameStates gameState)
{
	return ((0 <= gameState) && (gameState < GsNum));
}

// Determine if the game state is a "special" game state.
bool GameStateIsSpecial(GameStates gameState)
{
	return ((gameState == GsRestart) || (gameState == GsQuit));
}

// Execute the Load function for the current game state.
void GameStateExecuteLoad(GameStates gameState)
{
	// First validate the game state and the function pointer.
	if (GameStateIsValid(gameState) &&
		((*GameStateTab[gameState].gameStateLoad) != NULL))
	{
		// Execute the Init function.
		(*GameStateTab[gameState].gameStateLoad)();
	}
}

// Execute the Init function for the current game state.
void GameStateExecuteInit(GameStates gameState)
{
	// First validate the game state and the function pointer.
	if (GameStateIsValid(gameState) &&
		((*GameStateTab[gameState].gameStateInit) != NULL))
	{
		// Execute the Init function.
		(*GameStateTab[gameState].gameStateInit)();
	}
}

// Execute the Update function for the current game state.
void GameStateExecuteUpdate(GameStates gameState, float dt)
{
	// First validate the game state and the function pointer.
	if (GameStateIsValid(gameState) &&
		((*GameStateTab[gameState].gameStateUpdate) != NULL))
	{
		// Execute the Update function.
		(*GameStateTab[gameState].gameStateUpdate)(dt);
	}
}

// Execute the Shutdown function for the current game state.
void GameStateExecuteShutdown(GameStates gameState)
{
	// First validate the game state and the function pointer.
	if (GameStateIsValid(gameState) &&
		((*GameStateTab[gameState].gameStateShutdown) != NULL))
	{
		// Execute the Shutdown function.
		(*GameStateTab[gameState].gameStateShutdown)();
	}
}

// Execute the Unload function for the current game state.
void GameStateExecuteUnload(GameStates gameState)
{
	// First validate the game state and the function pointer.
	if (GameStateIsValid(gameState) &&
		((*GameStateTab[gameState].gameStateUnload) != NULL))
	{
		// Execute the Init function.
		(*GameStateTab[gameState].gameStateUnload)();
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

