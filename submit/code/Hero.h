/***********************************************************************
 * File: Hero.h
 * Author: Raymin, Tone-yeah
 * Create Date: - -
 * Editor: Raymin, Tone-yeah
 * Update Date: 2023/06/04
 * Description: This header is to store Hero class
***********************************************************************/

#pragma once

#include "main.h"
#include "Position.h"
#include "invalidLocation.h"

class Hero {

private:
	Position	sPos;			// Hero location
	char sIcon = 'H';	// Hero icon
	int	hp;
	int	sLevel = 1;     // Level
	int	sMaxExp;		// Level update experience
	int	sCurrentExp;	// current exp hero has
	int power = 10;

public:
	// default constructor
	Hero() {
		this->sPos.x = 0;
		this->sPos.y = 0;
		this->sLevel = 1;
		this->sCurrentExp = 0;
		this->sMaxExp = 15;
		this->sIcon = 'H';
		this->hp = 100;
		this->power = 10;
	};
	// setting constructor
	Hero(int x, int y, int level = 1, int maxExp = 15, int currentExp = 0, char icon = 'H', int hp = 100, int power = 10) {
		this->sPos.x = x;
		this->sPos.y = y;
		this->sLevel = level;
		this->sCurrentExp = currentExp;
		this->sMaxExp = maxExp;
		this->sIcon = icon;
		this->hp = hp;
		this->power = power;
	};

	// Setting constructor
	Hero(Position& pos, int level = 1, int maxExp = 15, int currentExp = 0, char icon = 'H', int hp = 100, int power = 10) {
		this->sPos = pos;
		this->sLevel = level;
		this->sCurrentExp = currentExp;
		this->sMaxExp = maxExp;
		this->sIcon = icon;
		this->hp = hp;
		this->power = power;
	};

	// Set position
	void setPos(Position pos) { this->sPos = pos; }
	void setPos(int x, int y) {
		this->sPos.x = x;
		this->sPos.y = y;
	}

	void setIcon(char& icon) { this->sIcon = icon; }

	void setLevel(int level) { this->sLevel = level; }

	void setExp(int exp) { this->sCurrentExp = exp; }

	void SetMaxExp(int maxexp) { this->sMaxExp = maxexp; }

	void setHP(int hp) { this->hp = hp; }

	void setPower(int power) { this->power = power; }

	Position getPos(void) { return this->sPos; }

	char getIcon(void) { return this->sIcon; }

	int getLevel(void) { return this->sLevel; }

	int getExp(void) { return this->sCurrentExp; }

	int getMaxExp(void) { return this->sMaxExp; }

	int getHP() const { return this->hp; }
	
	int getPower() { return this->power; }

	void move(Position next);

	void gainEXP(int points);

	void damage(int points);

	void gainHp(int points);

	void levelUp();
};
