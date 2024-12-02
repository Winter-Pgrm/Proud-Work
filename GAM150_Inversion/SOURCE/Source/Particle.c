//------------------------------------------------------------------------------
//
// File Name:	Particles.c
// Author(s):	Deni Van Winkle
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright © 1017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "AEEngine.h"
#include "Enemy.h"
#include "Particle.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
typedef struct Particle
{
	float LifeTimer;
	  // The starting position
	float XPosition;
	float YPosition;
	  // Velocity for the particles to move
	float VelocityX;
	float VelocityY;

	AEGfxVertexList *ParticleMesh;

} Particle;
//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------
int ParticleNum = 0;
ParticlePtr List[10];
AEGfxVertexList *ParticleMesh;
//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------
AEGfxVertexList *ParticleMeshCreate();
//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

void ParticleEffectInit()
{
	ParticleMesh = ParticleMeshCreate();
}

ParticlePtr ParticleCreate(float Startingx, float Startingy, float particleXVelocity, float particleYVelocity, AEGfxVertexList *ParticleMeshP)
{
	ParticlePtr NewParticle = calloc(1, sizeof(Particle));
	if (NewParticle)
	{
		NewParticle->VelocityX = particleXVelocity;
		NewParticle->VelocityY = particleYVelocity;
		NewParticle->XPosition = Startingx;
		NewParticle->YPosition = Startingy;
		NewParticle->LifeTimer = 5;
		NewParticle->ParticleMesh = ParticleMeshP;
		return NewParticle;
	}
	else
	{
		return NULL;
	}
}

void ParticleEffectStart(int NumParticles, float Startingx, float Startingy)
{
	float particleXVelocities[5] = { 5, 0, -5, 2.5, -2.5 };
	float particleYVelocities[5] = { 2, 5, 2, 3.5, 3.5 };

	if (!List[0])
	{
		int count;
		for (count = 0; count < NumParticles / 2; ++count)
		{
			List[count] = ParticleCreate(Startingx, Startingy, particleXVelocities[count], particleYVelocities[count],
				ParticleMesh);
			++ParticleNum;
		}
		for (count = 0; count < NumParticles / 2; ++count)
		{
			List[count + NumParticles / 2] = ParticleCreate(Startingx, Startingy, particleXVelocities[count],
				-particleYVelocities[count], ParticleMesh);
			++ParticleNum;
		}
	}
}


void ParticleEffectUpdate(float dt)
{
	if (List[0])
	{
		int count;
		for (count = 0; count < ParticleNum; ++count)
		{
			List[count]->XPosition += List[count]->VelocityX;
			List[count]->YPosition += List[count]->VelocityY;
			ParticleDraw(List[count], 1.0f);
			List[count]->LifeTimer -= dt;
		}

		if (List[0]->LifeTimer <= 0)
		{
			ParticleEffectDestroy(List, ParticleNum);
			ParticleNum = 0;
		}
	}
}

void ParticleEffectDestroy(ParticlePtr *EffectList, int ParticleCount)
{
	int count;
	for (count = 0; count < ParticleCount; ++count)
	{
		free(EffectList[count]);
		EffectList[count] = NULL;
	}
	ParticleCount = 0;
}

void ParticleDraw(ParticlePtr particle, float Transparency)
{
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetFullTransformWithZOrder(particle->XPosition, particle->YPosition, 0.0f, 0.0f, 1.0f, 1.0f);
	AEGfxSetTransparency(Transparency);
	AEGfxMeshDraw(particle->ParticleMesh, AE_GFX_MDM_TRIANGLES);
}

float ParticleGetXPosition(ParticlePtr particle)
{
	if (particle)
	{
		return particle->XPosition;
	}
	else
	{
		return 0.0f;
	}
}

float ParticleGetYPosition(ParticlePtr particle)
{
	if (particle)
	{
		return particle->YPosition;
	}
	else
	{
		return 0.0f;
	}
}

float ParticleGetXVelocity(ParticlePtr particle)
{
	if (particle)
	{
		return particle->VelocityX;
	}
	else
	{
		return 0.0f;
	}
}

float ParticleGetYVelocity(ParticlePtr particle)
{
	if (particle)
	{
		return particle->VelocityY;
	}
	else
	{
		return 0.0f;
	}
}

void ParticleSetXPosition(ParticlePtr particle, float Position)
{
	if (particle)
	{
		particle->XPosition = Position;
	}
}

void ParticleSetYPosition(ParticlePtr particle, float Position)
{
	if (particle)
	{
		particle->YPosition = Position;
	}
}

void ParticleFree()
{
	if (ParticleMesh)
	{
		AEGfxMeshFree(ParticleMesh);
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
AEGfxVertexList *ParticleMeshCreate()
{
	AEGfxMeshStart();

	AEGfxTriAdd(
		-3.0f, -3.0f, 0xFF601365, 0.0f, 0.0f,
		3.0f, -3.0f, 0xFFF1875, 0.0f, 0.0f,
		-3.0f, 3.0f, 0xFF12FF59, 0.0f, 0.0f);

	AEGfxTriAdd(
		3.0f, -3.0f, 0xFF601376, 0.0f, 0.0f,
		3.0f, 3.0f, 0xFFF1295, 0.0f, 0.0f,
		-3.0f, 3.0f, 0xFF10F194, 0.0f, 0.0f);

	return AEGfxMeshEnd();
}


