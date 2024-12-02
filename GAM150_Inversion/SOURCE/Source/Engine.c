//------------------------------------------------------------------------------
//
// File Name:	Engine.c
// Author(s):	Doug Schilling (dschilling)
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Engine.h"
#include "GameStateManager.h"
#include "Trace.h"
#include "AEEngine.h"
#include "Soundfunctions.h"

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

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Initialize the game engine.
void EngineInit()
{
	//--------------------------------------------------------------------------
	// NOTE: Certain modules need to be initialized first.
	//--------------------------------------------------------------------------

	// Initialize the Tracing/Logging module.
	TraceInit();

	TraceMessage("Engine: Init");
	// Initialize the system
		AESysInitInfo sysInitInfo;
	sysInitInfo.mCreateWindow = 1;
	sysInitInfo.mWindowHandle = NULL;
	//sysInitInfo.mAppInstance = instanceH;
	sysInitInfo.mShow = 1;
	sysInitInfo.mWinWidth = 1280;
	sysInitInfo.mWinHeight = 800;
	sysInitInfo.mCreateConsole = 1;
	sysInitInfo.mMaxFrameRate = 60;
	sysInitInfo.mpWinCallBack = NULL;
	sysInitInfo.mClassStyle = CS_HREDRAW | CS_VREDRAW;
	sysInitInfo.mWindowStyle = WS_OVERLAPPEDWINDOW;
	sysInitInfo.mHandleWindowMessages = 1;
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, 0);

	//Fmod Init 
	FMODInit();
	if (0 == AESysInit(&sysInitInfo))
		printf("System Init Failed!\n");


	// Changing the window title
	AESysSetWindowTitle("Inversion");

	// reset the system modules
	AESysReset();

	//--------------------------------------------------------------------------
	// NOTE: Other modules can be initialized later and in any order.
	//--------------------------------------------------------------------------

	// Initialize the game state manager.
	GameStateManagerInit();
}

// Update the game engine.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void EngineUpdate(float dt)
{
	TraceMessage("Engine: Update");

	AESysUpdate();
	//Fmod update
	FMODUpdate(dt);
	// Update the game state manager.
	GameStateManagerUpdate(dt);
}

// Shutdown the game engine.
void EngineShutdown()
{
	//--------------------------------------------------------------------------
	// NOTE: Some modules can be shutdown in any order.
	//--------------------------------------------------------------------------

	// Shutdown the game state manager.
	GameStateManagerShutdown();
	//Fmod shutdown
	FMODShutdown();
	//--------------------------------------------------------------------------
	// NOTE: Certain modules need to be shutdown last and in reverse order.
	//--------------------------------------------------------------------------
	
	// free the system
	AESysExit();
 
	TraceMessage("Engine: Shutdown");


	// Shutdown the Tracing/Logging module.
	TraceShutdown();
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

