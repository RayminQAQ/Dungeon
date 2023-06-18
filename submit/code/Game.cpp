/***********************************************************************
 * File: Game.cpp
 * Author: Raymin, Tone-yeah
 * Create Date: - -
 * Editor: Raymin, Tone-yeah
 * Update Date: 2023/06/04
 * Description: This cpp is to store Game class method
***********************************************************************/

#include "Game.h"

// setting constructor
Game::Game() {
	this->creatures.clear();
}

// Intent: set up the board
// Pre: size x and y must be positive
// Post : the board was initialized
void Game::setUpBoard(const int& rowN, const int& colN){
	srand(time(NULL));
	std::vector<std::vector<bool>> validFlags(sizeY);
	for (int i = 0; i < sizeY; i++) {
		validFlags[i].resize(sizeX);
		for (int j = 0; j < sizeX; j++) {
			validFlags[i][j] = board[i][j] == GWALL ? false : true;
		}
	}
	
	auto getRandomPos = [&rowN, &colN]() {
		return Position((int)(rand() % colN), (int)(rand() % rowN));
	};

	auto getValidRandomPos = [&validFlags, &getRandomPos]() {
		while (true) {
			Position pos = getRandomPos();
			if (validFlags[pos.y][pos.x]) {
				return pos;
			}
		}
	};

	Position hPos = getValidRandomPos();
	validFlags[hPos.y][hPos.x] = false;
	hero.setPos(hPos);

	for (int i = 0; i < creatures.size(); i++) {
		Position cPos = getValidRandomPos();
		validFlags[cPos.y][cPos.x] = false;
		creatures[i]->setPos(cPos);
	}

	for (int i = 0; i < triggers.size(); i++) {
		Position tPos = getValidRandomPos();
		validFlags[tPos.y][tPos.x] = false;
		triggers[i].setPosition(tPos);
	}

	for (int i = 0; i < meats.size(); i++) {
		Position mPos = getValidRandomPos();
		validFlags[mPos.y][mPos.x] = false;
		meats[i].setPosition(mPos);
	}

	for (int i = 0; i < portals.size(); i++) {
		Position pPos = getValidRandomPos();
		validFlags[pPos.y][pPos.x] = false;
		Position anotherPos = getValidRandomPos();
		validFlags[anotherPos.y][anotherPos.x] = false;
		portals[i].setPosition(pPos);
		portals[i].setAnotherPos(anotherPos);
	}

	Position oPos = getValidRandomPos();
	validFlags[oPos.y][oPos.x] = false;
	hole.setPosition(oPos);
}

// Intent: initialize the game
// Pre: none
// Post: game is initialized
void Game::initialize(){
	this->level = 0;
	sizeX = 5;
	sizeY = 5;
	board.clear();
	creatures.clear();
	items.clear();
	triggers.clear();
	meats.clear();
	portals.clear();
}

// Intent: add a bat into the creature vector
// Pre: the informations should be given
// Post: the bat was added into the vector
void Game::addBat(Position pos, char icon, int power, int hp) 
{
	Bat* bat = new Bat(pos, icon, power, hp);
	this->creatures.push_back(bat);
}

// Intent: add a bat into the creature vector
// Pre: none
// Post: the bat was added into the vector
void Game::addBat()
{
	Bat* bat = new Bat();
	this->creatures.push_back(bat);
}

// Intent: add a wolf into the creature vector
// Pre: the information should be given
// Post: the wolf was added into the vector
void Game::addWolf(Position pos, char icon, int power, int hp) {
	Wolf* wolf = new Wolf(pos, icon, power, hp);
	this->creatures.push_back(wolf);
}

// Intent: add a wolf into the creature vector
// Pre: none
// Post: the wolf was added into the vector
void Game::addWolf() {
	Wolf* wolf = new Wolf();
	this->creatures.push_back(wolf);
}
// Intent: add a akeleton into the creature vector
// Pre: the information should be given
// Post: the skeleton was added into the vector
void Game::addSkeleton(Position pos, char icon, int power, int hp) {
	Skeleton* skeleton = new Skeleton(pos, icon, power, hp);
	this->creatures.push_back(skeleton);
}

// Intent: add a akeleton into the creature vector
// Pre: none
// Post: the skeleton was added into the vector
void Game::addSkeleton() {
	Skeleton* skeleton = new Skeleton();
	this->creatures.push_back(skeleton);
}

