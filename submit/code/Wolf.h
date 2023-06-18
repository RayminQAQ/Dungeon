/***********************************************************************
 * File: Wolf.h
 * Author: Raymin, Tone-yeah
 * Create Date: - -
 * Editor: Raymin, Tone-yeah
 * Update Date: 2023/06/04
 * Description: This header is to store Wolf as derived class
***********************************************************************/

#pragma once
#include "Position.h"
#include "Hero.h"
#include "Creature.h"

#include "main.h"

#include <iostream>

class Wolf : public Creature {
public:
	Wolf() {
		this->pos = Position(0, 0);
		this->icon = 'W';
		this->power = 15;
		this->hp = 15;
	}

	Wolf(Position pos, char icon, int power, int hp)
		: Creature(pos, icon, power, hp) {}

	void move(const std::vector<std::vector<char>>& board, const std::vector<Creature*>& creatures, Hero& hero) override {
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				Position around(pos.x + i, pos.y + j);
				if (around == hero.getPos()) {
					pos = hero.getPos();
					return;
				}
			}
		}

		std::vector<Position> poss;
		for (int i = 0; i < creatures.size(); i++) {
			poss.push_back(creatures[i]->getPos());
		}

		int count = 0;
		while (1) {
			count++;

			Position getRandomPos;
			int randomNumber = rand() % 4;
			if (randomNumber == 0) getRandomPos = Position(0, -1); // UP
			else if (randomNumber == 1) getRandomPos = Position(1, 0); // RIGHT
			else if (randomNumber == 2) getRandomPos = Position(0, 1); // DOWN
			else if (randomNumber == 3) getRandomPos = Position(-1, 0); // LEFT

			Position next = pos + getRandomPos;
			// check validation
			bool inValid = false;
			if (isPositionValid(next, board, poss)) {
				this->pos = next;
				break;
			}
			if (count > 25) break;
		}
	}

	void woof();
};