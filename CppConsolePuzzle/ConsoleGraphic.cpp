#include "pch.h"
#include "ConsoleGraphic.h"
#include "ConsoleUtils.h"
#include <string>
#include <vector>


ConsoleGraphic::ConsoleGraphic() : ConsoleGraphic({ "" }) {}

ConsoleGraphic::~ConsoleGraphic() {}

ConsoleGraphic::ConsoleGraphic(std::vector<std::string> str, int direc, int dist)
{
	// Width = longest line in str vector
	gwidth_ = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i].length() > gwidth_) gwidth_ = str[i].length();
	}
	gheight_ = str.size();
	img_ = str;
	load_position(direc, dist);
}

int ConsoleGraphic::get_width() {
	return gwidth_;
}

int ConsoleGraphic::get_height() {
	return gheight_;
}

ConsoleGraphic ConsoleGraphic::whitespace(int width, int height) {
	std::string row = std::string(width, ' ');
	std::vector<std::string> str;
	str.assign(height, row);
	return ConsoleGraphic(str);
}

ConsoleGraphic ConsoleGraphic::load_position(int direc, int dist) {
	// Offset the image based on the desired direction (counterclockwise: 0=north, 1=east, etc.) and distance
	int xoffset = (direc == 1) ? dist : (direc == 3) ? -dist : 0;
	int yoffset = (direc == 0) ? -dist : (direc == 2) ? dist : 0;

	// Off-by-one adjustment
	if (yoffset <= 0 && gheight_ % 2 == 0) yoffset--;
	if (xoffset <= 0 && gwidth_ % 2 == 0) xoffset--;

	// Pos = centre + offset
	xstart_ = (bwidth - 1) / 2 - (gwidth_ - 1) / 2 + xoffset;
	ystart_ = (bheight - 1) / 2 - (gheight_ - 1) / 2 + yoffset;

	return *this;
}

void ConsoleGraphic::print(int animate_delay, bool animate_horizontal)
{
	if (!animate_horizontal) {
		// "Garage door" animation drawing from top to bottom
		for (int y = 0; y < gheight_; y++) {
			if (animate_delay) Sleep(animate_delay);
			goto_xy(xstart_, ystart_ + y);
			std::cout << img_[y];
		}
	}
	else {
		// "Sliding curtains" animation drawing horizontally left and right from centre
		int x1 = gwidth_ / 2;
		int x2 = x1 + 1;
		while (x1 >= 0 || x2 < gwidth_) {
			if (animate_delay) Sleep(animate_delay);

			for (int y = 0; y < gheight_; y++) {
				// Continually check whether x is within bounds in case image is non-rectangular
				if (x1 >= 0 && x1 < img_[y].length()) {
					goto_xy(xstart_ + x1, ystart_ + y);
					std::cout << img_[y][x1];
				}
				if (x2 < gwidth_ && x2 < img_[y].length()) {
					goto_xy(xstart_ + x2, ystart_ + y);
					std::cout << img_[y][x2];
				}
			}

			x1--;
			x2++;
		}
	}
}
