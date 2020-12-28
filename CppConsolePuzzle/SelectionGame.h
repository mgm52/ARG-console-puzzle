#pragma once
#include <vector>
#include <string>
#include "ConsoleGraphic.h"

class SelectionGame
{
	ConsoleGraphic centrePiece_;

	int arrow_x_;
	int arrow_y_;
	int option_x_;
	int option_y_;

	int selectedItem_;

	int drawing_;
	int playing_;

	int beepHz_;

	// Answers are in order REDACTED
	std::vector<ConsoleGraphic> wordOptions_;

	std::vector<int> currentIndices_;

	std::string endText_;

	std::vector<ConsoleGraphic> arrows_;

	int lastCorrectTime_;

	bool spaceHeld_;
public:
	SelectionGame(ConsoleGraphic centrePiece,
		std::vector<std::string> wordOptions,
		std::vector<int> startingIndices,
		int beepHz,
		std::string endText,
		int arrows_offset);
	void play();
	void Redraw();
	void SetDrawMode(bool drawing);
	void play_intro();
	int RespondToInput();
	void ToggleSelected();
	void SetSelectedItem(int index);
	void CorrectAnswer();
	void play_tutorial();
	int CheckCorrect();
};