// Intent: print the board
// Pre: function setUpBoard should be called first
// Post: print the board on the console
void Game::printBoard() {
	std::vector<std::vector<char>> printBoard(sizeY);

	for (int i = 0; i < sizeY; i++) {
		printBoard[i].resize(sizeX);
		for (int j = 0; j < sizeX; j++) {
			printBoard[i][j] = board[i][j];
		}
	}

	for (const auto& creaturePtr : this->creatures) {
		char iconTmp = creaturePtr->getIcon();
		Position posTmp = creaturePtr->getPos();
		int powerTmp = creaturePtr->getPower();
		int hpTmp = creaturePtr->getHp();

		printBoard[posTmp.y][posTmp.x] = iconTmp;
	}

	for (int i = 0; i < items.size(); i++) {
		printBoard[items[i]->getPos().y][items[i]->getPos().x] = items[i]->getIcon();

		if (items[i]->getIcon() == 'P') {
			printBoard[items[i]->getAnotherPos().y][items[i]->getAnotherPos().x] = items[i]->getIcon();
		}
	}

	printBoard[hero.getPos().y][hero.getPos().x] = hero.getIcon();

	for (int i = 0; i < sizeY; i++) {
		for (int j = 0; j < sizeX; j++) {
			// Color selection
			if (printBoard[i][j] == this->hero.getIcon()) {
				std::cout << YELLOW << printBoard[i][j] << RESET;
			}
			else if (printBoard[i][j] == GEND) {
				std::cout << RED << printBoard[i][j] << RESET;
			}
			else if (printBoard[i][j] == 'W' || printBoard[i][j] == 'B' || printBoard[i][j] == 'S') {
				std::cout << GREEN << printBoard[i][j] << RESET;
			}
			else if (printBoard[i][j] == GWALL) {
				std::cout << WHITE_BG << printBoard[i][j] << RESET;
			}
			else if (printBoard[i][j] == GNOTHING) {
				std::cout << printBoard[i][j] << RESET;
			}
			else {
				std::cout << printBoard[i][j];
			}
		}
		std::cout << std::endl;
	}
}

bool Game::gameover() {
	if (hero.getHP() <= 0) return true;
	else return false;
}

// Intent: update the all creatures on the console
// Pre: none
// Post: new information is updated on the board
void Game::update(bool gKeyState[]){
	Position delta(0, 0);

	// input
	bool hasInput = false;
	if (gKeyState[ValidInput::EW]) {
		delta -= Position(0, 1);
		hasInput = true;
	}
	else if (gKeyState[ValidInput::ES]) {
		delta += Position(0, 1);
		hasInput = true;
	}
	else if (gKeyState[ValidInput::EA]) {
		delta -= Position(1, 0);
		hasInput = true;
	}
	else if (gKeyState[ValidInput::ED]) {
		delta += Position(1, 0);
		hasInput = true;
	}

	if (hasInput) {
		/* Move Hero */
		Position next = delta + hero.getPos();
		if (isPositionValid(next)) hero.move(next);
		else throw invalidLocation("Invalid Location.");
	}
	///
	
	bool deleteCreature = false;
	std::vector<int> indexCreature;
	for (int i = 0; i < this->creatures.size(); i++) {
		this->creatures[i]->update(hero, deleteCreature);
		this->creatures[i]->move(board, creatures, hero);
		if (deleteCreature == true) { // delete creature
			indexCreature.push_back(i);
			deleteCreature = false;
		}
	}

	std::sort(this->creatures.begin(), this->creatures.end());

	for (int i = indexCreature.size() - 1; i >= 0; i--) {
		this->creatures.erase(this->creatures.begin() + indexCreature[i]);
	}

	///
	int index = -1;
	for (int i = 0; i < items.size(); i++) {
		if (items[i]->getPos() == hero.getPos() && items[i]->getIcon() == 'O') {
			std::cout << MAGENTA << "input 1 to get into next level, input 2 to stay in the level:" << RESET << std::endl;
			char c;
			while (1) {
				std::cin >> c;
				if (c == '1') {
					getInNextLevel();
					break;
				}
				else if (c == '2') break;
				else std::cout << "invalid input!" << std::endl;
			}
			if (c == '1') break;
		}
		else if (items[i]->getPos() == hero.getPos() && (items[i]->getIcon() == 'T' || items[i]->getIcon() == 'M')) {
			index = i;
		}
		items[i]->update(hero);
	}

	// delete the acivatd items
	if (index != -1) {
		auto pos = items.begin() + index;

		auto anotherPos = triggers.end();
		for (int i = 0; i < triggers.size(); i++) {
			if (items[index]->getPos() == triggers[i].getPos()) anotherPos = triggers.begin() + i;
		}

		if (anotherPos == triggers.end()) {
			auto anotherPos = meats.end();
			for (int i = 0; i < meats.size(); i++) {
				if (items[index]->getPos() == meats[i].getPos()) anotherPos = meats.begin() + i;
			}
			items.erase(pos);
			meats.erase(anotherPos);
		}
		else {
			items.erase(pos);
			triggers.erase(anotherPos);
		}
	}
	
	system("CLS");
	printBoard();
	printGameInfo();
}

