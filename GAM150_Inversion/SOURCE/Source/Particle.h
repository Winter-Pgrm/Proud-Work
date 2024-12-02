//------------------------------------------------------------------------------
//
// File Name:	Particle.h
// Author(s):	Deni Van Winkle
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

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
	typedef struct Particle* ParticlePtr;
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------
	ParticlePtr ParticleCreate(float Startingx, float Startingy, float particleXVelocity, float particleYVelocity, AEGfxVertexList *ParticleMesh);

	void ParticleEffectStart(int NumParticles, float Startingx, float Startingy);

	void ParticleEffectUpdate(float dt);

	void ParticleEffectDestroy();

	void ParticleDraw(ParticlePtr particle, float Transparency);

	float ParticleGetXPosition(ParticlePtr particle);

	float ParticleGetYPosition(ParticlePtr particle);

	float ParticleGetXVelocity(ParticlePtr particle);

	float ParticleGetYVelocity(ParticlePtr particle);

	void ParticleSetXPosition(ParticlePtr particle, float Position);

	void ParticleSetYPosition(ParticlePtr particle, float Position);

	void ParticleEffectInit();

	void ParticleFree();

	/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif
