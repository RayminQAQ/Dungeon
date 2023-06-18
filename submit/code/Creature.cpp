/***********************************************************************
 * File: Creature.cpp
 * Author: Raymin, Tone-yeah
 * Create Date: - -
 * Editor: Raymin, Tone-yeah
 * Update Date: 2023/06/04
 * Description: This cpp is to store Creature class method
***********************************************************************/

#include "Creature.h"

// Intent: update the infomations
// Pre: none
// Post: the informations is updated
void Creature::update(Hero& hero, bool& deleteCreature) {
	Position hPos = hero.getPos();

	Position dir;
	/*
	if (canSee(this->Pos, hPos, dir)) {
		std::cout << "Creature has find the Hero in the ( " << dir.x << ", " << dir.y << " ) direction\n";
		this->sIcon = '!';
	}
	else {
		std::cout << "Creature didn't find the Hero\n";
		this->sIcon = 'C';
	}
	*/
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			Position around(pos.x + i, pos.y + j);
			if (hPos == around) battle(hero, deleteCreature);
		}
	}
}

void Creature::battle(Hero& hero, bool& deleteCreature) {
	// Game Instruction
	system("CLS");
	std::cout << RED << "Play Rock-Paper-Sisisor Game" << RESET << std::endl;
	std::cout << "Enter key to continue" << std::endl;
	system("pause");

	// gaming
	int creatureHp = this->getHp(), heroHp = hero.getHP(), heroPower = hero.getPower(), creaturePower = this->power;

	while (true) {
		system("CLS");
		std::cout << "1 for Rock, 2 for Paper, 3 for Sisisor" << std::endl;
		std::cout << "You have " << heroHp  << " HP left" << std::endl;
		std::cout << "Your power is " << heroPower << std::endl;
		std::cout << "Creature have " << creatureHp << " HP left" << std::endl;
		std::cout << "Creature's power is " << creaturePower << std::endl;

		int opponent = rand() % 3 + 1;
		std::string str;
		std::cin >> str;
		if (str.length() != 1) { continue;}
		else if ('0' > str[0] || '9' < str[0]) { continue; }
		int c = stoi(str);
		if (c == 1 || c == 2 || c == 3) {
			//
			std::cout << "Opponent Choose ";
			switch (opponent) {
			case 1:
				std::cout << "Rock " << std::endl;
				break;
			case 2:
				std::cout << "Paper" << std::endl;
				break;
			case 3:
				std::cout << "Scissors" << std::endl;
				break;
			default:
				std::cout << "BUG IN RockPaperSisisor-1" << std::endl;
				break;
			}
		}
		else {
			continue;
		}


		switch (c) {
		case 1:
			if (opponent == 1) {
				std::cout << "Draw" << std::endl;
			}
			else if (opponent == 2) {
				std::cout << "You Lost" << std::endl;
				heroHp -= this->power;
			}
			else if (opponent == 3) {
				std::cout << "You Win" << std::endl;
				creatureHp -= heroPower;
			}
			break;
		case 2:
			if (opponent == 1) {
				std::cout << "You Win" << std::endl;
				creatureHp -= heroPower;
			}
			else if (opponent == 2) {
				std::cout << "Draw" << std::endl;
			}
			else if (opponent == 3) {
				std::cout << "You Lost" << std::endl;
				heroHp -= this->power;
			}
			break;
		case 3:
			if (opponent == 1) {
				std::cout << "You Lost" << std::endl;
				heroHp -= this->power;
			}
			else if (opponent == 2) {
				std::cout << "You Win" << std::endl;
				creatureHp -= heroPower;
			}
			else if (opponent == 3) {
				std::cout << "Draw" << std::endl;
			}
			break;
			default:
				std::cout << "BUG IN RockPaperSisisor-2" << std::endl;
				break;
		}

		if (creatureHp <= 0) {
			std::cout << RED << "You overcome the creature!! Continue game" << RESET << std::endl;
			hero.setHP(heroHp);
			hero.gainEXP(5);
			deleteCreature = true;
			break;
		}
		else if (heroHp <= 0) {
			std::cout << RED << "You died from the creature!!" << RESET << std::endl;
			deleteCreature = false;
			hero.setHP(heroHp);
			break;
		}

		system("pause");
	}

	system("pause");
}
