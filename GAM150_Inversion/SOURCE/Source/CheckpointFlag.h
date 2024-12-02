//------------------------------------------------------------------------------
//
// File Name:	CheckpointFlag.h
// Author(s):	Brian Lu
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#pragma once
#include "AEEngine.h"

void FlagInit();

void FlagInit2();

void SetFlag1Unclear();

void SetFlag2Unclear();

void SetFlag1Clear();

void SetFlag2Clear();

void SetFlag1Update(float x, float y);

void SetFlag2Update(float x, float y);

void FlagShutDown();
