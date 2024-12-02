//------------------------------------------------------------------------------
//
// File Name:	Camera.c
// Author(s):	Brian Lu, Fengchao Xie
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "AEEngine.h"
#include "Player.h"
#include "LevelManager.h"
#include "Camera.h"
//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
static f32 camYsize;
static f32 camXsize;
static float CamXOrigin;
static float CamYOrigin;
const BitmapHeader *size;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------



// Save camera origin
void CameraInit(PlayerPtr player)
{
	AEGfxSetCamPosition(0, 0);
	camXsize = AEGfxGetWinMaxX();
	camYsize = AEGfxGetWinMaxY();
	//AEGfxGetCamPosition(&CamXOrigin, &CamYOrigin);
	float playerX = PlayerGetXcoordinate(player);
	float playerY = PlayerGetYcoordinate(player);
	CamXOrigin = playerX;
	CamYOrigin = playerY;
	AEGfxSetCamPosition(CamXOrigin, CamYOrigin);
}

// Update Camera
void CameraUpdate(float playerX, float playerY)
{
	float camX, camY, height, width;
	AEGfxGetCamPosition(&camX, &camY); //current cam pos
	//camX - winMinx then setcam 
	//cam y + winmaxy then setcam = player x, y = height/2 - camYsize
	
	size = GetCurrentLevelImageHeader(); 
	height = (float)size->Height * 2; //size of the map
	width = (float)size->Width * 2; //size of the map
		// right                          left                               top                                bottom
	if (playerX + camXsize < width / 2 && playerX - camXsize > -width / 2 && playerY + camYsize < height / 2 && playerY - camYsize > -height / 2)
	{
		AEGfxSetCamPosition(playerX, playerY);
	}
	else if (playerY + camYsize > height / 2 && playerX - camXsize < -width / 2 ) //top left
	{
		AEGfxSetCamPosition((-width / 2 + camXsize), (height / 2 - camYsize));
	}
	else if (playerY + camYsize > height / 2 && playerX + camXsize > width / 2 ) //top right
	{
		AEGfxSetCamPosition((width / 2 - camXsize), (height / 2 - camYsize));
	}
	else if (playerY - camYsize < -height / 2 && playerX - camXsize < -width / 2 ) //bottom left
	{
		AEGfxSetCamPosition((-width / 2 + camXsize), (-height / 2 + camYsize));
	}
	else if (playerY - camYsize < -height / 2 && playerX + camXsize > width / 2) //bottom right
	{
		AEGfxSetCamPosition((width / 2 - camXsize), (-height / 2 + camYsize));
	}
	else if (playerY + camYsize > height / 2) //top
	{
		AEGfxSetCamPosition(playerX, (height / 2 - camYsize));
	}
	else if (playerY - camYsize < -height / 2) //bottom
	{
		AEGfxSetCamPosition(playerX, (-height / 2 + camYsize));
	}
	else if (playerX + camXsize > width / 2) //right
	{
		AEGfxSetCamPosition((width / 2 - camXsize), playerY);
	}
	else if (playerX - camXsize < -width / 2) //left
	{
		AEGfxSetCamPosition((-width / 2 + camXsize), playerY);
	}
}

void CameraReset()
{
	AEGfxSetCamPosition(CamXOrigin, CamYOrigin);
}

void CameraResetOrigin()
{
	AEGfxSetCamPosition(0, 0);
}

void CameraGetDelta(f32 * deltaCamX, f32 * deltaCamY)
{
	f32 CameraX = 0, CameraY = 0;
	AEGfxGetCamPosition(&CameraX, &CameraY);
	*deltaCamX = CameraX - CamXOrigin;
	*deltaCamY = CameraY - CamYOrigin;
}
//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

