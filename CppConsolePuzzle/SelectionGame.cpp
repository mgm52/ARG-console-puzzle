#include "pch.h"
#include "SelectionGame.h"
#include <vector>
#include <string>
#include <stdlib.h>
#include "ConsoleUtils.h"
#include "ConsoleGraphic.h"
#include <time.h>
#include "Images.h"

SelectionGame::SelectionGame(ConsoleGraphic centrePiece,
	std::vector<std::string> wordOptions,
	std::vector<int> startingIndices,
	int beepHz,
	std::string endText,
	int arrows_offset)
{
	endText_ = endText;

	centrePiece_ = centrePiece;

	arrow_x_ = centrePiece.getWidth() / 2 + 4 + arrows_offset;
	arrow_y_ = centrePiece.getHeight() / 2 + 2 + arrows_offset / 2;

	option_x_ = arrow_x_ + 6;
	option_y_ = arrow_y_ + 3;

	for (int i = 0; i < wordOptions.size(); i++) {
		wordOptions_.push_back(ConsoleGraphic({ wordOptions[i] }));
	}

	currentIndices_ = startingIndices;

	beepHz_ = beepHz;

	spaceHeld_ = false;

	lastCorrectTime_ = -1;

	drawing_ = true;
	playing_ = false;

	arrows_ = { ConsoleGraphic({ "^","|" }, 0, arrow_y_),
									   ConsoleGraphic({ "-->" }, 1, arrow_x_),
									   ConsoleGraphic({ "|","v" }, 2, arrow_y_),
									   ConsoleGraphic({ "<--" }, 3, arrow_x_) };
}

void SelectionGame::Redraw() {
	if (drawing_) {
		clear_buffer();
		centrePiece_.print(0, 0);

		arrows_[selectedItem_].print();

		for (int i = 0; i < 4; i++) {
			wordOptions_[currentIndices_[i]].load_position(i, (i % 2) ? option_x_ : option_y_).print();
		}
	}
}

void SelectionGame::SetDrawMode(bool drawing) {
	drawing_ = drawing;
	if (drawing) Redraw();
}

void SelectionGame::play_tutorial() {
	SetDrawMode(false);

	clear_buffer();
	ConsoleGraphic({ "ARROW KEY" }).print(0, 0);

	int a = -1;
	while ((a = get_arrow_key()) < 0) {
		Sleep(50);
		update_key_buffer();
	};
	SetSelectedItem(a);

	clear_buffer();
	ConsoleGraphic({ "SPACE" }).print(0, 0);

	while (!get_space_key()) {
		Sleep(50);
		update_key_buffer();
	}
	ToggleSelected();

	system("color 8f");
	SetDrawMode(true);
	play();
}

void SelectionGame::play_intro() {
	clear_buffer();
	centrePiece_.load_position(0, 0).print(50, true);

	Sleep(500);

	play();
}

void SelectionGame::play() {
	playing_ = true;

	Redraw();

	while (playing_) {
		Sleep(50);
		RespondToInput();
	}
}

void SelectionGame::SetSelectedItem(int index) {
	selectedItem_ = index;
	Redraw();
}

void SelectionGame::ToggleSelected() {
	currentIndices_[selectedItem_] += 1;
	if (currentIndices_[selectedItem_] >= wordOptions_.size()) currentIndices_[selectedItem_] = 0;
	Redraw();
	Beep(beepHz_, 50);
}

int SelectionGame::CheckCorrect() {
	// Check if we have a winning combination (0, 1, 2, 3). If check fails at any point, return 0.
	for (int i = 0; i < currentIndices_.size(); i++) {
		if (currentIndices_[i] != i) {
			lastCorrectTime_ = -1;
			return 0;
		}
	}

	// First landed correct answer, wait until user's lingered on it
	if (lastCorrectTime_ < 0) {
		lastCorrectTime_ = time(NULL);
		return 0;
	}

	// If we've had the correct answer selected for 1s, return 1
	if (lastCorrectTime_ > 0 && time(NULL) - lastCorrectTime_  >= 3) {
		return 1;
	}

	return 0;
}

void SelectionGame::CorrectAnswer() {
	playing_ = false;

	Sleep(1000);
	clear_buffer();

	ConsoleGraphic({images::TICK}).print(50);

	ConsoleGraphic({ endText_ }, 2, 12).print(1000);

	Sleep(2000);
}



int SelectionGame::RespondToInput() {
	std::cin.clear();

	update_key_buffer();

	int arrowDir = get_arrow_key();
	if (arrowDir > -1) SetSelectedItem(arrowDir);

	int won = 0;
	if (get_space_key())
	{
		if (!spaceHeld_) {
			spaceHeld_ = true;
			ToggleSelected();
		}
	}
	else {
		spaceHeld_ = false;
	}

	if (CheckCorrect()) CorrectAnswer();

	return 0;
}