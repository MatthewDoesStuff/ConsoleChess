#include "Chess.hpp"

Chess::Chess() : board{turn}
{
}

Chess::~Chess() = default;

[[nodiscard]] std::pair<Position, Position> Chess::getMoveData() const
{
	return moveData;
}

void Chess::setMoveData(MoveData data)
{
	moveData = data;
}

MoveData Chess::convertMoveData(const std::string& startPosition, const std::string& endPosition)
{
	auto pairStart{Converter::convert(startPosition[0], startPosition[1])};
	auto pairEnd{Converter::convert(endPosition[0], endPosition[1])};
	return std::make_pair(pairStart, pairEnd);
}

bool Chess::move(const std::pair<Position, Position>& md)
{
	if (!board.checkIfMoveIsPossible(md))
	{
		return false;
	}
	board.move(md);
	return true;
}

bool Chess::getCheckMate()
{
	return board.getCheckMate();
}

void Chess::changeTurn() { turn = turn == Color::white ? Color::black : Color::white; }

std::ostream& operator<<(std::ostream& out, const Chess& c)
{
	out << c.board;
	return out;
}
