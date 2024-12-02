#pragma once
//------------------------------------------------------------------------------
//
// File Name:	Death.h
// Author(s):	Brian Lu
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "AEEngine.h"
#include "Player.h"
#include "Checkpoint.h"

void deathCheck(PlayerPtr player, float x, float y, float dt);

static void deathAnimation(PlayerPtr player);

void deathInit();
void deathUpdate(PlayerPtr player);
void deathShutdown();