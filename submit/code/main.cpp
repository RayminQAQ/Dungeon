/***********************************************************************
 * File: main.cpp
 * Author: Tone
 * Create date: 2023/05/18
 * Editor: Tone, Raymin
 * Update Date: 2023/06/04
 * Description: main program of dungeon
 * ***********************************************************************/

#include "Position.h"
#include "main.h"
#include "Game.h"
#include "InvalidInput.h"

#include <iostream>
#include <conio.h>

using namespace std;

void updateKey(bool gKeyState[]);

int main() {
	// Initialize the game
	Game game;
	//game.setUpBoard(SIZE, SIZE);
	game.initialize();
	game.getInNextLevel();
	

	// user input
	bool gKeyState[ValidInput::INVALID];
	for (int i = 0; i < ValidInput::INVALID; i++) {
		gKeyState[i] = false;
	}

	// update
	game.update(gKeyState);
	
	while (!gKeyState[ValidInput::EESC]) {
		try {
			updateKey(gKeyState);

			if (gKeyState[ValidInput::ESave]) {
				game.save();
				gKeyState[ValidInput::ESave] = false;
				game.printBoard();
				game.printGameInfo();
				continue;
			}
			else if (gKeyState[ValidInput::ELoad]) {
				game.load();
				gKeyState[ValidInput::ELoad] = false;
				game.printBoard();
				game.printGameInfo();
				continue;
			}

			game.update(gKeyState);
			if (game.gameover()) {
				system("CLS");
				cout << "you lose!" << endl;
				cout << "you go through the " << game.getLevel() << " levels." << endl;
				cout << "come to challenge next time." << endl;
				system("pause");
				break;
			}
		}
		catch (invalidLocation e) {
			cerr << e.what() << endl;
		}
		catch (invalidInput e) {
			cerr << e.what() << endl;
		};
	}
	return 0;
}

// Intent: update key state and read input
// Pre: gKeyState should contain all key can be pressed
// Post: store the pressed key in array
void updateKey(bool gKeyState[]) {
	// User Input
	cout << "INPUT KEY LET HERO TO MOVE" << endl;
	cout << "press (W, A, S, D) to move, press (1) to save, press (2) to load:" << endl;
	char key = _getch();

	// Update gKeyState[]
	for (int i = 0; i < ValidInput::EESC; i++) {
		gKeyState[i] = false;
	}
	switch (key) {
	case 'W': case 'w':
		gKeyState[ValidInput::EW] = true;
		break;
	case 'A': case 'a':
		gKeyState[ValidInput::EA] = true;
		break;
	case 'S': case 's':
		gKeyState[ValidInput::ES] = true;
		break;
	case 'D': case 'd':
		gKeyState[ValidInput::ED] = true;
		break;
	case 27: // ESC
		gKeyState[ValidInput::EESC] = true;
		break;
	case '1':
		gKeyState[ValidInput::ESave] = true;
		break;
	case '2':
		gKeyState[ValidInput::ELoad] = true;
		break;
	default:
		throw invalidInput("Invalid input");
		break; 
	}
	return;
}

bool isPositionValid(const Position& pos, const std::vector<std::vector<char>>& board, const std::vector<Position>& poss) {

	if (board[pos.y][pos.x] == '*') return false;

	for (int i = 0; i < poss.size(); i++) {
		if (pos == poss[i]) return false;
	}

	return true;
}