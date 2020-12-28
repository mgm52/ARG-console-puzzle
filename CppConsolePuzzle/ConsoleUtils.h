#pragma once

#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <cwchar>
#include <vector>
#include <string>

// Setup
extern int bwidth;
extern int bheight;
void set_window(int width, int height);
void set_font();

// Graphics
void animate_window_size(int width, int height);
void clear_buffer();

// Input
extern int key_buffer[2];
int get_arrow_key();
bool get_space_key();
void update_key_buffer();

// Manage cursor
void show_console_cursor(bool show_flag);
void goto_xy(int x, int y);
