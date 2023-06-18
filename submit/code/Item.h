/***********************************************************************
 * File: Item.h
 * Author: Raymin, Tone-yeah
 * Create Date: - -
 * Editor: Raymin, Tone-yeah
 * Update Date: 2023/06/04
 * Description: This header is to store Item, as derived class
***********************************************************************/

#pragma once
#include "Position.h"
#include "Hero.h"

class Item {
public:
	char icon;
	Position pos;

	// defautlt constructor
	Item() {
		icon = ' ';
		pos = Position(0, 0);
	}

	// setting constuctor
	Item(Position pos, char icon) {
		this->icon = icon;
		this->pos = pos;
	}

	// setter
	void setIcon(char icon) { this->icon = icon; }
	void setPosition(Position pos) { this->pos = pos; }

	//getter
	char getIcon() { return icon; }
	Position getPos() { return pos; }

	virtual void update(Hero& hero) = 0;
	virtual Position getAnotherPos() = 0;
	virtual void setAnotherPos(const Position&) = 0;
};
