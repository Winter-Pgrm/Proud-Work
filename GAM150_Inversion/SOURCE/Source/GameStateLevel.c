//------------------------------------------------------------------------------
//
// File Name:	GameStateLevel.c
// Author(s):	Brian Lu, Alex Phillips, Ian Gaither, Deni Van Winkle
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <math.h>

#include "GameStateManager.h"
#include "GameStateLevel.h"
#include "Trace.h"
#include "AEEngine.h"
#include "Player.h"
#include "Enemy.h"
#include "physics.h"
#include "Particle.h"
#include "Commandlist.h"
#include "LevelManager.h"
#include "Gfx.h"
#include "Camera.h"
#include "Collision.h"
#include "Soundfunctions.h"
#include "Checkpoint.h"
#include "CheckpointFlag.h"
#include "Hook.h"
#include "Timer.h"
#include "Death.h"
#include "OptionsMenu.h"
#include "PlayerMovement.h"
#include "SnowEffect.h"
#include "Coin.h"
// ---------------------------------------------------------------------------

// Libraries
#pragma comment (lib, "Alpha_Engine.lib")


#define MAXLENGTH 1000;
//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------
static int numLives = 0;
//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
int gGameRunning = 1;

static int originflag = 0;
static float Checkpointarrayholder[8] ;
static float FINISH[2] = { 0,10.0f };
static float outofbounds[2] = { -190.0, 555.55f };
static int VICTORY = 0;
AEVec2 checkpointeLocation = { 0,0 };
AEVec2 checkpointeLocation2 = { 0,0 };
static int  paused = FALSE;
static int checkpaused = FALSE;
static int previousFrame = 0;



PlayerPtr player;
EnemyPtr enemy;
EnemyPtr enemy2;
CPPoint Lvl1checkpointptr;
//
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------


// Load the resources associated with the Stub game state.
void GameStateLevelLoad()
{
	gGameRunning = 1;
	VICTORY = 0;
	playmusicBGMPause(SongMainMenu);
	playsoundBGM();
	TraceMessage("Level1: Load");
	UpdateScore();
}

// Initialize the memory associated with the Stub game state.
void GameStateLevelInit()
{
	player = PlayerCreate("player1", "Assets/PenguinFrames.png");

	 if (GetCurrentLevelIndex() == 1)
	{
	
		GameStateManagerSetNextState(GsMainMenu);
	}
	FlagInit();
	FlagInit2();
	optionsmenuinit();

	enemy = EnemyCreate("Test", (float)-580.523254, (float)125.841309, 1000);
	enemy2 = EnemyCreate("Final",  (float)600, (float)-90, 300);


	LevelManagerInit(player);
	checkthecheckpoints(&*Checkpointarrayholder);
	CameraInit(player);
	TimerInit();
	SnowInit();
	ParticleEffectInit();
	CoinInit();
	TraceMessage("Level1: Init");
}

