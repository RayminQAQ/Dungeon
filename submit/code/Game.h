/***********************************************************************
 * File: Game.h
 * Author: Raymin, Tone-yeah
 * Create Date: - -
 * Editor: Raymin, Tone-yeah
 * Update Date: 2023/06/04
 * Description: This header is to store Game class
***********************************************************************/

#pragma once

#include "Hero.h"
#include "Creature.h"
#include "Bat.h"
#include "Skeleton.h"
#include "Wolf.h"
#include "Item.h"
#include "Variable.h"
#include "Trigger.h"
#include "Meat.h"
#include "Portal.h"
#include "Color.h"
#include "Hole.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <conio.h>
#include <algorithm>

class Game {
private:
	int sizeX, sizeY;
	int level;
	std::vector<std::vector<char>> board;
	Hero hero;
	std::vector<Creature*> creatures;
	std::vector<Item*> items;
	std::vector<Trigger> triggers;
	std::vector<Meat> meats;
	std::vector<Portal> portals;
	Hole hole;
	const char GWALL = '*';
	const char GNOTHING = ' ';
	const char GEND = 'O';
	
	void loadMap();
	void generateMaze();
	void divide(Position pos, int width, int height, bool horizontal);
	void chooseOrientation(const int& width, const int& height, bool& HORIZONTAL);
	void resetItems();
public:
	Game();
	void setUpBoard(const int& sizeX, const int& sizeY);
	void initialize();
	void getInNextLevel();
	
	// add
	void addBat(Position pos, char icon, int power, int hp);
	void addWolf(Position pos, char icon, int power, int hp);
	void addSkeleton(Position pos, char icon, int power, int hp);
	void addTrigger(Position, char, int);
	void addMeat(Position, char, int);
	void addPortal(Position, char, Position);
	void addHole(Position, char);
	void addBat();
	void addWolf();
	void addSkeleton();
	void addTrigger();
	void addMeat();
	void addPortal();

	void setHeroPos(Position);
	int getLevel();
	void printBoard();
	void printGameInfo();
	void update(bool gKeyState[]);
	void save();
	void load();
	void allCreatruesLevelUp();
	// void MoveHero(Position);

	bool isPositionValid(const Position& pos);
	bool gameover();

	// battle -> no use
	void battleOOP();
	void RockPaperSisisor();
};