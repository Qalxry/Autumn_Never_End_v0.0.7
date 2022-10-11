#pragma once
#ifndef GAMECONTROL_HPP
#define GAMECONTROL_HPP
#include <iostream>

//-----------------------------------------------------------------------------------------------

void WaitForInput(const char& input_char) {
	char temp = getchar();
	while(temp != input_char)
		temp = getchar();
}

//-----------------------------------------------------------------------------------------------

#endif
