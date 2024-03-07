#pragma once

#include <map>

struct Position
{
	int x{};
	int y{};

	bool operator<(const Position& position) const
	{
		return x < position.x and y < position.y;
	}

	bool operator==(const Position& position) const
	{
		return x == position.x and y == position.y;
	}
};

class Converter
{
public:
	static Position convert(char posX, char posY)
	{
		return Position{char_to_int_y.at(posY), char_to_int_x.at(posX)};
	}

private:
	inline static const std::map<char, int> char_to_int_x =
	{
		{'a', 0},
		{'b', 1},
		{'c', 2},
		{'d', 3},
		{'e', 4},
		{'f', 5},
		{'g', 6},
		{'h', 7},
	};

	inline static const std::map<char, int> char_to_int_y =
	{
		{'1', 0},
		{'2', 1},
		{'3', 2},
		{'4', 3},
		{'5', 4},
		{'6', 5},
		{'7', 6},
		{'8', 7},
	};

	Position position;
};
