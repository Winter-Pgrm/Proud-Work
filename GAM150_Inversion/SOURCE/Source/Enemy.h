//------------------------------------------------------------------------------
//
// File Name:	Enemy.h
// Author(s):	Deni Van Winkle
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "Player.h"

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
	typedef struct Enemy* EnemyPtr;
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------
	EnemyPtr EnemyCreate(char * name, float startingX, float startingY, float Boundaryoffset);

	void FreeEnemy(EnemyPtr enemy);

	CharacterPtr EnemyGetCharacter(EnemyPtr enemy);
	
	float EnemyGetstartingX(EnemyPtr enemy);

	float EnemyGetstartingY(EnemyPtr enemy);

	float EnemyGetXBoundary(EnemyPtr enemy);

	float EnemyGetYBoundary(EnemyPtr enemy);

	float EnemyGetXVelocity(EnemyPtr enemy);

	float EnemyGetYVelocity(EnemyPtr enemy);

	void EnemySetStartingX(EnemyPtr enemy, float x);

	void EnemySetStartingY(EnemyPtr enemy, float y);

	void EnemySetXBoundary(EnemyPtr enemy, float x);

	void EnemySetYBoundary(EnemyPtr enemy, float y);

	void EnemySetXvelocity(EnemyPtr enemy, float x);

	void EnemySetYvelocity(EnemyPtr enemy, float y);

	void EnemyUpdate(EnemyPtr enemy, float dt);

	bool EnemyCollision(PlayerPtr player, EnemyPtr enemy);


	/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