// Intent: add trigger into the board
// Pre: none
// Post: Trigger is shown on the board
void Game::addTrigger(Position pos, char icon, int exp){
	triggers.push_back(Trigger(pos, icon, exp));
	items.push_back(&triggers.back());
}

// Intent: add trigger into the board
// Pre: none
// Post: Trigger is shown on the board
void Game::addTrigger() {
	triggers.push_back(Trigger());
	items.push_back(&triggers[triggers.size() - 1]);
}

// Intent: add meat into the board
// Pre: none
// Post: Meat is shown on the board
void Game::addMeat(Position pos, char icon, int heal) {
	meats.push_back(Meat(pos, icon, heal));
	items.push_back(&meats[meats.size() - 1]);
}

// Intent: add meat into the board
// Pre: none
// Post: Meat is shown on the board
void Game::addMeat() {
	meats.push_back(Meat());
	items.push_back(&meats[meats.size() - 1]);
}

// Intent: add portal into the board
// Pre: none
// Post: Portal is shown on the board
void Game::addPortal(Position pos, char icon, Position anotherPos) {
	portals.push_back(Portal(pos, icon, anotherPos));
	items.push_back(&portals.back());
}

// Intent: add portal into the board
// Pre: none
// Post: Portal is shown on the board
void Game::addPortal() {
	portals.push_back(Portal());
	items.push_back(&portals[portals.size() - 1]);

}

// Intent: set hero position
// Pre: pos should be valid
// Post: hero is set on the board
void Game::setHeroPos(Position pos){
	hero.setPos(pos);
}

void Game::getInNextLevel(){
	level++;
	sizeX += 2;
	sizeY += 2;

	//loadMap();
	board.clear();

	board.resize(sizeY);
	for (int i = 0; i < sizeY; i++) {
		board[i].resize(sizeX);
	}

	generateMaze();
	
	addBat();
	addTrigger();
	addMeat();
	if (level % 3 == 2) {
		addWolf();
	}
	if (level % 4 == 0) {
		addSkeleton();
		addPortal();
	}
	resetItems();
	allCreatruesLevelUp();

	setUpBoard(sizeX, sizeY);
}

void Game::resetItems() {
	items.clear();
	for (int i = 0; i < triggers.size(); i++) {
		items.push_back(&triggers[i]);
	}

	for (int i = 0; i < meats.size(); i++) {
		items.push_back(&meats[i]);
	}

	for (int i = 0; i < portals.size(); i++) {
		items.push_back(&portals[i]);
	}

	items.push_back(&hole);
}

void Game::loadMap(){
	std::ifstream in;
	std::string filename = "maps\\level1";
	filename += ".txt";
	std::cout << std::endl;
	std::cout << filename << std::endl;

	in.open("maps\\level1.txt", std::ios::in); // NOTICE
	this->board.clear();

	in.open(filename, std::ios::in);
	board.clear();

	int x, y;
	in >> x >> y;
	this->sizeX = x;
	this->sizeY = y;
	in.ignore();

	for (int i = 0; i < y; i++) {
		std::string str;
		getline(in, str);

		std::vector<char> line;
		for (int i = 0; i < x; i++) {
			line.push_back(str[i]);
		}
		board.push_back(line);
	}
}

// Intent: check is position valid
// Pre: none
// Post: if position valid return true, other wise return false
bool Game::isPositionValid(const Position& pos) {
	if (board[pos.y][pos.x] != '*') {
		return true;
	}
	return false;
}

void Game::printGameInfo() {
	// Hero Info
	std::cout << "Hero level is at : " << this->hero.getLevel() << std::endl;
	std::cout << "Hero exp is at: " << this->hero.getExp() << "/" << this->hero.getMaxExp() << std::endl;
	std::cout << "Hero hp is at " << this->hero.getHP() << std::endl;
	std::cout << "Hero power is at " << this->hero.getPower() << std::endl;

	// Creature Info
	std::cout << "T means Trigger to gain exp, ";
	std::cout << "M means Meat to heal, ";
	std::cout << "P means Portal to teleport" << std::endl;
	std::cout << "B means Bat, W means Wolf, S means Skeleton" << std::endl;
	std::cout << "H means Hero" << std::endl;
	return;
}

