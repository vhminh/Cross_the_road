#include "Function.h"
#include <Windows.h>
#include <conio.h>
#include "Constants.h"

void gotoXY(int x, int y) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(h, pos);
}

void setCursorVisible(bool state) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = state;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void fixConsoleSize() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

int random(int start, int end) {
	return rand() % (end - start) + start;
}

/*
void flushInputStart() {
	while (IGNORE_INPUT) {
		_getch();
	}
}

void flushInputEnd() {
	IGNORE_INPUT = true;
}
*/