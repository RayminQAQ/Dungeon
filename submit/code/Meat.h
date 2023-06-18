/***********************************************************************
 * File: Meat.h
 * Author: Raymin, Tone-yeah
 * Create Date: - -
 * Editor: Raymin, Tone-yeah
 * Update Date: 2023/06/04
 * Description: This header is to store Meat, as derived class
***********************************************************************/


#pragma once 
#include "Item.h"

class Meat : public Item {
private:
	int heal;
public:
	// default constructor
	Meat() {
		icon = 'M';
		pos = Position(0, 0);
		heal = 10;
	}

	// setting constructor
	Meat(Position pos, char icon, int heal) : Item(pos, icon) {
		this->heal = heal;
	}

	// copy constructor
	Meat(const Meat& ref) { *this = ref; }

	// getter
	int getHealAmount() { return heal; }
	Position getAnotherPos() override { return pos; }
	void setAnotherPos(const Position& pos) override {
		this->pos = pos;
	}

	// Intent: update
	// Pre: none
	// Post: if hero is on the meat than hero gain hp
	void update(Hero& hero) override {
		if (hero.getPos().x == pos.x && hero.getPos().y == pos.y) {
			hero.gainHp(heal);
		}
	}
};