void Game::chooseOrientation(const int& width, const int& height, bool& HORIZONTAL) {
	if (width < height) {
		HORIZONTAL = 1;
	}
	else if (height < width) {
		HORIZONTAL = 0;
	}
	else {
		HORIZONTAL = rand() % 2;
	}
}

void Game::divide(Position pos, int width, int height, bool horizontal) {
	if (width < 3 || height < 3) {
		return;
	}

	chooseOrientation(width, height, horizontal);

	const int truewidth = (width - 1) / 2;
	const int trueheight = (height - 1) / 2;

	// wall
	Position wall;
	wall.x = pos.x + (horizontal ? 0 : 2 * (rand() % truewidth) + 1);
	wall.y = pos.y + (horizontal ? 2 * (rand() % trueheight) + 1 : 0);

	// passage
	Position passage;
	passage.x = wall.x + (horizontal ? 2 * (rand() % truewidth) : 0);
	passage.y = wall.y + (horizontal ? 0 : 2 * (rand() % trueheight));

	// direction
	Position d;
	d.x = horizontal ? 1 : 0;
	d.y = horizontal ? 0 : 1;

	int length = horizontal ? width : height;

	int dir[4][2] = {
		{1,0},
		{0,-1},
		{-1,0},
		{0,1}
	};
	for (int i = 0; i < length; i++) {
		Position delta;
		delta.y = wall.y + i * d.y, delta.x = wall.x + i * d.x;
		if (delta.y == passage.y && delta.x == passage.x) continue;
		board[delta.y][delta.x] = GWALL;
	}

	// new
	Position n;
	n.x = pos.x;
	n.y = pos.y;
	int w = horizontal ? width : wall.x - pos.x;
	int h = horizontal ? wall.y - pos.y : height;
	divide(n, w, h, horizontal);

	n.x = horizontal ? pos.x : wall.x + 1;
	n.y = horizontal ? wall.y + 1 : pos.y;
	w = horizontal ? width : pos.x + width - wall.x - 1;
	h = horizontal ? pos.y + height - wall.y - 1 : height;
	divide(n, w, h, horizontal);
}

void Game::generateMaze(){
	srand(time(NULL));
	for (int i = 0; i < sizeY; i++) {
		for (int j = 0; j < sizeX; j++) {
			if (i == 0 || i == sizeY - 1 || j == 0 || j == sizeX - 1) board[i][j] = '*';
			else board[i][j] = ' ';
		}
	}

	bool HORIZONTAL = 0;
	divide(Position(1, 1), sizeX - 2, sizeY - 2, HORIZONTAL);
}

void Game::save(){
	system("CLS");
	std::cout << "Input file name for saving or Exit to leave saving." << std::endl;
	std::cout << "Input: ";
	std::string input;
	std::cin >> input;
	if (input.compare("Exit") == 0)	return;

	std::ofstream oStream(input + ".txt");
	oStream << sizeX << " " << sizeY << " " << level << std::endl;

	for (int i = 0; i < sizeY; i++) {
		for (int j = 0; j < sizeX; j++) {
			oStream << board[i][j];
		}
		oStream << std::endl;
	}
	oStream << std::endl;

	oStream << hero.getPos() << " " << hero.getHP() << " " << hero.getLevel() << " " << hero.getExp() << " " << hero.getMaxExp() << std::endl;
	
	oStream << creatures.size() << std::endl;
	for (int i = 0; i < creatures.size(); i++) {
		oStream << creatures[i]->getPos() << " " << creatures[i]->getIcon() << " " << creatures[i]->getHp() <<  " " << creatures[i]->getPower() << std::endl;
	}

	oStream << triggers.size() << std::endl;
	for (int i = 0; i < triggers.size(); i++) {
		oStream << triggers[i].getPos() << " " << triggers[i].getIcon() << " " << triggers[i].getExpAmount() << std::endl;
	}

	oStream << meats.size() << std::endl;
	for (int i = 0; i < meats.size(); i++) {
		oStream << meats[i].getPos() << " " << meats[i].getIcon() << " " << meats[i].getHealAmount() << std::endl;
	}

	oStream << portals.size() << std::endl;
	for (int i = 0; i < portals.size(); i++) {
		oStream << portals[i].getPos() << " " << portals[i].getIcon() << " " << portals[i].getAnotherPos() << std::endl;
	}

	oStream << hole.getPos() << " " << hole.getIcon() << std::endl;

	oStream.close();
	system("CLS");
}

