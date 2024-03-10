#pragma once

#include "Board.hpp"
#include "Color.hpp"
#include "Converter.hpp"

using MoveData = std::pair<Position, Position>;

class Chess
{
public:
	Chess();
	~Chess();

	[[nodiscard]] std::pair<Position, Position> getMoveData() const;

	void setMoveData(MoveData);

	MoveData convertMoveData(const std::string&, const std::string&);

	bool move(const std::pair<Position, Position>&);

	bool getCheckMate();

	void changeTurn();

	friend std::ostream& operator<<(std::ostream&, const Chess&);

private:
	std::pair<Position, Position> moveData;
	Color turn{Color::white};
	Board board;
};
