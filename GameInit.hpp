#pragma once
#ifndef GAMEINIT_HPP
#define GAMEINIT_HPP
#include <iostream>
#include <windows.h>
#include "GameText.hpp"
using namespace std;

//-----------------------------------------------------------------------------------------------

HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);			//������
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);			//������

//-----------------------------------------------------------------------------------------------

//����̨��������
void setTitle() {
	SetConsoleTitle(L"Autumn Never End");
}

//����̨�������Կ��ַ��������
void setWcoutLocate() {
	wcout.imbue(locale("chs"));
}

//����̨�������
void setCursor(bool showCursor) {
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(hOut, &CursorInfo);			//��ȡ����̨�����Ϣ
	CursorInfo.bVisible = showCursor;					//���ؿ���̨���
	SetConsoleCursorInfo(hOut, &CursorInfo);			//���ÿ���̨���״̬
}

//����̨�����ն�����
void setRGB() {
	DWORD dwInMode, dwOutMode;
	GetConsoleMode(hIn, &dwInMode);						//��ȡ����̨����ģʽ
	GetConsoleMode(hOut, &dwOutMode);					//��ȡ����̨���ģʽ
	dwInMode |= 0x0200;									//���Ŀ���̨����ģʽ
	dwOutMode |= 0x0004;								//���Ŀ���̨���ģʽ
	SetConsoleMode(hIn, dwInMode);						//���ÿ���̨����ģʽ
	SetConsoleMode(hOut, dwOutMode);					//���ÿ���̨���ģʽ
}

//����̨��������
void setScreen(short screen_X = 213, short screen_Y = 133) {
	COORD coord = { screen_X + 1, screen_Y + 1 };		//�����Ļ��С����213����133 
	SetConsoleScreenBufferSize(hOut, coord); 			//���û���ߴ�
	SMALL_RECT wrt = { 0, 0, screen_X, screen_Y };
	SetConsoleWindowInfo(hOut, TRUE, &wrt); 			//���ô���ߴ�
}

//����̨��������
void setFont(short font_X = 3, short font_Y = 3) {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof cfi;
	cfi.nFont = 0;
	cfi.dwFontSize.X = font_X;
	cfi.dwFontSize.Y = font_Y;  						//���������С
	cfi.FontFamily = FF_DONTCARE;
	SetCurrentConsoleFontEx(hOut, FALSE, &cfi);
}

//����̨ȫ��ģʽ
void fullScreen() {
	HWND hwnd = GetForegroundWindow();
	int cx = GetSystemMetrics(SM_CXSCREEN);				//��Ļ��� ����
	int cy = GetSystemMetrics(SM_CYSCREEN);				//��Ļ�߶� ����
	LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);	//��ȡ������Ϣ
	//���ô�����Ϣ ��� ȡ�����������߿�
	SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);
	SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);
}

//����̨���ģʽ
void maxScreen() {
	COORD NewSize = GetLargestConsoleWindowSize(hOut);	//��ÿ���̨������꣬�������ַ���Ϊ��λ
	NewSize.X -= 1;
	NewSize.Y -= 1;    //���Բ��ӣ�����ʱ��ʾ������
	SetConsoleScreenBufferSize(hOut, NewSize);			//���ÿ���̨��������С

	SMALL_RECT DisplayArea = { 0,0,0,0 };
	DisplayArea.Right = NewSize.X;
	DisplayArea.Bottom = NewSize.Y;
	SetConsoleWindowInfo(hOut, TRUE, &DisplayArea);		//���ÿ���̨��С

	//����̨�Ѿ���󻯣����ǳ�ʼλ�ò�����Ļ���Ͻǣ�������´���
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_MAXIMIZE);
}

//����̨���ģʽ
void maxScreen_debugger() {
	COORD NewSize = GetLargestConsoleWindowSize(hOut);	//��ÿ���̨������꣬�������ַ���Ϊ��λ
	NewSize.X -= 1;
	NewSize.Y -= 1;    //���Բ��ӣ�����ʱ��ʾ������
	SetConsoleScreenBufferSize(hOut, NewSize);			//���ÿ���̨��������С
	cout << "��������ȣ�" << NewSize.X << "\n�������߶ȣ�" << NewSize.Y << "\n";

	SMALL_RECT DisplayArea = { 0,0,0,0 };
	DisplayArea.Right = NewSize.X;
	DisplayArea.Bottom = NewSize.Y;
	SetConsoleWindowInfo(hOut, TRUE, &DisplayArea);		//���ÿ���̨��С

	//����̨�Ѿ���󻯣����ǳ�ʼλ�ò�����Ļ���Ͻǣ�������´���
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_MAXIMIZE);
}

//-----------------------------------------------------------------------------------------------

//��Ϸ����Ĭ��ģʽ
void gameInit_default() {
	setTitle();
	setWcoutLocate();
	setCursor(false);
	setRGB();
	setFont();
	maxScreen();
	ios::sync_with_stdio(false);
	GameTextInit();
}

//��Ϸ����ģʽ
void gameInit_debugger() {
	setTitle();
	setWcoutLocate();
	setCursor(false);
	setRGB();
	while (1) {
		short font_X, font_Y;
		cout << "�������� X ֵ = ";
		cin >> font_X;
		cout << "�������� Y ֵ = ";
		cin >> font_Y;
		setFont(font_X, font_Y);
		maxScreen_debugger();
	}
}

//-----------------------------------------------------------------------------------------------

#endif