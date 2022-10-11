#pragma once
#ifndef GAMESTORY_HPP
#define GAMESTORY_HPP
#include "GameText.hpp"
#include "GameControl.hpp"

//-----------------------------------------------------------------------------------------------

void FirstScene() {
	GameTextOutputControl(
		"Resources\\Text\\Story01.txt", 
		10, 40, { 10, 10 }, { 255, 255, 255 }, 20, 4);
}

//-----------------------------------------------------------------------------------------------

#endif
