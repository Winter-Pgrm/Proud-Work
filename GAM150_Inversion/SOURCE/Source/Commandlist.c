//------------------------------------------------------------------------------
//
// File Name:	Commandlist.c
// Author(s):	Alexander Phillips
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright � 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Commandlist.h"
#include "AEEngine.h"
#include "physics.h"
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

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------


int getinput()
{

	if (AEInputCheckCurr(VK_LBUTTON))
	{
		return 1;
	}
	else if (AEInputCheckCurr(VK_RBUTTON))
	{
		return 2;
	}
	else
	{
		return 0;
	}
}
//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
