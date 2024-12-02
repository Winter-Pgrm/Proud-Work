//------------------------------------------------------------------------------
//
// File Name:	FMOD.c
// Author(s):	Alex Phillips
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Trace.h"
#include "fmod.h"
#include "random.h"
#include "Soundfunctions.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------
#define soundtotals 33
//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

static	FMOD_SYSTEM      *FmodSystem;
static	FMOD_SOUND       *sound[soundtotals];
static	FMOD_SOUND       *Musicsound[soundtotals];
static  FMOD_CHANNEL       *channelsound[1];
//try an array of channels and use for each sound 
static	FMOD_CHANNEL     *channel[soundtotals] = { 0 };


static FMOD_CHANNELGROUP *Music = 0;
static FMOD_CHANNELGROUP *SoundEffects = 0;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------
static char *BGM = "BGM";
static char *SEF = "SEF";
FMOD_RESULT       result;
unsigned int      version;
void             *extradriverdata = 0;
float vol= 0.0;
int low = 5;
int high = 1;
static float pitchchangerforjump;

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Initialize the ...

void FMODInit()
{
	//Common_Init(&extradriverdata);
	
	result = FMOD_System_Create(&FmodSystem);
	checkforeerrors(result);
	
	
	result = FMOD_System_GetVersion(FmodSystem, &version);
	checkforeerrors(result);

	result = FMOD_System_Init(FmodSystem, 32, FMOD_INIT_NORMAL, extradriverdata);
	checkforeerrors(result);
	result = FMOD_System_CreateChannelGroup(FmodSystem, BGM, &Music);
	checkforeerrors(result);
	result = FMOD_System_CreateChannelGroup(FmodSystem, SEF, &SoundEffects);
	checkforeerrors(result);
	
	Createallsounds();
	
	
	checkforeerrors(result);
	
	//result = FMOD_ChannelGroup_SetVolume(Music, 0.25);
	//result = FMOD_ChannelGroup_SetVolume(SoundEffects, .80);
	//result = FMOD_Channel_SetVolume(channel, 0.05f);
	checkforeerrors(result);
	
	//result = FMOD_Channel_SetPriority(channel, low);
	//result = FMOD_Channel_SetPriority(channel2, high);
	

	
	//FMOD_Sound_GetMusicChannelVolume(sound[0], channel, &vol);
	//result = FMOD_Channel_SetVolume(channel, vol);
	//ERRCHECK(result);
	
	//FMOD_Channel_GetVolume(&channel, &vol);
	//vol = 0.0f;//max(min(vol, 1.0f), 0.0f);
	

}

// Update the ...
// Params:
//	 dt = Change in time (in seconds) since the last game loop.

void FMODUpdate(float dt)
{
	UNREFERENCED_PARAMETER(dt);

	result = FMOD_System_Update(FmodSystem);
	checkforeerrors(result);
	//ERRCHECK(result);
}

// Shutdown the ...
void FMODShutdown()
{
	//result = FMOD_Sound_Release(sound[0]);
	checkforeerrors(result);
	result = FMOD_System_Close(FmodSystem);
	checkforeerrors(result);
	result = FMOD_System_Release(FmodSystem);
	checkforeerrors(result);

}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
void Createallsounds()
{
	MakeBGM();
	Makesoundeffects();
}


