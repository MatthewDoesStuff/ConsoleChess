#pragma once

#include <algorithm>
#include <array>
#include <iostream>
#include <ranges>
#include <unordered_map>

#include "Bishop.hpp"
#include "Color.hpp"
#include "Converter.hpp"
#include "Field.hpp"
#include "Figure.hpp"
#include "King.hpp"
#include "Knight.hpp"
#include "Pawn.hpp"
#include "Queen.hpp"
#include "Rook.hpp"

using MoveData = std::pair<Position, Position>;

class Board
{
public:
	Board(const Color& turn);

	bool getCheckMate() const;

	bool canPawnAttack(const auto&, const std::array<std::array<Field, 8>, 8>&);

	bool canPawnMove(const auto&, const std::array<std::array<Field, 8>, 8>&);

	bool isHorizontal(const auto&);

	bool isVertical(const auto&);

	bool isDiagonal(const auto&);

	bool isKnight(const auto&);

	bool isPawn(const auto&, const std::array<std::array<Field, 8>, 8>&);

	bool checkDirection(const auto&, const std::array<std::array<Field, 8>, 8>&);
	bool checkLength(const auto&, const std::array<std::array<Field, 8>, 8>&);

	bool checkModifier(const auto&, const std::array<std::array<Field, 8>, 8>&);

	bool checkIfFigureMoveIsCorrect(const auto&, const std::array<std::array<Field, 8>, 8>&);

	bool isSubscriptOutOfRange(const int, const int);

	bool checkForObstacles(const MoveData&, const std::array<std::array<Field, 8>, 8>&);

	int promoteFigureChoice();

	void promote(const auto&);

	std::pair<Position, Position> getKingPosition(const std::array<std::array<Field, 8>, 8>&);

	bool isKingOnPath(const int, const int, const std::array<std::array<Field, 8>, 8>&);

	bool checkCheck(const std::array<std::array<Field, 8>, 8>&);

	void checkFieldsNearKing(const int, const int, std::map<Position, bool>,
	                         const std::array<std::array<Field, 8>, 8>&);

	bool canKingMove(const std::array<std::array<Field, 8>, 8>&);

	bool isCheckingFigureOnPathOf(const int, const int, const std::array<std::array<Field, 8>, 8>&);

	bool canKillCheckingFigure(const std::array<std::array<Field, 8>, 8>&);

	std::vector<Position> getCheckingFigurePath(Position, const std::array<std::array<Field, 8>, 8>&);

	bool canBlockPathOfCheckingFigure(const int, const int, Position,
	                                  const std::array<std::array<Field, 8>, 8>&);

	bool canDefendKing(const std::array<std::array<Field, 8>, 8>&);

	void isCheckMate(const std::array<std::array<Field, 8>, 8>&);

	bool checkMoveDataForNullptr(const auto&, const std::array<std::array<Field, 8>, 8>&);

	bool checkIfMoveIsPossible(const std::pair<Position, Position>&);

	void move(const std::pair<Position, Position>&);

	friend std::ostream& operator <<(std::ostream&, const Board&);

private:
	bool check{false};
	Position checkingFigure{};
	bool checkMate{false};
	std::pair<Position, Position> enemyKing{};
	std::array<std::array<Field, 8>, 8> fields{};
	const Color& turn;
};
