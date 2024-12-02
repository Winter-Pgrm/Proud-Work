//------------------------------------------------------------------------------
//
// File Name:	Player.h
// Author(s):	Brian Lu & Deni Van Winkle
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "Characters.h"

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
	typedef struct Player* PlayerPtr;

	//------------------------------------------------------------------------------
	// Public Variables:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------
	PlayerPtr PlayerCreate(char * name, char * Texture);

	void PlayerSetXcoordinate(PlayerPtr player, float x);

	void PlayerSetYcoordinate(PlayerPtr player, float y);

	float PlayerGetXcoordinate(PlayerPtr player);

	float PlayerGetYcoordinate(PlayerPtr player);

	CharacterPtr PlayerGetCharacter(PlayerPtr player);

	void PlayerFree(PlayerPtr player);
	
	void PlayerSetFrameIndex(PlayerPtr player, float x, float y, int frame);

	float PlayerGetFrameIndexX(PlayerPtr player);

	float PlayerGetFrameIndexY(PlayerPtr player);

	void PlayerSetCurrentTextureOffset(PlayerPtr player, int x);

	int PlayerGetCurrentTextureOffset(PlayerPtr player);

	void PlayerSetDeathDuration(PlayerPtr player, float duration);

	float PlayerGetDeathDuration(PlayerPtr player);

	int GetPlayertriggered1stcheckpoint(PlayerPtr player);
	void SetPlayertriggered1stcheckpoint(PlayerPtr player, int zeroorone);
	void SetPlayertriggered2ndcheckpoint(PlayerPtr player, int zeroorone);
	int GetPlayertriggered2ndcheckpoint(PlayerPtr player);	/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif


