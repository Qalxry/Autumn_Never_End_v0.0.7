#ifndef GAMESCREENBUFFER_HPP
#define GAMESCREENBUFFER_HPP
#include <iostream>
#include <windows.h>
#include "GameFileMapping.hpp"
using namespace std;

//-----------------------------------------------------------------------------------------------

HANDLE hOriginalIn = GetStdHandle(STD_INPUT_HANDLE);			//������
HANDLE hOriginalOut = GetStdHandle(STD_OUTPUT_HANDLE);			//������

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
		//��������Ļ������
		hGameScreenBuffer = CreateConsoleScreenBuffer(
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		if (hGameScreenBuffer == INVALID_HANDLE_VALUE) {
			cerr << "[B001][ERROR][ScreenBuffer::CreateConsoleScreenBuffer]\nFail to create new Screen Buffer.\n";
			Sleep(3000);
			exit(1);
		}
		//����ԭ��Ļ����������������Ļ������
		/*CONSOLE_SCREEN_BUFFER_INFOEX OriginalInfo;
		GetConsoleScreenBufferInfoEx(hOriginalOut, &OriginalInfo);
		SetConsoleScreenBufferInfoEx(hGameScreenBuffer, &OriginalInfo);*/
		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof cfi;
		cfi.nFont = 0;
		cfi.dwFontSize.X = 3;
		cfi.dwFontSize.Y = 7;//���������С
		cfi.FontFamily = FF_DONTCARE;
		SetCurrentConsoleFontEx(hGameScreenBuffer, FALSE, &cfi);
		CONSOLE_CURSOR_INFO CursorInfo;
		GetConsoleCursorInfo(hOut, &CursorInfo);			//��ȡ����̨�����Ϣ
		CursorInfo.bVisible = false;					//���ؿ���̨���
		SetConsoleCursorInfo(hOut, &CursorInfo);			//���ÿ���̨���״̬
		//������Ļ�����������ʼ����
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

	//���ǻ�����������
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

	//���øû�����Ϊ�������
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
