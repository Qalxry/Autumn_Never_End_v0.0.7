#pragma once
#ifndef GAMESTART_HPP
#define GAMESTART_HPP
#include "GameInit.hpp"
#include "GamePicture.hpp"
#include "GameFileMapping.hpp"
#include "GamePainting.hpp"
#include "GameScreenBuffer.hpp"
#include "GameStory.hpp"

//-----------------------------------------------------------------------------------------------

//”Œœ∑∆Ù∂Ø
void gameStart(){
	gameInit_default();
	system("color d0"); 
	for(int i = -21; i < 22; i++)
		txtPicOutput("Resource\\pic_Plane.txt", 0, 97 + i, 37, 'b');
	for(int i = -20; i < 20; i++)
		txtPicOutput("Resource\\pic_Plane.txt", 0, 97, 37 + i, 'b');
	txtPicOutput("Resource\\pic_WenHao_b.txt", 0, 78, 37, 'w');
	Sleep(500);
	txtPicOutput("Resource\\pic_Start.txt", 0, 62, 86, 'b');
	COORD coord = { 180, 130 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	system("pause");
} 

void gameStart_FileMapping() {
	gameInit_default();
	GameFileMap* pic1 = new GameFileMap(L"background.txt");
	pic1->FileMappingOutput();
	GameFileMap* pic2 = new GameFileMap(L"background.txt");
	drawGraphByTrace("trace_change.txt", 63, 50);
	system("pause");
}

void gameStart_FileMapping_MultipleBuffer() {
	gameInit_default();
	GameFileMap* pic1 = new GameFileMap(L"Resources\\Images\\bg02_start.txt");
	GameFileMap* pic2 = new GameFileMap(L"Resources\\Images\\scene02_classroom.txt");

	ScreenBuffer* sb2 = new ScreenBuffer(pic2);

	pic1->FileMappingOutput();
	drawGraphByTrace("Resources\\Traces\\trace01_xrbj.txt", 63, 50);
	sb2->SetActiveScreenBuffer();
	FirstScene();
	delete pic1;
	delete pic2;
	system("pause");
}

void gameStart_Debugger() {
	//gameInit_debugger();
	gameInit_default();
	FirstScene();
	system("pause");
}

//-----------------------------------------------------------------------------------------------

#endif
