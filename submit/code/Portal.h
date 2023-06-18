/***********************************************************************
 * File: Portal.h
 * Author: Raymin, Tone-yeah
 * Create Date: - -
 * Editor: Raymin, Tone-yeah
 * Update Date: 2023/06/04
 * Description: This header is to store Portal as derived class
***********************************************************************/

#pragma once
#include "Item.h"

class Portal : public Item {
private:
	Position anotherPos;
public:
	// default constructor
	Portal() {
		icon = 'P';
		pos = Position(0, 0);
		anotherPos = Position(0, 0);
	}

	// setting constructor
	Portal(Position pos, char icon, Position anotherPos) : Item(pos, icon) {
		this->anotherPos = anotherPos;
	}

	// copy constructor
	Portal(const Portal& ref) { *this = ref; }

	// getter
	Position getAnotherPos() { return anotherPos; }
	void setAnotherPos(const Position& pos) override {
		this->anotherPos = pos;
	}

	// Intent: update for portal function
	// Pre: none
	// Post: if hero is on the portal than teleport hero to another position
	void update(Hero& hero) override {
		if (hero.getPos().x == pos.x && hero.getPos().y == pos.y) {
			hero.setPos(anotherPos);
		}
		else if (hero.getPos().x == anotherPos.x && hero.getPos().y == anotherPos.y) {
			hero.setPos(pos);
		}
	}
};
