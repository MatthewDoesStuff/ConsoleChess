#pragma once

#include <cmath>
#include <iostream>

#include "converter.hpp"

class Chess {
public:

	static std::pair<Position, Position> getMoveData()
	{
		std::string startPos, movePos;
		
		std::cout << "pick a figure you want to move: " << std::endl;
		std::cin >> startPos;
		auto pairPick = Converter::convert(startPos[0], startPos[1]);

		std::cout << "choose where do you want to move: " << std::endl;
		std::cin >> movePos;
		auto pairMove = Converter::convert(movePos[0], movePos[1]);

		return std::make_pair(pairPick, pairMove);
	}
	std::pair<Position, Position> moveData;
	Chess() = default;

	static bool getTurn()
	{
		return turn;
	}

	static void changeTurn() { turn = not turn; }

private:

	inline static bool turn{true}; 
};