// Update the Stub game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameStateLevelUpdate(float dt)
{
	static float timedelay = 0.0f;
	TraceMessage("Level1: Update");
	
	// Game Loop
	while (gGameRunning)
	{
		AEInputUpdate();
		if (AEInputCheckTriggered(VK_ESCAPE))
		{
			paused = TRUE;
			checkpaused = TRUE;

		}
			if (paused == FALSE)
			{
				physicsUpdate(player);
				dt = .16f;


			}
			else if(paused == TRUE)
			{
				
		
				dt = 0; 
				if (checkpaused == FALSE)
				{
					paused = FALSE;
					dt = .16f;
				}
			}
		

		// Informing the system about the loop's start		

		s32 x = 0, y = 0;
		AEInputGetCursorPosition(&x, &y);
		
		static float sx = 0.0f;
		static float sy = 0.0f;
		if (GetPlayertriggered1stcheckpoint(player) || GetPlayertriggered2ndcheckpoint(player))
		{
			checkpointeLocation2.x = checkpointeLocation.x;
			checkpointeLocation2.y = checkpointeLocation.y;
			checkpointeLocation = *checkifcheckpointertriggered(PlayerGetXcoordinate(player), PlayerGetYcoordinate(player), Checkpointarrayholder, player);
			if (checkpointeLocation.x == -10000.0f && checkpointeLocation.y == 100000.0f)
			{
				checkpointeLocation.x = checkpointeLocation2.x;
				checkpointeLocation.y = checkpointeLocation2.y;
			}
		}
		else
		{
			checkpointeLocation = *checkifcheckpointertriggered(PlayerGetXcoordinate(player), PlayerGetYcoordinate(player), Checkpointarrayholder, player);
			if (!GetPlayertriggered1stcheckpoint(player) && !GetPlayertriggered2ndcheckpoint(player))
			checkpointeLocation = *GetStartPoint();
		}

		
		//penguin frames
		PlayerSetFrameIndex(player, 0.2f, 0.0f, 1);
		PlayerSetFrameIndex(player, 0.4f, 0.0f, 2); //idle frame
		PlayerSetFrameIndex(player, 0.6f, 0.0f, 3);
		PlayerSetFrameIndex(player, 0.8f, 0.0f, 4);

		if (paused == FALSE)
		{
			if (AEInputCheckCurr('R'))
			{
				reset();

				PlayerSetXcoordinate(player, checkpointeLocation.x);
				PlayerSetYcoordinate(player, checkpointeLocation.y);
				CameraReset();
				if (timedelay <= 0.0f)
				{
					playsoundsplash();
					timedelay = 0.5f;
				}
				else if (timedelay > 0)
				{
					timedelay -= dt;
				}
			}
			
			PlayerMovement(player, dt);
			
			if (AEInputCheckTriggered(VK_RBUTTON))
			{
				if(CharacterGetLives(PlayerGetCharacter(player)) == 1)
					Inversion(player);

			}
			else if (AEInputCheckTriggered(VK_LBUTTON))
			{
				if (hookActiveStatus())
				{
					HookReset();
				}
				else
				{
					HookReset();
					HookBegin(player);
					if(CharacterGetLives(PlayerGetCharacter(player)) == 1)
						playsoundshot(); //sound not tested but added 
				}
			}
			dt = .16f;
		}
		else if (paused == TRUE)
		{
			 
			
			dt = 0;
			if (checkpaused == FALSE)
			{
				paused = FALSE;
				dt = .16f;
			}
		}

		
		//---------------------------------
		// Graphics Update
		AESysFrameStart();
		if (paused != TRUE)
		{
			CameraUpdate(PlayerGetXcoordinate(player), PlayerGetYcoordinate(player));
		}
		GfxUpdate(player, dt);
		flagsbuilder(&*Checkpointarrayholder);
		TimerUpdate(dt);
		CoinUpdate(dt);
		//set dt to 0 to pause them 
		EnemyUpdate(enemy, dt);
		EnemyUpdate(enemy2, dt);
		ParticleEffectUpdate(dt);
		SnowEffect(dt);
		
		if (paused == TRUE)
		{
			checkpaused = Pausedstate(dt );
		
			if (checkpaused == FALSE)
			{
				
				CameraUpdate(PlayerGetXcoordinate(player), PlayerGetYcoordinate(player));
				paused = FALSE;
				dt = .16f;
				
				
			}
			else if (checkpaused == 3)
			{
				//CameraReset();
				GameStateManagerSetNextState(GsMainMenu);
				gGameRunning = 0;
				paused = FALSE;
				dt = .16f;
			}
			else if (checkpaused == 4)
			{
				CameraInit(player);
				GameStateManagerSetNextState(GsQuit);
				gGameRunning = 0;
				paused = FALSE;
				dt = .16f;
			}
		}
		AESysFrameEnd();
		//
		//---------------------------------


		// check if forcing the application to quit


		if (EnemyCollision(player, enemy) || EnemyCollision(player, enemy2))
		{

			CharacterSetLives(PlayerGetCharacter(player), 0);
		}

		if (checkifgoalpoiunt(PlayerGetXcoordinate(player), (PlayerGetYcoordinate(player))))
		{

			VICTORY = goalpoint();
			
			if (GetCurrentLevelIndex() == 0)
			{
				unsigned total = 1;
			    LevelManagerChangeLevel(player,total);
			   LevelManagerChangeLevel(player,total);
				checkpointeLocation = *GetStartPoint();
				nextLevel();
	
				//nextLevel();
				UpdateScore();
				checkthecheckpoints(&*Checkpointarrayholder);
				CameraInit(player);
			}
			else if (GetCurrentLevelIndex() == 1)
			{
				
				unsigned total = 2;
				
				LevelManagerChangeLevel(player, total);
				checkpointeLocation = *GetStartPoint();
				checkthecheckpoints(&*Checkpointarrayholder);
				
				ScoreInit();
				UpdateScore();
				
				CameraInit(player);
			}
			else if (GetCurrentLevelIndex() == 2)
			{

				unsigned total = 3;
				
				LevelManagerChangeLevel(player, total);
				checkpointeLocation = *GetStartPoint();
				checkthecheckpoints(&*Checkpointarrayholder);

				ScoreInit();
				UpdateScore();

				CameraInit(player);
			}
			else if (GetCurrentLevelIndex() == 3)
			{

				unsigned total = 0;
				gGameRunning = 0;
				LevelManagerChangeLevel(player, total);
				SetPlayertriggered1stcheckpoint(player, 0);
				SetPlayertriggered2ndcheckpoint(player, 0);
				GameStateManagerSetNextState(GsCredits);
				getFastestTime();
				ScoreInit();
				UpdateScore();
				TimerReset();
			}
			VICTORY = 0;
			CameraResetOrigin();

		}
	
		deathCheck(player, checkpointeLocation.x, checkpointeLocation.y, dt); //checks if the player is dead

	}
}

// Shutdown any memory associated with the Stub game state.
void GameStateLevelShutdown()
{
	GfxShutdown();
	freeoptions();
	SnowFree();
	ParticleFree();
	TraceMessage("Level1: Shutdown");
}

// Unload the resources associated with the Stub game state.
void GameStateLevelUnload()
{
	playmusicBGMPause(SongLevel1);
	playmusicBGMPause(SongExtraSong2);
	TraceMessage("Level1: Unload");
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

