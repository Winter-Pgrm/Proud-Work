//------------------------------------------------------------------------------
//
// File Name:	LevelManager.h
// Author(s):	Ian Gaither ian.gaither
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

#include "Player.h"

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

	//Bitmap File Structs//

	#pragma pack(push)  // push current structure packing onto stack
	#pragma pack(1)     // set packing to 1 byte, necessary to read bitmap file correctly
	typedef struct BitmapHeader
	{
		unsigned short int FileType;
		unsigned int FileSize;
		unsigned short int Reserved1;
		unsigned short int Reserved2;
		unsigned int ImageOffset;
		unsigned int HeaderSize;
		int Width; //Image Width, Displayed at 1:1
		int Height; //Image Height, Displayed at 1:1
		unsigned short int Planes;
		unsigned short int Bits;
		unsigned int Compression;
		unsigned int ImageSize;
		int xResolution;
		int yResolution;
		unsigned int Colors;
		unsigned int ImportantColors;
	} BitmapHeader;

	typedef struct PixelData
	{
		unsigned char B;
		unsigned char G;
		unsigned char R;
	}PixelData;
	#pragma pack(pop)   // restore packing data
	//////////////////////

	typedef struct LightningData
	{
		float rotation;
		float length;
		float centerX;
		float centerY;
	}LightningData;

	//------------------------------------------------------------------------------
	// Public Variables:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	//open levels and save leveldata
	void LevelManagerInit(PlayerPtr player);

	//level index starting from 0
	void LevelManagerChangeLevel(PlayerPtr player, unsigned newIndex);
	
	const char * GetBlueImageName();

	const char * GetRedImageName();

	// Returns the pixel data for the current level
	const PixelData *** GetCurrentLevelCollisionData();

	// Returns the header for the current level
	const BitmapHeader * GetCurrentLevelImageHeader();

	unsigned GetCurrentLevelIndex();

	const AEVec2* GetStartPoint();

	const AEVec2* GetEndPoint();

	float * GetCheckpoints();

	float * GetLineBounds();

	int GetLevelNumLines();

	LightningData * GetLightningData();

	/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

