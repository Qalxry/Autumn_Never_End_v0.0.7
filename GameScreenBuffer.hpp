#ifndef GAMESCREENBUFFER_HPP
#define GAMESCREENBUFFER_HPP
#include <iostream>
#include <windows.h>
#include "GameFileMapping.hpp"
using namespace std;

//-----------------------------------------------------------------------------------------------

HANDLE hOriginalIn = GetStdHandle(STD_INPUT_HANDLE);			//输入句柄
HANDLE hOriginalOut = GetStdHandle(STD_OUTPUT_HANDLE);			//输出句柄

//-----------------------------------------------------------------------------------------------

class ScreenBuffer {
public:
	ScreenBuffer() {
		hGameScreenBuffer = CreateConsoleScreenBuffer(
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	}
	ScreenBuffer(GameFileMap* gameFileMap) {
		//创建新屏幕缓冲区
		hGameScreenBuffer = CreateConsoleScreenBuffer(
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		if (hGameScreenBuffer == INVALID_HANDLE_VALUE) {
			cerr << "[B001][ERROR][ScreenBuffer::CreateConsoleScreenBuffer]\nFail to create new Screen Buffer.\n";
			Sleep(3000);
			exit(1);
		}
		//拷贝原屏幕缓冲区属性至新屏幕缓冲区
		/*CONSOLE_SCREEN_BUFFER_INFOEX OriginalInfo;
		GetConsoleScreenBufferInfoEx(hOriginalOut, &OriginalInfo);
		SetConsoleScreenBufferInfoEx(hGameScreenBuffer, &OriginalInfo);*/
		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof cfi;
		cfi.nFont = 0;
		cfi.dwFontSize.X = 3;
		cfi.dwFontSize.Y = 7;//设置字体大小
		cfi.FontFamily = FF_DONTCARE;
		SetCurrentConsoleFontEx(hGameScreenBuffer, FALSE, &cfi);
		CONSOLE_CURSOR_INFO CursorInfo;
		GetConsoleCursorInfo(hOut, &CursorInfo);			//获取控制台光标信息
		CursorInfo.bVisible = false;					//隐藏控制台光标
		SetConsoleCursorInfo(hOut, &CursorInfo);			//设置控制台光标状态
		//向新屏幕缓冲区填入初始数据
		resultOfWrite = WriteFile(
			hGameScreenBuffer,
			gameFileMap->pMapViewOfFile,
			gameFileMap->fileSize.LowPart,
			&writeCharNumber, NULL);
		if (!resultOfWrite) {
			cerr << "[B002][ERROR][ScreenBuffer::WriteFile]\nFail to write file data to new Screen Buffer.\n";
			Sleep(3000);
			exit(1);
		}
	}

	//覆盖缓冲区的内容
	void OutputToScreenBuffer(GameFileMap* gameFileMap) {
		resultOfWrite = WriteFile(
			hGameScreenBuffer,
			gameFileMap->pMapViewOfFile,
			gameFileMap->fileSize.LowPart,
			&writeCharNumber, NULL);
		if (!resultOfWrite) {
			cerr << "[B002][ERROR][ScreenBuffer::WriteFile]\nFail to write file data to new Screen Buffer.\n";
			Sleep(3000);
			exit(1);
		}
	}

	//设置该缓冲区为活动缓冲区
	void SetActiveScreenBuffer() {
		resultOfSetActive = SetConsoleActiveScreenBuffer(hGameScreenBuffer);
		if (!resultOfSetActive) {
			cerr << "[B004][ERROR][ScreenBuffer::SetActiveScreenBuffer]\nFail to set this Screen Buffer as Active Screen Buffer.\n";
			Sleep(3000);
			exit(1);
		}
	}
	~ScreenBuffer() {
		CloseHandle(hGameScreenBuffer);
	}
	HANDLE hGameScreenBuffer = nullptr;
	DWORD writeCharNumber = 0;
	BOOL resultOfWrite = 0;
	BOOL resultOfSetActive = 0;
};

//-----------------------------------------------------------------------------------------------

#endif
