#include "stdafx.h"
#include "AEEngine.h"
#include "Collision.h"

static float angle = 0.0f;



void hook(s32 sx, s32 sy, float *playerX, float *playerY)
{
	AEGfxLine(*playerX, *playerY, 0, 0, 1, 1, 1, (sx - 630), (-sy + 400),1, 1, 1, 0, 0);
	angle = atan2((-sy + 400) - *playerY, (sx - 630) - *playerX);
	*playerX += cos(angle) * 3;
	*playerY += sin(angle) * 3;
}

