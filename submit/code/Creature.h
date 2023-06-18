/***********************************************************************
 * File: Creature.h
 * Author: Raymin, Tone-yeah
 * Create Date: - -
 * Editor: Raymin, Tone-yeah
 * Update Date: 2023/06/04
 * Description: This header is to store Creature base class
***********************************************************************/

#pragma once
#include "Position.h"
#include "Hero.h"
#include "main.h"
#include "Color.h"

#include <iostream>
#include <conio.h>
#include <vector>

class Creature {
public:
	bool isAlive = false;
	Position pos;
	char icon = 'C';
	int power;
	int hp;

	// Default constructor
	Creature() {
		this->isAlive = true;
		this->pos.x = 1;
		this->pos.y = 1;
		this->icon = 'C';
		this->power = 5;
		this->hp = 10;
	}

	//setting constructor
	Creature(Position pos, char icon, int power, int hp) {
		this->isAlive = true;
		this->pos = pos;
		this->icon = icon;
		this->power = power;
		this->hp = hp;
	}

	// setter and getter
	void setPos(Position pos) { this->pos = pos; }
	void setPos(int x, int y) {
		this->pos.x = x;
		this->pos.y = y;
	}

	void setIcon(const char& icon) { this->icon = icon; }

	void setPower(const int& power) { this->power = power; }

	void setHp(const int& hp) { this->hp = hp; }

	Position getPos(void) { return this->pos; }

	char getIcon(void) { return this->icon; }

	int getPower() { return this->power; }

	int getHp() { return this->hp; }

	void update(Hero& hero, bool& deleteCreature);

	virtual void move(const std::vector<std::vector<char>>& board, const std::vector<Creature*>& creatures, Hero& hero) = 0;
	
	// battle, by default in base class is void RockPaperSisisor();
	virtual void battle(Hero& hero, bool& deleteCreature);
};


