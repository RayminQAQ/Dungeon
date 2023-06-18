#pragma once
#include "Item.h"

class Trigger : public Item {
private:
	int exp;
public:
	// default constructor
	Trigger() {
		icon = 'T';
		pos = Position(0, 0);
		exp = 10;
	}

	// setting constructor
	Trigger(Position pos, char icon, int exp) : Item(pos, icon) {
		this->exp = exp;
	}

	// copy constructor
	Trigger(const Trigger& ref) { *this = ref; }

	//getter
	int getExpAmount() const { return this->exp; }
	Position getAnotherPos() override { return pos; }
	void setAnotherPos(const Position& pos) override {
		this->pos = pos;
	}

	// Intent: update trigger function
	// Pre: none
	// Post: if hero is on the trigger than hero gain exp
	void update(Hero& hero) override {
		if (hero.getPos().x == pos.x && hero.getPos().y == pos.y) {
			hero.gainEXP(exp);
		}
	}
};
