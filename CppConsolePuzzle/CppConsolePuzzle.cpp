#define _WIN32_WINNT 0x0500
#include "pch.h"
#include "ConsoleGraphic.h"
#include "ConsoleUtils.h"
#include "Images.h"
#include "SelectionGame.h"
#include <algorithm>
#include <Windows.h>

SelectionGame* get_clock_puzzle() {
	std::vector<std::string> clock_times{
		"12", "3", "6"
	};
	std::string clock_times_fav_num = "3";
	clock_times.push_back("9");

	return new SelectionGame(ConsoleGraphic(images::CLOCK),
		clock_times, { 0, 0, 0, 0 },
		525, "GRACIAS", 0);
}

SelectionGame* get_humphrey_puzzle() {
	return new SelectionGame(ConsoleGraphic(images::HUMPHREY),
		{ "BACK", "MATH", "FISH", "LION" }, { 1, 0, 3, 2 },
		400, "DANKE", 0);
}

SelectionGame* get_hardware_puzzle() {
	return new SelectionGame(ConsoleGraphic(images::HARDWARE),
		{ "PSU", "HDD", "MOBO", "FAN" }, { 2, 1, 0, 3 },
		320, "ARIGATO", 0);
}

SelectionGame* get_french_puzzle() {
	std::vector<std::string> parts{ //Spells "sarcelle"
		"le", "cel", "ar", "s"
	};
	std::reverse(parts.begin(), parts.end());

	return new SelectionGame(ConsoleGraphic(images::TEAL),
		parts, { 3, 1, 0, 2 },
		600, "MERCI", -10);
}

SelectionGame* get_chinese_puzzle() {
	std::vector<std::string> aichinese{ //(人工智能)
		"+667A", "I", "+4EBA"
	};
	std::reverse(aichinese.begin(), aichinese.end());
	aichinese.push_back("+80FD");

	return new SelectionGame(ConsoleGraphic(images::AI),
		aichinese, { 0, 2, 1, 3 },
		320, "XIEXIE", -8);
}

int main()
{
	show_console_cursor(false);
	animate_window_size(65, 31);
	set_font();

	HWND console_window = GetConsoleWindow();
	SetWindowLong(console_window, GWL_STYLE, GetWindowLong(console_window, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

	system("color 0f");
	get_clock_puzzle()->play_tutorial();

	system("color 1B");
	get_humphrey_puzzle()->play_intro();

	system("color F0");
	get_hardware_puzzle()->play_intro();

	system("color 3F");
	get_french_puzzle()->play_intro();

	system("color 0F");
	get_chinese_puzzle()->play_intro();

	// Print 51x7 rectangle of whitespace
	ConsoleGraphic::whitespace(51, 7).print(100, true);

	// Obfuscated
	std::string s = ")\"Qj.\"vjg\"ogpw\"nqqmu\"fgnkekqwu\"vqfc{#\")";
	for (int i = 0; i < s.length(); i++) {
		s[i] = s[i] - 2;
	}

	ConsoleGraphic({ "Bots tell secrets to those who give complements.", s, "", "    How discordant." }).print(100, true);

	Sleep(1000);

	ConsoleGraphic::whitespace(55, 2).load_position(2, 3).print(100, true);
	ConsoleGraphic({ "[END OF THIS PROGRAM. THANK YOU FOR PARTICIPATING!]" }, 2, 3).print(50, true);

	std::cin.ignore();
	std::cin.get();

	return 0;
}