void MakeBGM()
{
	
	//FMOD_System_CreateStream (FmodSystem, BGM, FMOD_DEFAULT | FMOD_LOOP_NORMAL, extradriverdata, &sound[0]);
	result = FMOD_System_CreateSound(FmodSystem, "game sound\\Unfound Mastering.wav", FMOD_DEFAULT | FMOD_LOOP_NORMAL, extradriverdata, &Musicsound[0]);
	checkforeerrors(result);
	
	result = FMOD_System_CreateSound(FmodSystem, "game sound\\Intermission.mp3", FMOD_DEFAULT | FMOD_LOOP_NORMAL, extradriverdata, &Musicsound[1]);
	checkforeerrors(result);
	result = FMOD_System_CreateSound(FmodSystem, "game sound\\MazeSong.wav", FMOD_DEFAULT | FMOD_LOOP_NORMAL, extradriverdata, &Musicsound[2]);
	checkforeerrors(result);
	result = FMOD_System_CreateSound(FmodSystem, "game sound\\MazeSong2.wav", FMOD_DEFAULT | FMOD_LOOP_NORMAL, extradriverdata, &Musicsound[3]);
	checkforeerrors(result);
	result = FMOD_System_CreateSound(FmodSystem, "game sound\\MazeSong4.wav", FMOD_DEFAULT | FMOD_LOOP_NORMAL, extradriverdata, &Musicsound[4]);
	checkforeerrors(result);
	
}
void Makesoundeffects()
{
	result = FMOD_System_CreateSound(FmodSystem, "game sound\\Pickup_Coin8.wav", FMOD_DEFAULT | FMOD_LOOP_OFF, extradriverdata, &sound[1]);
	checkforeerrors(result);
	result = FMOD_System_CreateSound(FmodSystem, "game sound\\splash.wav", FMOD_DEFAULT | FMOD_LOOP_OFF, extradriverdata, &sound[2]);
	checkforeerrors(result);
	
	result = FMOD_System_CreateSound(FmodSystem, "game sound\\walk.wav", FMOD_DEFAULT | FMOD_LOOP_OFF, extradriverdata, &sound[3]);
	checkforeerrors(result);
	result = FMOD_System_CreateSound(FmodSystem, "game sound\\walk2.wav", FMOD_DEFAULT | FMOD_LOOP_OFF, extradriverdata, &sound[4]);
	checkforeerrors(result);
	result = FMOD_System_CreateSound(FmodSystem, "game sound\\Up.wav", FMOD_DEFAULT | FMOD_LOOP_OFF, extradriverdata, &sound[5]);
	checkforeerrors(result);
	result = FMOD_System_CreateSound(FmodSystem, "game sound\\up4.wav", FMOD_DEFAULT | FMOD_LOOP_OFF, extradriverdata, &sound[6]);
	checkforeerrors(result);
	result = FMOD_System_CreateSound(FmodSystem, "game sound\\flag.wav", FMOD_DEFAULT | FMOD_LOOP_OFF, extradriverdata, &sound[15]);
	checkforeerrors(result);
	result = FMOD_System_CreateSound(FmodSystem, "game sound\\helicopter.wav", FMOD_DEFAULT | FMOD_LOOP_OFF, extradriverdata, &sound[16]);
	checkforeerrors(result);
	result = FMOD_System_CreateSound(FmodSystem, "game sound\\quick.wav", FMOD_DEFAULT | FMOD_LOOP_OFF, extradriverdata, &sound[17]);
	checkforeerrors(result);
	result = FMOD_System_CreateSound(FmodSystem, "game sound\\Woopwoopwoop.wav", FMOD_DEFAULT | FMOD_LOOP_OFF, extradriverdata, &sound[18]);
	checkforeerrors(result);
	result = FMOD_System_CreateSound(FmodSystem, "game sound\\soft.wav", FMOD_DEFAULT | FMOD_LOOP_OFF, extradriverdata, &sound[19]);
	checkforeerrors(result);
	result = FMOD_System_CreateSound(FmodSystem, "game sound\\yehs.wav", FMOD_DEFAULT | FMOD_LOOP_OFF, extradriverdata, &sound[20]);
	checkforeerrors(result);
	result = FMOD_System_CreateSound(FmodSystem, "game sound\\alienstartnoise.wav", FMOD_DEFAULT | FMOD_LOOP_OFF, extradriverdata, &sound[21]);
	checkforeerrors(result);
	result = FMOD_System_CreateSound(FmodSystem, "game sound\\higher.wav", FMOD_DEFAULT | FMOD_LOOP_OFF, extradriverdata, &sound[22]);
	checkforeerrors(result);
	result = FMOD_System_CreateSound(FmodSystem, "game sound\\alaram.wav", FMOD_DEFAULT | FMOD_LOOP_OFF, extradriverdata, &sound[23]);
	checkforeerrors(result);
	result = FMOD_System_CreateSound(FmodSystem, "game sound\\bringbringbrin.wav", FMOD_DEFAULT | FMOD_LOOP_OFF, extradriverdata, &sound[24]);
	checkforeerrors(result);


}
void playsoundsplash()
{
	result = FMOD_System_CreateSound(FmodSystem, "game sound\\splash.wav", FMOD_DEFAULT | FMOD_LOOP_OFF, extradriverdata, &sound[2]);
	checkforeerrors(result);
	result = FMOD_System_PlaySound(FmodSystem, sound[2], SoundEffects, false, &channel[2]);
	
	checkforeerrors(result);
	sound[2] = NULL;
}
//This function starts the BGM for the game 
void playsoundBGM()
{
	//remove channelgroups make a master volume setter and make and play sounds in the play sound functions
	//may need more channels for this. check 
	//check if the channel is NULL
	// do checks and what not.
	 float randomsong = randomfloatrange(0.0f, 1.0f);
	 if (randomsong <= .5f)
	 {
		 result = FMOD_System_PlaySound(FmodSystem, Musicsound[0], Music, false, &channelsound[0]);
		 result = FMOD_Channel_SetPriority(channelsound[0], 66);
		 result = FMOD_ChannelGroup_SetVolume(Music, .24f);
		 result = FMOD_ChannelGroup_SetPaused(Music, false);
	 }
	 else
	 {
		 result = FMOD_System_PlaySound(FmodSystem, Musicsound[4], Music, false, &channel[10]);
		 FMOD_Channel_SetPriority(channel[10], 66);
		 result = FMOD_ChannelGroup_SetVolume(Music, .24f);
		 result = FMOD_ChannelGroup_SetPaused(Music, false);

	 }
	//sound[0] = NULL;
	//FMOD_System_PlaySound(FmodSystem, sound[0], Music, false, channel);
}
//This function plays the sound for the shot from the grappling gun
void playsoundshot()
{

	result = FMOD_System_CreateSound(FmodSystem, "game sound\\shot.wav", FMOD_DEFAULT | FMOD_LOOP_OFF, extradriverdata, &sound[8]);
	checkforeerrors(result);
	result = FMOD_System_PlaySound(FmodSystem, sound[8], SoundEffects, false, &channel[12]);

}
void playsoundflag()
{
	
	result = FMOD_System_PlaySound(FmodSystem, sound[15], SoundEffects, false, &channel[12]);
	checkforeerrors(result);

}
//this function plays a sound for when the grappling hood attaches 
void playsoundgrappleattach()
{
	result = FMOD_System_CreateSound(FmodSystem, "game sound\\grappling hit.wav", FMOD_DEFAULT | FMOD_LOOP_OFF, extradriverdata, &sound[7]);
	checkforeerrors(result);
	result = FMOD_System_PlaySound(FmodSystem, sound[7], SoundEffects, false, &channel[11]);

}
//This function plays a sound for when the player jumps 
//needs bool doublejump 
void playsoundjump(bool doublejump)
{
	
	if (pitchchangerforjump > 1)
	{
	//	pitchchangerforjump = 55.7f;
	//	result = FMOD_Channel_SetPitch(channel[3], pitchchangerforjump);
	}
	if (doublejump == true)
	{
 		result = FMOD_System_PlaySound(FmodSystem, sound[5], SoundEffects, false, &channel[5]);
		FMOD_Channel_SetVolume(channel[5], .5f);
	//	result = FMOD_Channel_SetPitch(channel[5], pitchchangerforjump);
		//pitchchangerforjump += 5.5f;
	}
	else
	{
		result = FMOD_System_PlaySound(FmodSystem, sound[6], SoundEffects, false, &channel[6]);
		//result =  FMOD_Channel_SetPitch(channel[5], pitchchangerforjump);
	//	pitchchangerforjump += .5;
	}
	FMOD_Channel_GetPitch(channel[5], &pitchchangerforjump);
}
//This function plays a sound for when the player lands
void playsoundland()
{
	result = FMOD_System_CreateSound(FmodSystem, "game sound\\land.wav", FMOD_DEFAULT | FMOD_LOOP_OFF, extradriverdata, &sound[14]);
	checkforeerrors(result);
	result = FMOD_System_PlaySound(FmodSystem, sound[14], SoundEffects, false, &channel[18]);
	checkforeerrors(result);


}
//This function plays a sound for when the player walks forward
void playsoundwalk()
{
	//helperfunction
	static int currentwalksound = 1;
	currentwalksound = walknumber(currentwalksound);
	switch (currentwalksound)
	{
	case 1:
		result = FMOD_System_PlaySound(FmodSystem, sound[4], SoundEffects, false, &channel[4]);
		checkforeerrors(result);
		break;
	default:
		result = FMOD_System_PlaySound(FmodSystem, sound[3], SoundEffects, false, &channel[3]);
		checkforeerrors(result);
		break;
	}
	

}
//This is a function being used by the walk sound function
int walknumber(int current)
{
	switch (current)
	{
	case 1:
		return 2;
	default:
		return 1;
		break;
	}

}
//this function plays the sound for if the player is running
void playsoundrun()
{


}
void playGoldsound()
{
	result = FMOD_System_PlaySound(FmodSystem, sound[4], SoundEffects, false, &channel[1]);
	checkforeerrors(result);

}
//this function plays the Backroundmusic for the first level
void playmusicBGMLevel1()
{


}
//this function plays the Backroundmusic for the Main Menu
void playmusicBGMMainmenu()
{
	result = FMOD_System_PlaySound(FmodSystem, Musicsound[3], Music, false, &channel[9]);
	result = FMOD_ChannelGroup_SetVolume(Music, .24f);
}
//this function plays the Backroundmusic for the Credit screen
void playmusicBGMCreditscreen()
{


}
//this function plays the Backroundmusic for the digipen splash screen
void playmusicBGMDigipenscreen()
{
	result = FMOD_System_PlaySound(FmodSystem, Musicsound[1], Music, false, &channel[7]);
	result = FMOD_ChannelGroup_SetVolume(Music, .35f);
}
//Channels are defined in a ENUM list; IF you play a song Send this function
// that Enum title for EXAMPLE: Songtitle
//this function plays the Backroundmusic for the pause screen
void playmusicBGMPause(Gamesounds soundtopause)
{
	if(soundtopause ==SongLevel1)
		result = FMOD_Channel_Stop(channelsound[0]);
	else if (soundtopause == SongExtraSong2)
		result = FMOD_Channel_Stop(channel[10]);
	else
	result = FMOD_Channel_Stop(channel[soundtopause]);

}
//this function plays the Backroundmusic for the inverion states 
void playmusicBGMInversion()
{


}
void playsoundMainMenuselectiontop()
{
	result = FMOD_System_CreateSound(FmodSystem, "game sound\\top MM.wav", FMOD_DEFAULT | FMOD_LOOP_OFF, extradriverdata, &sound[9]);
	checkforeerrors(result);
	result = FMOD_System_PlaySound(FmodSystem, sound[9], SoundEffects, false, &channel[13]);

}
void playsoundMainMenuselectionmiddle()
{
	result = FMOD_System_CreateSound(FmodSystem, "game sound\\middlemm.wav", FMOD_DEFAULT | FMOD_LOOP_OFF, extradriverdata, &sound[10]);
	checkforeerrors(result);
	result = FMOD_System_PlaySound(FmodSystem, sound[10], SoundEffects, false, &channel[14]);

}
void playsoundMainMenuselectionbottom()
{
	result = FMOD_System_CreateSound(FmodSystem, "game sound\\bottomMM.wav", FMOD_DEFAULT | FMOD_LOOP_OFF, extradriverdata, &sound[11]);
	checkforeerrors(result);
	result = FMOD_System_PlaySound(FmodSystem, sound[11], SoundEffects, false, &channel[15]);

}
void playsoundInversionRed()
{
	result = FMOD_System_CreateSound(FmodSystem, "game sound\\Inversion1.wav", FMOD_DEFAULT | FMOD_LOOP_OFF, extradriverdata, &sound[12]);
	checkforeerrors(result);
	result = FMOD_System_PlaySound(FmodSystem, sound[12], SoundEffects, false, &channel[16]);

}
void playsoundInversionBlue()
{
	result = FMOD_System_CreateSound(FmodSystem, "game sound\\Inversion2.wav", FMOD_DEFAULT | FMOD_LOOP_OFF, extradriverdata, &sound[13]);
	checkforeerrors(result);
	result = FMOD_System_PlaySound(FmodSystem, sound[13], SoundEffects, false, &channel[17]);

}
void Pauseallsounds()
{

	float numberholder = 0.0f;
	result = FMOD_ChannelGroup_GetVolume(Music, &numberholder);
	checkforeerrors(result);
	if (numberholder == 0.0f)
	{
		numberholder = .60f;

	}
	else if (numberholder > 0.0f)
	{
		numberholder = 0.0f;
	}
	result = FMOD_ChannelGroup_SetVolume(Music, numberholder);
	checkforeerrors(result);


	
	result = FMOD_ChannelGroup_GetVolume(SoundEffects, &numberholder);
	checkforeerrors(result);
	
	if (numberholder == 0.0f)
	{
		numberholder = .60f;

	}
	else if (numberholder > 0.0f)
	{
		numberholder = 0.0f;
	}
	result = FMOD_ChannelGroup_SetVolume(SoundEffects, numberholder);
	checkforeerrors(result);

	
}
void soundcontrol(float volume)
{

	float numberholder = 0.0f;
	result = FMOD_ChannelGroup_GetVolume(SoundEffects, &numberholder);
	checkforeerrors(result);
	numberholder += volume;
	if (numberholder > 1.0f)
		numberholder = 1.0f;
	if (numberholder < 0.0f)
		numberholder = 0.0f;
	result = FMOD_ChannelGroup_SetVolume(SoundEffects, numberholder);
	checkforeerrors(result);
}
void Musiccontrol(float volume)
{
	float numberholder = 0.0f;
	result = FMOD_ChannelGroup_GetVolume(Music, &numberholder);
	checkforeerrors(result);
	numberholder += volume;
	if (numberholder > 1.0f)
		numberholder = 1.0f;
	if (numberholder < 0.0f)
		numberholder = 0.0f;
	result = FMOD_ChannelGroup_SetVolume(Music, numberholder);
	checkforeerrors(result);
	
}
void pitchmixer(FMOD_CHANNEL *soundtopitch)
{
	static float pitchchanger = .66f;
	result = FMOD_Channel_SetPitch(soundtopitch, pitchchanger);
	checkforeerrors(result);
}

void checkforeerrors(int ERRORnum)
{
	switch (ERRORnum)
	{
	case !0:
		TraceMessage("Error in Fmod");
	default:
		
		break;
	}



}
