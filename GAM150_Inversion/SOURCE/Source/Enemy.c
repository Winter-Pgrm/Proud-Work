//------------------------------------------------------------------------------
//
// File Name:	Enemy.c
// Author(s):	Deni Van Winkle
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Player.h"
#include "Enemy.h"
#include "Vector2D.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
typedef struct Enemy
{
	 // starting x position for the enemy object
	float StartingX;
	 // starting y position for the enemy object
	float StartingY;
	 // Where the enemy is going to travel too and back from
	float XBoundary;
	float YBoundary;

	float CurrentX;
	float CurrentY;
	// THe velocity that the Enemy will move at
	float Xvelocity;
	float Yvelocity;

	CharacterPtr character;
	AEGfxVertexList *EnemyMesh;

} Enemy;
//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
bool forward = true;
int YMovement = 0;
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------
void EnemyDraw(EnemyPtr enemy);
AEGfxVertexList *EnemyMeshCreate();
//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------
EnemyPtr EnemyCreate(char * name, float startingX, float startingY, float Boundaryoffset)
{
	EnemyPtr NewEnemy;
	NewEnemy = calloc(1, sizeof(Enemy));
	if (NewEnemy)
	{
		NewEnemy->character = CharacterCreate(name, NULL, 1);
		NewEnemy->StartingX = startingX;
		NewEnemy->StartingY = startingY;
		NewEnemy->CurrentX = startingX;
		NewEnemy->CurrentY = startingY;

		NewEnemy->XBoundary = startingX + Boundaryoffset;
		NewEnemy->YBoundary = startingY + Boundaryoffset;
		NewEnemy->Xvelocity = 10;
		NewEnemy->Yvelocity = 5;

		NewEnemy->EnemyMesh = EnemyMeshCreate();
		return NewEnemy;
	}
	else
	{
		return NULL;
	}
}

void FreeEnemy(EnemyPtr enemy)
{
	if (enemy)
	{
		CharacterFree(enemy->character);
		free(enemy);
		enemy = NULL;
	}
}

CharacterPtr EnemyGetCharacter(EnemyPtr enemy)
{
	if (enemy)
	{
		return enemy->character;
	}
	else
	{
		return NULL;
	}
}

float EnemyGetstartingX(EnemyPtr enemy)
{
	if (enemy)
	{
		return enemy->StartingX;
	}
	else
	{
		return 0.0f;
	}
}

float EnemyGetstartingY(EnemyPtr enemy)
{
	if (enemy)
	{
		return enemy->StartingY;
	}
	else
	{
		return 0.0f;
	}
}

float EnemyGetXBoundary(EnemyPtr enemy)
{
	if (enemy)
	{
		return enemy->XBoundary;
	}
	else
	{
		return 0.0f;
	}
}

float EnemyGetYBoundary(EnemyPtr enemy)
{
	if (enemy)
	{
		return enemy->YBoundary;
	}
	else
	{
		return 0.0f;
	}
}

float EnemyGetXVelocity(EnemyPtr enemy)
{
	if (enemy)
	{
		return enemy->Xvelocity;
	}
	else
	{
		return 0.0f;
	}
}

float EnemyGetYVelocity(EnemyPtr enemy)
{
	if (enemy)
	{
		return enemy->Yvelocity;
	}
	else
	{
		return 0.0f;
	}
}

void EnemySetStartingX(EnemyPtr enemy, float x)
{
	if (enemy)
	{
		enemy->StartingX = x;
	}
}

void EnemySetStartingY(EnemyPtr enemy, float y)
{
	if (enemy)
	{
		enemy->StartingY = y;
	}
}

void EnemySetXBoundary(EnemyPtr enemy, float x)
{
	if (enemy)
	{
		enemy->XBoundary = x;
	}
}

void EnemySetYBoundary(EnemyPtr enemy, float y)
{
	if (enemy)
	{
		enemy->YBoundary = y;
	}
}

void EnemySetXvelocity(EnemyPtr enemy, float x)
{
	if (enemy)
	{
		enemy->Xvelocity = x;
	}
}

void EnemySetYvelocity(EnemyPtr enemy, float y)
{
	if (enemy)
	{
		enemy->Yvelocity = y;
	}
}

void EnemyUpdate(EnemyPtr enemy, float dt)
{
	if (enemy)
	{
		if (forward == true)
		{
			enemy->CurrentX += enemy->Xvelocity * dt;
			if (enemy->CurrentX >= enemy->XBoundary)
			{
				forward = false;
			}
		}
		else if (forward == false)
		{
			enemy->CurrentX -= enemy->Xvelocity * dt;
			if (enemy->CurrentX <= enemy->StartingX)
			{
				forward = true;
			}
		}

		if (YMovement == 1)
		{
			enemy->CurrentY += enemy->Yvelocity * dt;
			if (enemy->CurrentY >= enemy->YBoundary)
			{
				YMovement = 2;
			}
		}
		else if (YMovement == 2)
		{
			enemy->CurrentY -= enemy->Yvelocity * dt;
			if (enemy->CurrentY <= enemy->StartingY)
			{
				YMovement = 1;
			}
		}

		if (CharacterGetLives(enemy->character) <= 0)
		{
			FreeEnemy(enemy);
		}
		EnemyDraw(enemy);
	}
}


bool EnemyCollision(PlayerPtr player, EnemyPtr enemy)
{
	float radius1 = 25;
	float radius2 = 20;

	Vector2D playerPosition = { PlayerGetXcoordinate(player), PlayerGetYcoordinate(player) };
	Vector2D enemyPosition = { enemy->CurrentX, enemy->CurrentY };

	float length = Vector2DDistance(&playerPosition, &enemyPosition);
	if (length - radius1 - radius2 < 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

AEGfxVertexList *EnemyMeshCreate()
{
	AEGfxMeshStart();

	AEGfxTriAdd(
		-20.0f, -20.0f, 0xFF602040, 0.0f, 0.0f,
		20.0f, -20.0f, 0xFFF1000, 0.0f, 0.0f,
		-20.0f, 20.0f, 0xFF20FF50, 0.0f, 0.0f);

	AEGfxTriAdd(
		20.0f, -20.0f, 0xFF602040, 0.0f, 0.0f,
		20.0f, 20.0f, 0xFFF1000, 0.0f, 0.0f,
		-20.0f, 20.0f, 0xFF20FF50, 0.0f, 0.0f);

	return AEGfxMeshEnd();
}

void EnemyDraw(EnemyPtr enemy)
{

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetFullTransformWithZOrder(enemy->CurrentX, enemy->CurrentY, 0.0f, 0.0f, 1.0f, 1.0f);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(enemy->EnemyMesh, AE_GFX_MDM_TRIANGLES);

}
