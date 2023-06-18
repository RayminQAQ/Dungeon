/***********************************************************************
 * File: invalidInput.h
 * Author: Raymin, Tone-yeah
 * Create Date: - -
 * Editor: Raymin, Tone-yeah
 * Update Date: 2023/06/04
 * Description: This header is to store invalidInput class for exception
***********************************************************************/

#pragma once
#include <string>

class invalidInput {
private:
	std::string message;
public:
	invalidInput() {};
	invalidInput(std::string m) : message(m) {};
	std::string what() { return message; }
};
