/***********************************************************************
 * File: invalidLocation.h
 * Author: Raymin, Tone-yeah
 * Create Date: - -
 * Editor: Raymin, Tone-yeah
 * Update Date: 2023/06/04
 * Description: This header is to store invalidLocation class for exception
***********************************************************************/

#pragma once

#include <string>
#include <exception>

class invalidLocation {
private:
	std::string message;
public:
	invalidLocation() {};
	invalidLocation(std::string m)
	 : message(m) {}
	std::string what() { return message; }
};
