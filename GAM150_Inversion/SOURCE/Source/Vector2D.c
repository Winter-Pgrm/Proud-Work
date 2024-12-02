//------------------------------------------------------------------------------
//
// File Name:	Vector2D.c
// Author(s):	Deni Van Winkle
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Vector2D.h"
#define _USE_MATH_DEFINES
#include <math.h>

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

// This function sets the coordinates of the 2D vector (pResult) to 0
void Vector2DZero(Vector2D *pResult)
{
	if (pResult)
	{
		pResult->x = 0;
		pResult->y = 0;
	}
}

// This function sets the coordinates of the 2D vector (pResult) to x & y
void Vector2DSet(Vector2D *pResult, float x, float y)
{
	if (pResult)
	{
		pResult->x = x;
		pResult->y = y;
	}
}

// In this function, pResult will be set to the opposite of pVec0
void Vector2DNeg(Vector2D *pResult, const Vector2D *pVec0)
{
	if (pResult)
	{
		pResult->x = -pVec0->x;
		pResult->y = -pVec0->y;
	}
}

// In this function, pResult will be the sum of pVec0 and pVec1
void Vector2DAdd(Vector2D *pResult, const Vector2D *pVec0, const Vector2D *pVec1)
{
	if (pResult)
	{
		pResult->x = pVec0->x + pVec1->x;
		pResult->y = pVec0->y + pVec1->y;
	}
}

// In this function, pResult will be the difference between pVec0 and pVec1 (specifically, pVec0 - pVec1)
void Vector2DSub(Vector2D *pResult, const Vector2D *pVec0, const Vector2D *pVec1)
{
	if (pResult)
	{
		pResult->x = pVec0->x - pVec1->x;
		pResult->y = pVec0->y - pVec1->y;
	}
}

// In this function, pResult will be the unit vector of pVec0
void Vector2DNormalize(Vector2D *pResult, const Vector2D *pVec0)
{
	if (pResult)
	{
		float length = Vector2DLength(pVec0);
		pResult->x = pVec0->x / length;
		pResult->y = pVec0->y / length;
	}
}

// In this function, pResult will be the vector pVec0 scaled by the value 'scale'
void Vector2DScale(Vector2D *pResult, const Vector2D *pVec0, float scale)
{
	if (pResult)
	{
		pResult->x = pVec0->x * scale;
		pResult->y = pVec0->y * scale;
	}
}

// In this function, pResult will be the vector pVec0 scaled by 'scale' and added to pVec1
void Vector2DScaleAdd(Vector2D *pResult, const Vector2D *pVec0, const Vector2D *pVec1, float scale)
{
	if (pResult)
	{
		pResult->x = pVec1->x + pVec0->x * scale;
		pResult->y = pVec1->y + pVec0->y * scale;
	}
}

// In this function, pResult will be the vector pVec0 scaled by 'scale' and pVec1 will be subtracted from it
void Vector2DScaleSub(Vector2D *pResult, const Vector2D *pVec0, const Vector2D *pVec1, float scale)
{
	if (pResult)
	{
		pResult->x = pVec0->x * scale - pVec1->x;
		pResult->y = pVec0->y * scale - pVec1->y;
	}
}

// This function returns to distance between two points.
float Vector2DDistance(const Vector2D *pVec0, const Vector2D *pVec1)
{
	float result;
	result = (float)sqrt((pVec0->x - pVec1->x) * (pVec0->x - pVec1->x) + (pVec0->y - pVec1->y) * (pVec0->y - pVec1->y));
	if (result < 0)
	{
		result *= -1;
	}
	return result;
}

// This function returns to distance between two points.
// NOTE: Do not use the square root function for this function.
float Vector2DSquareDistance(const Vector2D *pVec0, const Vector2D *pVec1)
{
	return (pVec0->x + pVec1->x) * (pVec0->x + pVec1->x) + (pVec0->y + pVec1->y) * (pVec0->y + pVec1->y);
}

// This function returns the dot product between pVec0 and pVec1
float Vector2DDotProduct(const Vector2D *pVec0, const Vector2D *pVec1)
{
	return (pVec0->x * pVec1->x) + (pVec0->y * pVec1->y);
}

// This function returns the length of the vector pVec0
float Vector2DLength(const Vector2D *pVec0)
{
	float result;
	if (pVec0)
	{
		result = (float)sqrt(Vector2DSquareLength(pVec0));
		return result;
	}
	else
	{
		return 0.0f;
	}
}

// This function returns the square of pVec0's length.
// NOTE: Do not use the square root function for this function.
float Vector2DSquareLength(const Vector2D *pVec0)
{
	float result;
	if (pVec0)
	{
		result = pVec0->x  * pVec0->x + pVec0->y * pVec0->y;
		return result;
	}
	else
	{
		return 0.0f;
	}
}


// This function computes the coordinates of the vector represented by the angle "angle", which is in Degrees.
// Converting from degrees to radians can be performed as follows:
//	 radians = (angle * M_PI) / 180.0f
// M_PI is defined in "math.h", which may be included as follows:
//   #define _USE_MATH_DEFINES
//   #include <math.h>
void Vector2DFromAngleDeg(Vector2D *pResult, float angle)
{

	float radians = (float)(angle * M_PI) / 180.0f;

	Vector2DFromAngleRad(pResult, radians);
}

// This function computes the coordinates of the vector represented by the angle "angle", which is in Radians.
void Vector2DFromAngleRad(Vector2D *pResult, float angle)
{
	Vector2DZero(pResult);
	pResult->x = cosf(angle);
	pResult->y = sinf(angle);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

