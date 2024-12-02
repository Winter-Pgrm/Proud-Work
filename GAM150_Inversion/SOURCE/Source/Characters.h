//------------------------------------------------------------------------------
//
// File Name:	Character.h
// Author(s):	Deni Van Winkle
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "AEEngine.h"

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
	typedef struct Character* CharacterPtr;
	//------------------------------------------------------------------------------
	// Public Variables:
	//------------------------------------------------------------------------------
	
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------
	CharacterPtr CharacterCreate(char * name, char * Texture, int Lives);

	void CharacterSetName(CharacterPtr character, char * name);

	void CharacterSetTexture(CharacterPtr character, char * Texture);

	void CharacterSetLives(CharacterPtr character, int Lives);

	const char * CharacterGetName(CharacterPtr character);
		
	AEGfxTexture * CharacterGetTexture(CharacterPtr character);

	int CharacterGetLives(CharacterPtr character);

	void CharacterFree(CharacterPtr character);
	
	int CharacterGetPrev(CharacterPtr character);

	void CharacterSetPrev(CharacterPtr character, int prev);
	/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

