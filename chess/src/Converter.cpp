#include "Converter.hpp"

Converter::Converter() = default;
Converter::~Converter() = default;

Position Converter::convert(char posX, char posY)
{
	static const std::map<char, int> charToIntX =
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

	static const std::map<char, int> charToIntY =
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

	return Position{charToIntY.at(posY), charToIntX.at(posX)};
}
