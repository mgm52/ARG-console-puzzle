#include "pch.h"
#include "ConsoleGraphic.h"
#include "ConsoleUtils.h"
#include "Images.h"
#include "SelectionGame.h"
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>

SelectionGame::SelectionGame(ConsoleGraphic centre_piece,
	std::vector<std::string> word_options,
	std::vector<int> starting_indices,
	int beep_hz,
	std::string end_text,
	int arrows_offset)
{
	centre_piece_ = centre_piece;

	int arrow_x = centre_piece.get_width() / 2 + 4 + arrows_offset;
	int arrow_y = centre_piece.get_height() / 2 + 2 + arrows_offset / 2;

	option_x_ = arrow_x + 6;
	option_y_ = arrow_y + 3;

	selected_item_ = 0;
	current_indices_ = starting_indices;

	last_correct_time_ = -1;
	space_held_ = false;

	for (int i = 0; i < word_options.size(); i++) {
		word_options_.push_back(ConsoleGraphic({ word_options[i] }));
	}
	arrows_ = { ConsoleGraphic({ "^","|" }, 0, arrow_y),
									   ConsoleGraphic({ "-->" }, 1, arrow_x),
									   ConsoleGraphic({ "|","v" }, 2, arrow_y),
									   ConsoleGraphic({ "<--" }, 3, arrow_x) };

	drawing_ = true;
	playing_ = false;

	beep_hz_ = beep_hz;

	endText_ = end_text;
}

void SelectionGame::play() {
	playing_ = true;

	redraw();

	while (playing_) {
		Sleep(50);
		respond_to_input();
	}
}

void SelectionGame::play_intro() {
	clear_buffer();
	centre_piece_.load_position(0, 0).print(50, true);

	Sleep(500);

	play();
}

void SelectionGame::play_tutorial() {
	set_draw_mode(false);

	// Wait for user to press arrow key
	clear_buffer();
	ConsoleGraphic({ "ARROW KEY" }).print(0, 0);

	int a = -1;
	while ((a = get_arrow_key()) < 0) {
		Sleep(50);
		update_key_buffer();
	};
	set_selected_item(a);

	// Wait for user to press space
	clear_buffer();
	ConsoleGraphic({ "SPACE" }).print(0, 0);

	while (!get_space_key()) {
		Sleep(50);
		update_key_buffer();
	}
	toggle_selected();

	// Show UI
	system("color 8f");
	set_draw_mode(true);
	play();
}

void SelectionGame::set_selected_item(int index) {
	selected_item_ = index;
	redraw();
}

int SelectionGame::check_correct() {
	// Check if we have a winning combination (0, 1, 2, 3). If check fails at any point, return 0.
	for (int i = 0; i < current_indices_.size(); i++) {
		if (current_indices_[i] != i) {
			last_correct_time_ = -1;
			return 0;
		}
	}

	// First landed correct answer, wait until user's lingered on it
	if (last_correct_time_ < 0) {
		last_correct_time_ = time(NULL);
		return 0;
	}

	// If we've had the correct answer selected for 1s, return 1
	if (last_correct_time_ > 0 && time(NULL) - last_correct_time_ >= 3) {
		return 1;
	}

	return 0;
}

void SelectionGame::correct_answer() {
	playing_ = false;

	Sleep(1000);
	clear_buffer();

	ConsoleGraphic({ images::TICK }).print(50);

	ConsoleGraphic({ endText_ }, 2, 12).print(1000);

	Sleep(2000);
}

void SelectionGame::redraw() {
	if (drawing_) {
		clear_buffer();
		centre_piece_.print(0, 0);

		arrows_[selected_item_].print();

		for (int i = 0; i < 4; i++) {
			word_options_[current_indices_[i]].load_position(i, (i % 2) ? option_x_ : option_y_).print();
		}
	}
}

int SelectionGame::respond_to_input() {
	std::cin.clear();

	update_key_buffer();

	int arrowDir = get_arrow_key();
	if (arrowDir > -1) set_selected_item(arrowDir);

	int won = 0;
	if (get_space_key())
	{
		if (!space_held_) {
			space_held_ = true;
			toggle_selected();
		}
	}
	else {
		space_held_ = false;
	}

	if (check_correct()) correct_answer();

	return 0;
}

void SelectionGame::set_draw_mode(bool drawing) {
	drawing_ = drawing;
	if (drawing) redraw();
}

void SelectionGame::toggle_selected() {
	current_indices_[selected_item_] += 1;
	if (current_indices_[selected_item_] >= word_options_.size()) current_indices_[selected_item_] = 0;
	redraw();
	Beep(beep_hz_, 50);
}









