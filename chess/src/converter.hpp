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
	Converter();
	~Converter();

	static Position convert(char, char);

private:
	//static const std::map<char, int> charToIntX;

	//static const std::map<char, int> charToIntY;

	Position position;
};
