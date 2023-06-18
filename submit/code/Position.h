/***********************************************************************
 * File: Position.h
 * Author: Raymin, Tone-yeah
 * Create Date: - -
 * Editor: Raymin, Tone-yeah
 * Update Date: 2023/06/04
 * Description: This header is to store Position class
***********************************************************************/

#pragma once
#include <iostream>
#include <vector>

class Position {
public:
	int x, y; // X, y Coordinate

	Position() : x(0), y(0) {} // default constructor
	Position(int x, int y) : x(x), y(y) {} // setting constructor
	Position(const Position& ref) { *this = ref; } // copy constructor

	// Operator overloading
	Position operator+(const Position& rhs) const {
		return Position(x + rhs.x, y + rhs.y);
	}
	Position& operator+=(const Position& rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
	Position operator-(const Position& rhs) const {
		return Position(x - rhs.x, y - rhs.y);
	}
	Position& operator-=(const Position& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}
	Position operator*(int scale) const {
		return Position(x * scale, y * scale);
	}
	bool operator==(const Position& rhs) const {
		return x == rhs.x && y == rhs.y;
	}
	bool operator!=(const Position& rhs) const {
		return !(*this == rhs);
	}
	friend std::ostream& operator <<(std::ostream& oStream, const Position& pos) {
		oStream << pos.x << " " << pos.y;
		return oStream;
	}
	friend std::istream& operator >>(std::istream& iStream, Position& pos) {
		iStream >> pos.x >> pos.y;
		return iStream;
	}
};
