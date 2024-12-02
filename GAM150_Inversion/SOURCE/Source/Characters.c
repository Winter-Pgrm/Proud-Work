//------------------------------------------------------------------------------
//
// File Name:	Characters.c
// Author(s):	Deni Van Winkle
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "AEEngine.h"
#include "Characters.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
typedef struct Character
{
	// The type of character such as Player or Enemy
	const char * name;

	// The texture file for the character
	AEGfxTexture *CharacterTexture;

	// The life of the character 0 if dead 1 if alive
	int alive;

	int prev; //previous color 0 red 1 blue
} Character;
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
CharacterPtr CharacterCreate(char * name, char * Texture, int Lives)
{
	CharacterPtr NewCharacter;
	NewCharacter = calloc(1, sizeof(Character));
	if (NewCharacter)
	{
		NewCharacter->name = name;
		NewCharacter->alive = Lives;
		NewCharacter->prev = 1;
		if (Texture != NULL)
		{
			NewCharacter->CharacterTexture = AEGfxTextureLoad(Texture);
		}
		return NewCharacter;
	}
	else
	{
		return NULL;
	}
}

void CharacterSetName(CharacterPtr character, char * name)
{
	if (character)
	{
		character->name = name;
	}
}

void CharacterSetTexture(CharacterPtr character, char * Texture)
{
	if (character)
	{
		character->CharacterTexture = AEGfxTextureLoad(Texture);
	}
}

void CharacterSetLives(CharacterPtr character, int Lives)
{
	if (character)
	{
		character->alive = Lives;
	}
}
int CharacterGetPrev(CharacterPtr character)
{
	if (character)
	{
		return character->prev;
	}
	else
		return 0;
}
void CharacterSetPrev(CharacterPtr character, int prev)
{
	if (character)
	{
		character->prev = prev;
	}
}
const char * CharacterGetName(CharacterPtr character)
{
	if (character)
	{
		return character->name;
	}
	else
	{
		return NULL;
	}
}

AEGfxTexture * CharacterGetTexture(CharacterPtr character)
{
	if (character)
	{
		return character->CharacterTexture;
	}
	else
	{
		return NULL;
	}
}

int CharacterGetLives(CharacterPtr character)
{
	if (character)
	{
		return character->alive;
	}
	else
		return 0;
}

void CharacterFree(CharacterPtr character)
{
	if (character)
	{
		free(character);
		character = NULL;
	}
}


//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

