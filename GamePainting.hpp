#ifndef GAMEPANITING_HPP
#define GAMEPANITING_HPP
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
using namespace std;

//-----------------------------------------------------------------------------------------------

void drawGraphByTrace(string traceFile, short beg_x = 0, short beg_y = 0) {
	ifstream ifs;
	ifs.open(traceFile, ios::in);
	//判断文件是否打开成功
	if (!ifs.is_open()) {
		cerr << traceFile << "轨迹txt文件打开失败！" << endl;
		exit(1);
	}
	//正式输出
	short fileSize, temp_x = 0, temp_y = 0, temp_t = 0;
	ifs >> fileSize;
	ios::sync_with_stdio(false);
	cout.tie(0);
	for (int j = 0; j < fileSize / 3; j++) {
		ifs >> temp_x >> temp_y >> temp_t;
		//cout << "\x1b[" << beg_y + temp_y << ";" << beg_x + temp_x << "H\x1b[48;2;255;255;255m    \x1b[4D\x1b[1E\x1b[48;2;255;255;255m    ";
		cout << "\x1b[" << beg_y + temp_y << ";" << beg_x + temp_x << "H\x1b[48;2;255;255;255m  ";
		//Sleep((temp_t > 20)? (temp_t - 20) : 0);
		//Sleep(1);
		for (int i = 0; i < 1e7; i++);
	}
	ifs.close();
	cout << "\x1b[0m";
}

//-----------------------------------------------------------------------------------------------

#endif