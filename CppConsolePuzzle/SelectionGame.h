#pragma once
#include "ConsoleGraphic.h"
#include <string>
#include <vector>

class SelectionGame
{
	ConsoleGraphic centre_piece_;

	int option_x_;
	int option_y_;

	int selected_item_;
	std::vector<int> current_indices_;

	int last_correct_time_;
	bool space_held_;

	// Answers are in order [0, 1, 2, 3]
	std::vector<ConsoleGraphic> word_options_;
	std::vector<ConsoleGraphic> arrows_;

	int drawing_;
	int playing_;

	int beep_hz_;

	std::string endText_;

	int check_correct();
	void correct_answer();
	void redraw();
	int respond_to_input();
	void set_selected_item(int index);
	void toggle_selected();
public:
	SelectionGame(ConsoleGraphic centre_piece,
		std::vector<std::string> word_options,
		std::vector<int> starting_indices,
		int beep_hz,
		std::string end_text,
		int arrows_offset);
	void play();
	void play_intro();
	void play_tutorial();
	void set_draw_mode(bool drawing);
};