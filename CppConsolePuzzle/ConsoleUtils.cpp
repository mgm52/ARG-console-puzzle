#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <cwchar>
#include <vector>
#include <string>
#include "ConsoleUtils.h"
#include <conio.h>

int bwidth;
int bheight;

int key_buffer[];

void set_window(int Width, int Height)
{
	_COORD coord = { Width, Height };

	int desktop_w = 0, desktop_h = 0;
	//GetDesktopResolution(desktop_w, desktop_h);

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = Height - 1;
	Rect.Right = Width - 1;

	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle 
	SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size 
	SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size

	bwidth = Width;
	bheight = Height;
}

void animate_window_size(int width, int height) {
	for (int i = 1; i <= 5; i++)
	{
		set_window(width / 5 * i, height / 5 * i);
		Sleep(50);
	}
}

void set_font() {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 9;                   // Width of each character in the font
	cfi.dwFontSize.Y = 18;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Courier"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	//std::cout << "Font: Times New Roman, Size: 24\n";
}

void show_console_cursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void goto_xy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clear_buffer() {
	system("CLS");
}

void update_key_buffer() {
	key_buffer[0] = -1; key_buffer[1] = -1;

	if (_kbhit()) key_buffer[0] = _getch();
	if (_kbhit()) key_buffer[1] = _getch();
}

int get_arrow_key() {
		// Arrow keys produce two chars in buffer, the first being 0 ish
		if (key_buffer[0] == 0 || key_buffer[0] == -32 || key_buffer[0] == 224) {
			switch (key_buffer[1]) {
			case 72: return 0;
			case 77: return 1;
			case 80: return 2;
			case 75: return 3;
			}
		}

	return -1;
}

bool get_space_key() {
	return (key_buffer[0] == ' ');
}