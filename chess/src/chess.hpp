#pragma once

#include <iostream>

#include "Board.hpp"
#include "Color.hpp"
#include "Converter.hpp"

using MoveData = std::pair<Position, Position>;

class Chess
{
public:
	Chess() : board{turn}
	{
	}

	~Chess() = default;


	[[nodiscard]] std::pair<Position, Position> getMoveData() const
	{
		return moveData;
	}

	void setMoveData(MoveData data)
	{
		moveData = data;
	}

	MoveData convertMoveData(const std::string& startPosition, const std::string& endPosition)
	{
		auto pairStart{Converter::convert(startPosition[0], startPosition[1])};
		auto pairEnd{Converter::convert(endPosition[0], endPosition[1])};
		return std::make_pair(pairStart, pairEnd);
	}

	bool move(const auto& moveData)
	{
		if (!board.checkIfMoveIsPossible(moveData))
		{
			return false;
		}
		board.move(moveData);
		return true;
	}

	bool getCheckMate()
	{
		return board.getCheckMate();
	}

	void changeTurn() { turn = turn == Color::white ? Color::black : Color::white; }

	friend std::ostream& operator<<(std::ostream& out, const Chess& c)
	{
		out << c.board;
		return out;
	}

private:
	std::pair<Position, Position> moveData;
	Color turn{Color::white};
	Board board;
};
