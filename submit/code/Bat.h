/***********************************************************************
 * File: Bat.h
 * Author: Raymin, Tone-yeah
 * Create Date: - -
 * Editor: Raymin, Tone-yeah
 * Update Date: 2023/06/04
 * Description: This header is to store Bat as derived class
***********************************************************************/

#pragma once
#include "Creature.h"
#include "Position.h"

#include "main.h"

class Bat : public Creature {
public:
	Bat() {
		this->pos = Position(0, 0);
		this->icon = 'B';
		this->power = 10;
		this->hp = 10;
	}

	Bat(Position pos, char icon, int power, int hp)
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

		int count = 0;
		while(1) {
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
			for (int i = 0; i < creatures.size(); i++) {
				if (next == creatures[i]->getPos()) inValid = true;
			}
			if (next.y <= 0 || next.y >= board.size() - 1|| next.x <= 0 || next.x >= board[0].size() - 1) inValid = true;

			if (!inValid) {
				this->pos = next;
				break;
			}

			if (count > 25) break;
		}
	}

	void bite();
};

