//------------------------------------------------------------------------------
//
// File Name:	SnowEffect.c
// Author(s):	Deni Van Winkle
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "AEEngine.h"
#include "Particle.h"
#include "SnowEffect.h"
#include "random.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
typedef struct Snow
{
	float EffectTimer;
	ParticlePtr SnowParticleList[20];

} Snow;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
SnowPtr SnowWave1;
SnowPtr SnowWave2;
AEGfxVertexList *SnowMesh;
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------
AEGfxVertexList *SnowMeshCreate();
void SnowUpdate(SnowPtr wave);
//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------
void SnowInit()
{
	SnowWave1 = calloc(1, sizeof(Snow));
	SnowWave2 = calloc(1, sizeof(Snow));
	if (SnowWave1 && SnowWave2)
	{
		SnowWave1->EffectTimer = 0;
		SnowWave2->EffectTimer = 25;
	}
	SnowMesh = SnowMeshCreate();
	randomInit();
}

void SnowEffect(float dt)
{
	if (SnowWave1->EffectTimer <= 0)
	{
		if (SnowWave1->SnowParticleList[0])
		{
			ParticleEffectDestroy(SnowWave1->SnowParticleList, 20);
		}
		int count;
		for (count = 0; count < 20; ++count)
		{
			SnowWave1->SnowParticleList[count] = ParticleCreate(randomfloatrange(AEGfxGetWinMinX(), AEGfxGetWinMaxX()), AEGfxGetWinMaxY(),
				randomfloatrange(-5, 5), randomfloatrange(-1, -3), SnowMesh);
		}
		SnowWave1->EffectTimer = 50;
	}

	if (SnowWave2->EffectTimer <= 0)
	{
		if (SnowWave2->SnowParticleList[0])
		{
			ParticleEffectDestroy(SnowWave2->SnowParticleList, 20);
		}
		int count;
		for (count = 0; count < 20; ++count)
		{
			SnowWave2->SnowParticleList[count] = ParticleCreate(randomfloatrange(AEGfxGetWinMinX(), AEGfxGetWinMaxX()), AEGfxGetWinMaxY(),
				randomfloatrange(-5, 5), randomfloatrange(-1, -3), SnowMesh);
		}
		SnowWave2->EffectTimer = 50;
	}

	if (SnowWave1->EffectTimer > 0)
	{
		SnowUpdate(SnowWave1);
		SnowWave1->EffectTimer -= dt;
	}

	if (SnowWave2->EffectTimer > 0)
	{
		SnowWave2->EffectTimer -= dt;
		if (SnowWave2->SnowParticleList[0])
		{
			SnowUpdate(SnowWave2);
		}
	}
}

void SnowFree()
{
	if (SnowWave1)
	{
		free(SnowWave1);
		SnowWave1 = NULL;
	}
	// Frees the second on separately incase one failed to be allocated
	if (SnowWave2)
	{
		free(SnowWave2);
		SnowWave2 = NULL;
	}

	AEGfxMeshFree(SnowMesh);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
AEGfxVertexList *SnowMeshCreate()
{
	AEGfxMeshStart();

	AEGfxTriAdd(
		-3.0f, -3.0f, 0xFFBDEDFF, 0.0f, 0.0f,
		3.0f, -3.0f, 0xFFBDEDFF, 0.0f, 0.0f,
		-3.0f, 3.0f, 0xFFBDEDFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		3.0f, -3.0f, 0xFFBDEDFF, 0.0f, 0.0f,
		3.0f, 3.0f, 0xFFBDEDFF, 0.0f, 0.0f,
		-3.0f, 3.0f, 0xFFBDEDFF, 0.0f, 0.0f);

	return AEGfxMeshEnd();
}

void SnowUpdate(SnowPtr wave)
{
	int count;
	for (count = 0; count < 20; ++count)
	{
		ParticleSetXPosition(wave->SnowParticleList[count], ParticleGetXPosition(wave->SnowParticleList[count]) + ParticleGetXVelocity(wave->SnowParticleList[count]));
		ParticleSetYPosition(wave->SnowParticleList[count], ParticleGetYPosition(wave->SnowParticleList[count]) + ParticleGetYVelocity(wave->SnowParticleList[count]));
		ParticleDraw(wave->SnowParticleList[count], 0.75f);
	}
}
