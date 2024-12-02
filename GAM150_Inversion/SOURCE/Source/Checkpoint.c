//------------------------------------------------------------------------------
//
// File Name:	Checkpoint.c
// Author(s):	Alex Phillips
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "AEEngine.h"
#include "Checkpoint.h"
#include "GameStateManager.h"
#include "LevelManager.h"
#include "Particle.h"
#include "Soundfunctions.h"
#include "CheckpointFlag.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------
AEVec2 Playerrespawnlocation = { 0,0 };
AEVec2 Nolocationchange = { -10000.0f,100000.0f };
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
CPPoint  Makecheckpoint(const float CurrentX, const float CurrentY)
{
	CPPoint holder;

	holder.x = CurrentX;
	holder.y = CurrentY;


	return holder;
}

float getpointx(CPPoint  holder)
{

	return holder.x;

}
float getpointy(CPPoint  holder)
{

	return holder.y;

}
int goalpoint()
{
	return  1;
}

//AEGfxLine((float)obj1X, (float)obj1Y, 0, 0, 1, 1, 1, (float)sx + (obj1X - 640), ((obj1Y)-(float)sy + 400), 0, 0, 1, 0, 1);

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

void checkthecheckpoints(float *checkpointarray)
{
	int i = 0;

	for (i = 0; i < 8; i++)
	{
		checkpointarray[i] = 0;
	}
	float * holder;
	holder = GetCheckpoints();
	for (i = 0; i < 8; i++)
	{
		checkpointarray[i] = holder[i];
	}


}
void flagsbuilder(float *checkpointarray)
{

		float distance1 = 0.0f;
	float distance2 = 0.0f;
	AEVec2 startLocation = { 0,0 };
	AEVec2 endLocation = { 0,0 };
	AEVec2 startLocation2 = { 0,0 };
	AEVec2 endLocation2 = { 0,0 };

		startLocation.x = checkpointarray[0 ];
	startLocation.y = checkpointarray[1 ];
	endLocation.x = checkpointarray[2 ];
	endLocation.y = checkpointarray[3 ];
	startLocation2.x = checkpointarray[4];
	startLocation2.y = checkpointarray[5];
	endLocation2.x = checkpointarray[6];
	endLocation2.y = checkpointarray[7];
	distance1 = AEVec2Distance(&startLocation2, &endLocation2);
	startLocation.x = (startLocation.x + (distance1 / 2));
	distance2 = AEVec2Distance(&startLocation2, &endLocation2);
	startLocation2.x = (startLocation2.x + (distance2 / 2));
	

	SetFlag1Update(startLocation.x , checkpointarray[1] + 38);
	SetFlag2Update(startLocation2.x, checkpointarray[5] + 38);
	//call the levelmanager for the point
	//probably set it in here
	

}
AEVec2 *checkifcheckpointertriggered(float CurrentX, float CurrentY, float *checkpointarray, PlayerPtr player)
{
	int i = 0;


	AEVec2 startLocation = { 0,0 };
	AEVec2 endLocation = { 0,0 };
	
	
	float distance = 0.0f;

	int currentflag = 0;

	//need vector 2ds for holding x and y 
	//set each of the above variables to the locations + 
	for (i = 0; i < 2; i++)
	{
		if (i == 0)
		{
			currentflag = GetPlayertriggered1stcheckpoint(player);
		}
		else if (i == 1)
		{
			currentflag = GetPlayertriggered2ndcheckpoint(player);
		}
		  startLocation.x = checkpointarray[(0 + (4 * i))];
		  startLocation.y = checkpointarray[(1 + (4 * i))];
			endLocation.x = checkpointarray[(2 + (4 * i))];
			endLocation.y = checkpointarray[(3 + (4* i))];

			if ((CurrentY >= startLocation.y && CurrentY <= (endLocation.y +50)) && (CurrentX >= startLocation.x && CurrentX <= endLocation.x) && currentflag == 0 )
			{
				distance = AEVec2Distance(&startLocation, &endLocation);
				Playerrespawnlocation.x = (startLocation.x +(distance/2));
				Playerrespawnlocation.y = startLocation.y + 40.0f;
				if (i == 0)
				{
					 SetPlayertriggered1stcheckpoint(player, 1);
					 SetPlayertriggered2ndcheckpoint(player, 0);
					 ParticleEffectStart(10, CurrentX, CurrentY);
					 playsoundflag();
					 SetFlag1Clear();
					 SetFlag2Unclear();
				}
				else if (i == 1)
				{
					SetPlayertriggered2ndcheckpoint(player, 1);
					SetPlayertriggered1stcheckpoint(player, 0);
					playsoundflag();

					SetFlag2Clear();
					SetFlag1Unclear();
					ParticleEffectStart(10, CurrentX, CurrentY);
				
				}

				return &Playerrespawnlocation;

			}
	}
	
	if (GetPlayertriggered1stcheckpoint(player) || GetPlayertriggered2ndcheckpoint(player))
		return &Nolocationchange;
	else 
	return &Playerrespawnlocation;

}

bool checkifgoalpoiunt(float CurrentX, float CurrentY )
{

	AEVec2 startLocation = *GetEndPoint();
	if ((CurrentX >= (startLocation.x - 60.0f) && CurrentX <= (startLocation.x + 60.0f)) && (CurrentY >= (startLocation.y - 60.0f) && CurrentY <= ( startLocation.y + 60.0f)))
		return true;

	return false;
	



}
//call for setting the check point location, if it is the 1st it will be [1] etc.
//apply this to checkpoint array in the gamestate level
//the checkpoints will be at least 20 pixels higher then each of those pixels. or well
// 0 to 20 pixels between those that point
// once triggered play an animation and sound effect and set the location as triggered.
// if another location is possible for a check point 
//if triggered play the animation and set the flag to 2 so if the player goes back 
// they can trigger the previous one.
// the first checkpoint is the startpoint in the game. 

//things required. probably a array of points could use the start point and the end point from the color for check point
//then take the points btween them and use that for the array. can also set that the 1,2, 3,4 as the start and 5,6,7,8 are the 2st checkpoint
//This is there start x and y and the last x and y
//max checkpoints will be 2 per level. the array will be the size of max checkpointer 

