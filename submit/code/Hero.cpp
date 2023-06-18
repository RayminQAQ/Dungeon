/***********************************************************************
 * File: Hero.cpp
 * Author: Raymin, Tone-yeah
 * Create Date: - -
 * Editor: Raymin, Tone-yeah
 * Update Date: 2023/06/04
 * Description: This cpp is to store Hero class method
***********************************************************************/


#include "Hero.h"
#include "Game.h"

// Intent: move the position
// Pre: none
// Post: the position is changed
void Hero::move(Position next) {
	sPos = next;
}

// Intent: gain EXP
// Pre: points should be positive
// Post: the CurrentExp is changed
void Hero::gainEXP(int points){
	int number = points;
	while (number > 0) {
		if (sCurrentExp + number >= sMaxExp) {
			number -= (sMaxExp - sCurrentExp);
			sCurrentExp = 0;
			sMaxExp = (int)((float)sMaxExp * 1.2f);
			sLevel++;
			levelUp();
		}
		else {
			sCurrentExp += number;
			number = 0;
		}
	}
}

// Intent: get damaged
// Pre: points should be positive
// Post: hp decrease
void Hero::damage(int points) {
	hp = hp - points;
	if (hp < 0)
		hp = 0;
}

// Intent: gain hp
// Pre: points should be positive
// Post: hp increase
void Hero::gainHp(int points){
	hp += points;
	if (hp > 100) hp = 100;
}

void Hero::levelUp(){
	hp += 25;
	if (hp > 100) hp = 100;
	power *= 1.5;
}
