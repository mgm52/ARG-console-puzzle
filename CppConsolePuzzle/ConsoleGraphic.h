#pragma once
#include <string>
#include <vector>

class ConsoleGraphic
{
private:
	int gwidth_;
	int gheight_;

	int xstart_;
	int ystart_;

	std::vector<std::string> img_;
public:
	void print(int animate_delay = 0, bool animate_horizontal = false);
	ConsoleGraphic load_position(int direc, int dist);

	int get_width();
	int get_height();

	static ConsoleGraphic whitespace(int width, int height);

	ConsoleGraphic(std::vector<std::string> str, int direc = 0, int dist = 0);

	ConsoleGraphic();
	~ConsoleGraphic();
};

