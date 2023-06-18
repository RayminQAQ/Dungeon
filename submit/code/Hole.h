#pragma once
#include "Item.h"

class Hole : public Item{
public:
	Hole() {
		icon = 'O';
		pos = Position(0, 0);
	}

	Hole(Position pos, char icon) {
		this->icon = icon;
		this->pos = pos;
	}

	Hole(Hole& ref) {
		this->icon = ref.icon;
		this->pos = ref.pos;
	}

	void update(Hero& hero) override {}

	Position getAnotherPos() override { return pos; }
	void setAnotherPos(const Position& pos) override {
		this->pos = pos;
	}
};
