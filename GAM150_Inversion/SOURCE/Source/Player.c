//------------------------------------------------------------------------------
//
// File Name:	Player.c
// Author(s):	Brian Lu & Deni Van Winkle
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Player.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
typedef struct
{
	float mX;
	float mY;
}TextureOffset;

typedef struct Player
{
	// The texture file for the character
	const char * LiveTexture;

	float PlayerXcoordinate;

	float PlayerYcoordinate;

	CharacterPtr character;

	TextureOffset textureOffsets[10];

	int currentTextureOffset;
	
	int checkpoint1triggered;

	int checkpoint2triggered;

	float deathDuration; //death duration

} Player;


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
PlayerPtr PlayerCreate(char * name, char * Texture)
{
	PlayerPtr NewPlayer;
	NewPlayer = calloc(1, sizeof(Player));
	
	if (NewPlayer)
	{
		NewPlayer->character = CharacterCreate(name, Texture, 1);
		NewPlayer->PlayerXcoordinate = -1100.0f;
		NewPlayer->PlayerYcoordinate = -600.0f;
		NewPlayer->LiveTexture = NULL;
		NewPlayer->currentTextureOffset = 2;
		NewPlayer->textureOffsets[0].mX = 0.0f;			
		NewPlayer->textureOffsets[0].mY = 0.0f;
		NewPlayer->checkpoint2triggered = 0;
		NewPlayer->checkpoint2triggered = 0;		
		NewPlayer->deathDuration = 15.0f;

		return NewPlayer;
	}
	else
	{
		return NULL;
	}
}

void PlayerSetXcoordinate(PlayerPtr player, float x)
{
	if (player)
	{
		player->PlayerXcoordinate = x;
	}
}

void PlayerSetYcoordinate(PlayerPtr player, float y)
{
	if (player)
	{
		player->PlayerYcoordinate = y;
	}
}


float PlayerGetXcoordinate(PlayerPtr player)
{
	if (player)
	{
		return player->PlayerXcoordinate;
	}
	else
	{
		return 0.0f;
	}
}

CharacterPtr PlayerGetCharacter(PlayerPtr player)
{
	if (player)
	{
		return player->character;
	}
	else
	{
		return NULL;
	}
}

float PlayerGetYcoordinate(PlayerPtr player)
{
	if (player)
	{
		return player->PlayerYcoordinate;
	}
	else
	{
		return 0.0f;
	}
}

void PlayerFree(PlayerPtr player)
{
	if (player)
	{
		CharacterFree(player->character);
		free(player);
		player = NULL;
	}
}

void PlayerSetCurrentTextureOffset(PlayerPtr player, int x)
{
	if (player)
	{
		player->currentTextureOffset = x;
	}
}

int PlayerGetCurrentTextureOffset(PlayerPtr player)
{
	if (player)
	{
		return player->currentTextureOffset;
	}
	else
	{
		return 0;
	}
}

void PlayerSetFrameIndex(PlayerPtr player, float x, float y, int frame)
{
	if (player)
	{	
		player->textureOffsets[frame].mX = x;				
		player->textureOffsets[frame].mY = y;
	}
}


float PlayerGetFrameIndexX(PlayerPtr player)
{
	if (player)
	{
		return player->textureOffsets[player->currentTextureOffset].mX;
	}
	else
	{
		return 0.0f;
	}
}

float PlayerGetFrameIndexY(PlayerPtr player)
{
	if (player)
	{
		return player->textureOffsets[player->currentTextureOffset].mY;
	}
	else
	{
		return 0.0f;
	}

}
int GetPlayertriggered1stcheckpoint(PlayerPtr player)
{
	if (player)
	{
		return player->checkpoint1triggered;
	}
	else
	{
		return 0;
	}
}
void SetPlayertriggered1stcheckpoint(PlayerPtr player, int zeroorone)
{
	if (player)
	{

		player->checkpoint1triggered = zeroorone;
	}

}

int GetPlayertriggered2ndcheckpoint(PlayerPtr player)
{
	if (player)
	{
		return player->checkpoint2triggered;
	}
	else
	{
		return 0;
	}
}

void SetPlayertriggered2ndcheckpoint(PlayerPtr player, int zeroorone)
{
	if (player)
	{

		player->checkpoint2triggered = zeroorone;
	}
}

void PlayerSetDeathDuration(PlayerPtr player, float duration)
{
	if (player)
	{
		player->deathDuration = duration;
	}

}

float PlayerGetDeathDuration(PlayerPtr player)
{
	if (player)
	{
		return player->deathDuration;
	}
	else
		return 0.0f;
}//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

