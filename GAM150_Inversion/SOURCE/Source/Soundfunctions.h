//------------------------------------------------------------------------------
//
// File Name:	Soundfunctions.h
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
#include "fmod.h"
//------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
	/* Assume C declarations for C++ */
#endif
#pragma warning(push)
#pragma warning(disable : 4201)
	//------------------------------------------------------------------------------
	// Public Consts:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Structures:
	//------------------------------------------------------------------------------
	typedef enum
	{
		/* Special Game States */
		
		SongLevel1 = 0,
		GamesoundGoldcoin = 1,
		GamesoundOUTOFBOUNDS = 2,
		GamesoundWALK1 = 3,
		GamesoundWALK2 = 4,
		GamesoundUP1 = 5,
		GamesoundUP2 = 6,
		SongDigipenlogo = 7,
		SongExtraSong = 8,
		SongMainMenu = 9,
		SongExtraSong2 = 10,
		Gamesoundgrapplehit = 11,
		Gamesoundshot = 12,
		Gamesoundtopmainmenu = 13,
		Gamesoundmiddlemainmenu = 14,
		Gamesoundbottommainmenu = 15,
		Gamesoundinversionred = 16,
		Gamesoundinversionblue = 17,
		Gamesoundland = 18,
		Gamesoundflag = 19,
		GamesoundHelicopter = 20,
		Gamesoundquick = 21,
		Gamesoundwoopwoopwoop = 22,
		Gamesoundsoft = 23,
		Gamesoundyehs = 24,
		Gamesoundalienstartnoise = 25,
		Gamesoundhigher = 26,
		Gamesoundalaram = 27,
		Gamesoundbringbringbrin = 28,

		/* Bookkeeping States: */
		Totalmusicnoises,
		Lastmusicsound = Totalmusicnoises - 1,

	} Gamesounds;
	
	//------------------------------------------------------------------------------
	// Public Variables:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------
	void FMODShutdown();
		void FMODUpdate(float dt);
		void FMODInit();
	void MakeBGM();
	void Makesoundeffects();
	void Createallsounds();
	void playsoundsplash();
	void playsoundshot();
	void playsoundgrappleattach();
	void playsoundjump(bool doublejump);
	void playsoundland();
	void playsoundwalk();
	void playsoundrun();
	void playsoundBGM();
	void playmusicBGMLevel1();
	void playmusicBGMMainmenu();
	void playsoundMainMenuselectiontop();
	void playsoundMainMenuselectionmiddle();
	void playsoundMainMenuselectionbottom();
	void playsoundInversionRed();
	void playsoundInversionBlue();
	
	void playmusicBGMCreditscreen();
	void playmusicBGMDigipenscreen();
	void playmusicBGMPause(Gamesounds soundtopause);
	void playmusicBGMInversion();
	int walknumber(int current);
	void checkforeerrors(int ERRORnum);
	void playGoldsound();
	void soundcontrol(float volume);
	void playsoundflag();
	void pitchmixer(FMOD_CHANNEL *soundtopitch);
	void Musiccontrol(float volume);
	void Pauseallsounds();
	/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

