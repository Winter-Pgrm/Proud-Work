//------------------------------------------------------------------------------
//
// File Name:	physics.h
// Author(s):	Ian Gaitheer
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Stub.h"
#include "Player.h"
#include "physics.h"
#include "collision.h"
#include "AEEngine.h"

#include "Soundfunctions.h"
#include "Hook.h"
#include "Vector2D.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

static const float xAccelRate = 0.06f;
static const float xAccelMax = 3.0f;
static const float xDecelRate = 0.2f;
static const float yAccelRate = 0.02f;
static const float yAccelMax = 5.0f;

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

static float xvelocity = 0.0f;
static float yvelocity = 0.0f;
static float xaccel = 0.0f;
static float yaccel = 0.0f;
static s32 sx;
static s32 sy;
static int Alexjumpsflap = 0;
static int triggeredhooksound = 0;
static float sounddel = 0;
static float soundjumpdel = 0;
static int jumpCheck = 0;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void HandleCollision(const CollisionData * collision);
static void UpdateVelocity();
static void UpdateAccel();

static void UpdateHookVelocity();

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

void physicsUpdate(PlayerPtr player)
{

	float x = PlayerGetXcoordinate(player);
	float y = PlayerGetYcoordinate(player);

	sounddel -= .16f;
	soundjumpdel -= .16f;

	if (CharacterGetLives(PlayerGetCharacter(player)) == 1)
	{
		UpdateVelocity();
		UpdateAccel();

		//if player is below the grapple point
		if (hookAnchorStatus() && PlayerGetYcoordinate(player) > currentHookY())
		{
			HookReset();
		}
		else if ((AEInputCheckCurr('A')) || (AEInputCheckCurr('D')))
		{
			xvelocity += xaccel;
		}
		else if (hookAnchorStatus())
		{
			//decell
			if (PlayerGetXcoordinate(player) > currentHookX())
			{
				xvelocity = -5.0f;
				if (PlayerGetXcoordinate(player) + xvelocity < currentHookX())
				{
					xvelocity = 0;
					PlayerSetXcoordinate(player, currentHookX());
				}
			}
			else if (PlayerGetXcoordinate(player) < currentHookX())
			{
				xvelocity = 5.0f;
				if (PlayerGetXcoordinate(player) + xvelocity > currentHookX())
				{
					xvelocity = 0;
					PlayerSetXcoordinate(player, currentHookX());
				}
			}
		}
		else
		{
			if (xvelocity > 0)
			{
				xvelocity = 3.0f + xaccel;

				if (xvelocity < 0)
				{
					xvelocity = 0;
					xaccel = 0;
				}
			}
			else if (xvelocity < 0)
			{
				xvelocity = -3.0f + xaccel;

				if (xvelocity > 0)
				{
					xvelocity = 0;
					xaccel = 0;
				}
			}
			
		}
		//if hook is attached and moving set xvel in normal from player->radius
		if (hookAnchorStatus() && xvelocity != 0)
		{
			//dissable gravity while hooked
			yaccel = 0;
			//Vector from the player to the anchor point
			Vector2D radiusVector = { currentHookX() - PlayerGetXcoordinate(player), currentHookY() - PlayerGetYcoordinate(player) };
			//Unit Vector in above direction
			Vector2D unitVec = { 0,0 };
			//Calc unit vector
			Vector2DNormalize(&unitVec, &radiusVector);
			//Scale vector by velocity in normal direction from radius vector
			Vector2D newVelocity = { 0,0 };
			Vector2DScale(&newVelocity, &unitVec, xvelocity);
			xvelocity = newVelocity.y;
			yvelocity = -newVelocity.x;
		}
		//gravity
		else if (yvelocity > -yAccelMax)
		{
			yvelocity += yaccel;
		}

		//map velocity to hook radius
		if (hookAnchorStatus())
		{
			HookMapToRadius(player, &xvelocity, &yvelocity);
		}
	}
	else
	{
		yaccel = 0.0f;
		yvelocity = 0.0f;
		xvelocity = 0.0f;
	}

	CollisionData finalData = { 0 };
	PlayerCollision(player, xvelocity, yvelocity, &finalData);
	HandleCollision(&finalData);

	if (AEInputCheckCurr('G'))
	{
		float worldX = 0, worldY = 0;
		AEInputGetCursorPosition(&sx, &sy);
		AEGfxConvertScreenCoordinatesToWorld((float)sx, (float)sy, &worldX, &worldY);
		PlayerSetXcoordinate(player, worldX);
		PlayerSetYcoordinate(player, worldY);
		//grapple(sx, sy, &x, &y);
	}
	else
	{
		x += xvelocity;
		y += yvelocity;
		PlayerSetXcoordinate(player, x);
		PlayerSetYcoordinate(player, y);
	}

	if (hookActiveStatus())
	{
		HookPhysicsUpdate(player);
		if (hookAnchorStatus() == true && triggeredhooksound == 0)
		{
			//playsoundgrappleattach();
			triggeredhooksound = 1; /*Alex function area*/
		}
		else if (hookAnchorStatus == false && triggeredhooksound == 1)
			triggeredhooksound = 0;
	}
}