void Game::load() {
	// Load from file and reset the dungen
	system("CLS");
	std::cout << "Input file name for loading or Exit to leave loading." << std::endl;
	std::cout << "Input: ";
	std::string input;
	std::cin >> input;
	if (input.compare("Exit") == 0)
		return;

	std::ifstream in;
	in.open(input + ".txt", std::ios::in);
	if (!in.is_open())
		return;

	// reset dungen
	board.clear();
	creatures.clear();
	items.clear();
	triggers.clear();
	meats.clear();
	portals.clear();

	in >> sizeX >> sizeY >> level;
	char _c;
	in.get(_c);

	for (int i = 0; i < sizeY; i++) {
		std::string str;
		getline(in, str);
		std::vector<char> temp;
		for (int j = 0; j < sizeX; j++) {
			temp.push_back(str[j]);
		}
		board.push_back(temp);
	}

	Position pos;
	int hp, level, exp, maxExp;
	in >> pos >> hp >> level >> exp >> maxExp;

	hero.setPos(pos);
	hero.setHP(hp);
	hero.setLevel(level);
	hero.setExp(exp);
	hero.SetMaxExp(maxExp);

	int creatureSize;
	in >> creatureSize;
	for (int i = 0; i < creatureSize; i++) {
		Position cPos;
		char icon;
		int hp, power;
		in >> cPos >> icon >> hp >> power;

		if (icon == 'B') {
			addBat(cPos, icon, hp, power);
		}
		else if (icon == 'W') {
			addWolf(cPos, icon, hp, power);
		}
		else if (icon == 'S') {
			addSkeleton(cPos, icon, hp, power);
		}
	}

	int triggerSize;
	in >> triggerSize;
	for (int i = 0; i < triggerSize; i++) {
		Position tPos;
		char icon;
		int exp;
		in >> tPos >> icon >> exp;

		addTrigger(tPos, icon, exp);
	}

	int meatSize;
	in >> meatSize;
	for (int i = 0; i < meatSize; i++) {
		Position mPos;
		char icon;
		int heal;
		in >> mPos >> icon >> heal;

		addMeat(mPos, icon, heal);
	}

	int portalSize;
	in >> portalSize;
	for (int i = 0; i < portalSize; i++) {
		Position pPos, anotherPos;
		char icon;
		in >> pPos >> icon >> anotherPos;

		addPortal(pPos, icon, anotherPos);
	}

	Position oPos;
	char oIcon;
	in >> oPos >> oIcon;
	hole.setPosition(oPos);
	hole.setIcon(oIcon);
	items.push_back(&hole);

	in.close();
	system("CLS");
}

void Game::battleOOP(){
	// Game Instruction
	std::cout << RED << "Try to survive in the OOP class" << RESET << std::endl;
	std::cout << "Entere key to continue" << std::endl;
	char c = _getch();

	// 

}

void Game::RockPaperSisisor() {
	// Game Instruction
	system("CLS");
	std::cout << RED << "Play Rock-Paper-Sisisor Game" << RESET << std::endl;
	std::cout << "Entere key to continue" << std::endl;
	char c = _getch();

	// gaming
	bool playerWin;
	std::cout << "1 for Rock, 2 for Paper, 3 for Sisisor" << std::endl;
	
	while (true) {
		int c, opponent = rand() % 3 + 1;
		std::cin >> c;
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


			switch (c) {
			case 1:
				if (opponent == 1) {
					std::cout << "Draw" << std::endl;
				}
				else if (opponent == 2) {
					std::cout << "You Lost" << std::endl;
				}
				else if (opponent == 3) {
					std::cout << "You Win" << std::endl;
				}
				break;
			case 2:
				if (opponent == 1) {
					std::cout << "You Win" << std::endl;
				}
				else if (opponent == 2) {
					std::cout << "Draw" << std::endl;
				}
				else if (opponent == 3) {
					std::cout << "You Lost" << std::endl;
				}
				break;
			case 3:
				if (opponent == 1) {
					std::cout << "You Lost" << std::endl;
				}
				else if (opponent == 2) {
					std::cout << "You Win" << std::endl;
				}
				else if (opponent == 3) {
					std::cout << "Draw" << std::endl;
				}
				break;
			default:
				std::cout << "BUG IN RockPaperSisisor-2" << std::endl;
				break;
			}
			break;
		}
	}
}

int Game::getLevel() { return level; }

void Game::allCreatruesLevelUp() {
	for (int i = 0; i < creatures.size(); i++) {
		int hp = creatures[i]->getHp(), power = creatures[i]->getPower();
		double rate = 1 + (level * 0.1);
		hp *= rate;
		power *= rate;
		creatures[i]->setHp(hp);
		creatures[i]->setPower(power);
	}

}
