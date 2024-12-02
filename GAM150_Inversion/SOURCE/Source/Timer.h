//------------------------------------------------------------------------------
//
// File Name:	Timer.h
// Author(s):	Brian Lu
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#pragma once
#include"AEEngine.h"

void TimerInit(); //initiates sprites

void TimerUpdate(float dt); //updates the timer (makes it run)

void TimerReset(); //resets the timer

void TimerAnimation(float dt);

void SetFinalScore(bool final);

void UpdateScore();

void ScoreInit();

void nextLevel();

void getFastestTime();
