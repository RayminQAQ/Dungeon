/***********************************************************************
 * File: main.h
 * Author: Raymin, Tone-yeah
 * Create Date: - -
 * Editor: Raymin, Tone-yeah
 * Update Date: 2023/06/04
 * Description: This header is to store main included header
***********************************************************************/

#pragma once
#include "Position.h"

void updateKey(bool gKeyState[]);
bool isPositionValid(const Position& pos, const std::vector<std::vector<char>>& board, const std::vector<Position>& poss);