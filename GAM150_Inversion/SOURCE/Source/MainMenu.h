// ------------------------------------------------------------------------------
//
// File Name:	MainMenu.h
// Author(s):	Deni Van Winkle, Alex Phillips
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
	extern void MainMenuLoad();

	// Initialize the memory associated with the Stub game state.
	extern void MainMenuInit();

	// Update the Stub game state.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	extern void MainMenuUpdate(float dt);

	// Shutdown any memory associated with the Stub game state.
	extern void MainMenuShutdown();

	// Unload the resources associated with the Stub game state.
	extern void MainMenuUnLoad();

	/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif
