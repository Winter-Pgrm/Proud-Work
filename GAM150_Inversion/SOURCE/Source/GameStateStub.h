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

// Load the resources associated with the Stub game state.
extern void GameStateStubLoad();

// Initialize the memory associated with the Stub game state.
extern void GameStateStubInit();

// Update the Stub game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
extern void GameStateStubUpdate(float dt);

// Shutdown any memory associated with the Stub game state.
extern void GameStateStubShutdown();

// Unload the resources associated with the Stub game state.
extern void GameStateStubUnload();

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