//cheat tool


void reset()
{
	yvelocity = 0.0f;
	yaccel = 0.0f;
}


//------------------------------------------------------------------------------
// Private Functions:
//-----------------------------------------------------------------------------

static void HandleCollision(const CollisionData * collision)
{
	if (hookAnchorStatus())
	{
		if (collision->down == true)
		{
			yaccel = 0;
			yvelocity = (float)collision->yColVel;
			Alexjumpsflap = 0;
			xvelocity = 0;
		}
		else if (collision->up)
		{
			yvelocity = (float)collision->yColVel;
			xvelocity = 0;
		}

		if (collision->left || collision->right)
		{
			xvelocity = (float)collision->xColVel;
			yvelocity = 0;
		}
	}
	else
	{
		if (collision->down == true)
		{
			yaccel = 0;
			yvelocity = (float)collision->yColVel;
			Alexjumpsflap = 0;
			jumpCheck = 1; //reset whenever grounded
		}
		else if (collision->up)
		{
			yvelocity = (float)collision->yColVel;
		}

		if (collision->left == true || collision->right == true)
		{
			xvelocity = (float)collision->xColVel;
		}
	}
}

static void UpdateVelocity()
{
	if ((AEInputCheckTriggered('W') || AEInputCheckTriggered(VK_SPACE)) && !hookAnchorStatus())
	{
		if (jumpCheck != 0) //set for double jump
		{
			yvelocity = 7.0f;
			jumpCheck = 0; //checks number of jumps

			if (soundjumpdel <= 0)
			{
				playsoundjump(true);
				soundjumpdel = 3.0f;
				Alexjumpsflap = 1;
			}
		}
	}
	if (AEInputCheckCurr('A'))
	{
		xvelocity = -3.0f;
		
		if (sounddel <= 0 && Alexjumpsflap == 0)
		{
			if (hookActiveStatus() == FALSE)
			{
				playsoundwalk();
			}
			
			sounddel = 1.5f;
		}
	}
	else if (AEInputCheckCurr('D'))
	{
		xvelocity = 3.0f;

		if (sounddel <= 0 && Alexjumpsflap == 0)
		{
			if (hookActiveStatus() == FALSE)
			{
				playsoundwalk();
			}
			sounddel = 1.5f;
		}
	}
}

static void UpdateAccel()
{
	if (hookAnchorStatus())
	{
		yaccel = 0;
	}
	else if (yaccel > -yAccelMax)
	{
		yaccel -= yAccelRate;
	}

	if (AEInputCheckCurr('A'))
	{
		//maintain and reverse accel
		if (xaccel > 0)
		{
			xaccel = -xaccel;
		}

		//cap accel
		if (xaccel > -xAccelMax)
		{
			xaccel -= xAccelRate;
		}
	}
	else if (AEInputCheckCurr('D'))
	{
		if (xaccel < 0)
		{
			xaccel = -xaccel;
		}

		if (xaccel < xAccelMax)
		{
			xaccel += xAccelRate;
		}
	}
	else
	{
		if (xvelocity > 0 && !hookAnchorStatus())
		{
			xaccel -= xDecelRate;
		}
		else if (xvelocity < 0 && !hookAnchorStatus())
		{
			xaccel += xDecelRate;
		}
	}
}

static void UpdateHookVelocity()
{
	if (true)
	{
		xvelocity = 0;
	}
}

float getXVelocity()
{
	return xvelocity;
}

float getYVelocity()
{
	return yvelocity;
}

