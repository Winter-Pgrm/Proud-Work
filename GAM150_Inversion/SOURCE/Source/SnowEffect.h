//------------------------------------------------------------------------------
//
// File Name:	SnowEffect.h
// Author(s):	Deni Van Winkle
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright � 2017 DigiPen (USA) Corporation.
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
	typedef struct Snow* SnowPtr;
	//------------------------------------------------------------------------------
	// Public Variables:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------
	void SnowInit();

	void SnowEffect(float dt);

	void SnowFree();

	/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

