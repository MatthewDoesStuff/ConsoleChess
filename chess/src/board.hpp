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
	Board(const Color& turn) : turn{turn}
	{
		for (int row{0}; row < 8; ++row)
		{
			for (int col{0}; col < 8; ++col)
			{
				if (row == 1)
				{
					fields[row][col].setFigure(std::make_shared<Pawn>(Color::black));
					//red figure color to distinct it from fields
				}
				if (row == 6)
				{
					fields[row][col].setFigure(std::make_shared<Pawn>(Color::white)); //green
				}
				if ((col + row) % 2 == 0)
				{
					fields[row][col].setColor(Color::white);
				}
				else
				{
					fields[row][col].setColor(Color::black);
				}
			}
		}

		fields[0][0].setFigure(std::make_shared<Rook>(Color::black));
		fields[0][7].setFigure(std::make_shared<Rook>(Color::black));
		fields[0][1].setFigure(std::make_shared<Knight>(Color::black));
		fields[0][6].setFigure(std::make_shared<Knight>(Color::black));
		fields[0][2].setFigure(std::make_shared<Bishop>(Color::black));
		fields[0][5].setFigure(std::make_shared<Bishop>(Color::black));
		fields[0][4].setFigure(std::make_shared<King>(Color::black));
		fields[0][3].setFigure(std::make_shared<Queen>(Color::black));

		fields[7][0].setFigure(std::make_shared<Rook>(Color::white));
		fields[7][7].setFigure(std::make_shared<Rook>(Color::white));
		fields[7][1].setFigure(std::make_shared<Knight>(Color::white));
		fields[7][6].setFigure(std::make_shared<Knight>(Color::white));
		fields[7][2].setFigure(std::make_shared<Bishop>(Color::white));
		fields[7][5].setFigure(std::make_shared<Bishop>(Color::white));
		fields[7][4].setFigure(std::make_shared<King>(Color::white));
		fields[7][3].setFigure(std::make_shared<Queen>(Color::white));
	}

	bool getCheckMate() const
	{
		return checkMate;
	}

	bool canPawnAttack(const auto& moveData, const std::array<std::array<Field, 8>, 8>& board)
	{
		return checkModifier(moveData, board) and abs(moveData.first.x - moveData.second.x) == 1 and
			abs(moveData.first.y - moveData.second.y) == 1 and !fields[moveData.second.x][moveData.second.y].isEmpty();
	}

	bool canPawnMove(const auto& moveData)
	{
		auto length = fields[moveData.first.x][moveData.first.y].getFigureSchema().length;
		int n{length == Figure::Length::one ? 1 : 2};

		for (int i{0}; i < n; ++i)
		{
			if (!fields[moveData.first.x + i][moveData.first.y].isEmpty())
			{
				return false;
			}
		}
		return true;
	}

	bool isHorizontal(const auto& moveData)
	{
		return moveData.first.x == moveData.second.x;
	}

	bool isVertical(const auto& moveData)
	{
		return moveData.first.y == moveData.second.y;
	}

	bool isDiagonal(const auto& moveData)
	{
		return abs(moveData.first.x - moveData.second.x) == abs(moveData.first.y - moveData.second.y);
	}

	bool isKnight(const auto& moveData)
	{
		if (moveData.first.x + 2 == moveData.second.x and moveData.first.y + 1 == moveData.second.y)
		{
			return true;
		}

		if (moveData.first.x + 2 == moveData.second.x and moveData.first.y - 1 == moveData.second.y)
		{
			return true;
		}

		if (moveData.first.x - 2 == moveData.second.x and moveData.first.y + 1 == moveData.second.y)
		{
			return true;
		}

		if (moveData.first.x - 2 == moveData.second.x and moveData.first.y - 1 == moveData.second.y)
		{
			return true;
		}

		if (moveData.first.x + 1 == moveData.second.x and moveData.first.y + 2 == moveData.second.y)
		{
			return true;
		}

		if (moveData.first.x - 1 == moveData.second.x and moveData.first.y + 2 == moveData.second.y)
		{
			return true;
		}

		if (moveData.first.x + 1 == moveData.second.x and moveData.first.y - 2 == moveData.second.y)
		{
			return true;
		}

		if (moveData.first.x - 1 == moveData.second.x and moveData.first.y - 2 == moveData.second.y)
		{
			return true;
		}
		return false;
	}

	bool isPawn(const auto& moveData, const std::array<std::array<Field, 8>, 8>& board)
	{
		if (moveData.first.y == moveData.second.y)
		{
			return true;
		}
		return canPawnAttack(moveData, board);
	}

	bool checkDirection(const auto& moveData, const std::array<std::array<Field, 8>, 8>& board)
	{
		const Figure::Directions figureDirection{
			board[moveData.first.x][moveData.first.y].getFigureSchema().direction
		};

		switch (figureDirection)
		{
		case Figure::Directions::vertical:
			return isVertical(moveData);

		case Figure::Directions::horizontalAndVertical:
			return isHorizontal(moveData) or isVertical(moveData);

		case Figure::Directions::diagonal:
			return isDiagonal(moveData);

		case Figure::Directions::all:
			return isHorizontal(moveData) or isVertical(moveData) or isDiagonal(moveData);

		case Figure::Directions::knight:
			return isKnight(moveData);

		case Figure::Directions::pawn:
			return isPawn(moveData, board);
		}
		return false;
	}

	bool checkLength(const auto& moveData, const std::array<std::array<Field, 8>, 8>& board)
	{
		Figure::Length figureLength{board[moveData.first.x][moveData.first.y].getFigureSchema().length};

		if (figureLength == Figure::Length::noLimit)
		{
			return true;
		}
		if (figureLength == Figure::Length::one)
		{
			if ((abs(moveData.first.x - moveData.second.x) == 1 and moveData.first.y == moveData.second.y) or (
					abs(moveData.first.y - moveData.second.y) == 1 and moveData.first.x == moveData.second.x)
				or abs(moveData.first.x - moveData.second.x) == 1 and abs(moveData.first.y - moveData.second.y == 1))
			{
				return true;
			}
		}
		if (figureLength == Figure::Length::knight)
		{
			if ((abs(moveData.first.x - moveData.second.x) == 2 and abs(moveData.first.y - moveData.second.y) == 1) or (
				abs(moveData.first.y - moveData.second.y) == 2 and abs(moveData.first.x - moveData.second.x) == 1))
			{
				return true;
			}
		}
		if (figureLength == Figure::Length::two)
		{
			if (abs(moveData.first.x - moveData.second.x) == 2 or abs(moveData.first.x - moveData.second.x) == 1)
			{
				return true;
			}
		}
		return false;
	}

	bool checkModifier(const auto& moveData, const std::array<std::array<Field, 8>, 8>& board)
	{
		const Figure::Modifiers figureModifier{board[moveData.first.x][moveData.first.y].getFigureSchema().modifier};

		if (figureModifier == Figure::Modifiers::none)
		{
			return true;
		}

		if (figureModifier == Figure::Modifiers::onlyTowardsEnemy)
		{
			if (board[moveData.first.x][moveData.first.y].getFigureColor() == Color::white and moveData.
				first.x > moveData.second.x)
			{
				return true;
			}
			if (board[moveData.first.x][moveData.first.y].getFigureColor() == Color::black and moveData.
				first.x < moveData.second.x)
			{
				return true;
			}
		}

		if (figureModifier == Figure::Modifiers::king)
		{
			auto kings = getKingPosition(board);

			int diffX{kings.first.x - kings.second.x};
			int diffY{kings.first.y - kings.second.y};

			int tempX{diffX < 0 ? -1 : 1};
			int tempY{diffY < 0 ? -1 : 1};

			if (diffX < tempX and diffY < tempY)
			{
				return true;
			}
			if (diffX > tempX and diffY > tempY)
			{
				return true;
			}
		}
		return false;
	}

	bool checkIfFigureMoveIsCorrect(const auto& moveData, const std::array<std::array<Field, 8>, 8>& board)
	{
		return checkDirection(moveData, board) and checkLength(moveData, board) and checkModifier(moveData, board);
	}

	bool isSubscriptOutOfRange(const int x, const int y)
	{
		return not(x >= 0 and y >= 0 and x <= 7 and y <= 7);
	}

	bool checkForObstacles(const MoveData& ObstacleData, const std::array<std::array<Field, 8>, 8>& board)
	{
		const Figure::Directions figureDirection{
			board[ObstacleData.first.x][ObstacleData.first.y].getFigureSchema().direction
		};

		int diff{ObstacleData.first.x - ObstacleData.second.x};
		int diffY{ObstacleData.first.y - ObstacleData.second.y};

		int modX{diff < 0 ? 1 : -1};
		int temp = modX;
		int modY{diffY < 0 ? 1 : -1};
		int tempY = modY;

		int n{diff < 0 ? -diff : diff};
		int x{ObstacleData.first.x};
		int y{ObstacleData.first.y};

		switch (figureDirection)
		{
		case Figure::Directions::vertical:
			for (int i{0}; i < n - 1; ++i)
			{
				if (!board[x + modX][y].isEmpty())
				{
					return true;
				}
				modX += temp;
			}
			return false;

		case Figure::Directions::horizontalAndVertical:
			for (int i{0}; i < n - 2; ++i)
			{
				if (!board[x + modX][y].isEmpty())
				{
					return true;
				}
				if (!board[x][y + modY].isEmpty())
				{
					return true;
				}
				modX += temp;
				modX += tempY;
			}
			return false;

		case Figure::Directions::diagonal:
			for (int i{0}; i < n - 2; ++i)
			{
				if (!board[x + modX][y + modY].isEmpty())
				{
					return true;
				}
				modX += temp;
				modY += tempY;
			}
			return false;

		case Figure::Directions::all:
			for (int i{0}; i < n - 2; ++i)
			{
				if (!board[x + modX][y].isEmpty() or !board[x][y + modY].isEmpty() or !board[x + modX][y + modY].
					isEmpty())
				{
					return true;
				}
				modX += temp;
			}
			return false;

		case Figure::Directions::pawn:
			return canPawnMove(ObstacleData);
		case Figure::Directions::knight:
		default:
			return false;
		}
	}

	int promoteFigureChoice()
	{
		int figureChoice{};

		std::cout << "1.Queen /n"
			"2.Knight /n"
			"3.Bishop /n"
			"4.Rook /n"
			"Promote to:";
		std::cin >> figureChoice;

		return figureChoice;
	}

	void promote(const auto& moveData)
	{
		auto color = fields[moveData.second.x][moveData.second.y].getFigureColor();
		const int figureChoice = promoteFigureChoice();

		while (figureChoice < 1 or figureChoice > 4)
		{
			std::cout << "wrong number";
			promoteFigureChoice();
		}

		switch (figureChoice)
		{
		case 1:
			fields[moveData.second.x][moveData.second.y].setFigure(std::make_shared<Queen>(color));
			break;
		case 2:
			fields[moveData.second.x][moveData.second.y].setFigure(std::make_shared<Knight>(color));
			break;
		case 3:
			fields[moveData.second.x][moveData.second.y].setFigure(std::make_shared<Bishop>(color));
			break;
		case 4:
			fields[moveData.second.x][moveData.second.y].setFigure(std::make_shared<Rook>(color));
			break;
		default:
			break;
		}
	}

	std::pair<Position, Position> getKingPosition(const std::array<std::array<Field, 8>, 8>& board)
	{
		Position whiteKing{};
		Position blackKing{};

		for (int x{0}; x < 8; ++x)
		{
			for (int y{0}; y < 8; ++y)
			{
				if (board[x][y].isKing() and board[x][y].getFigureColor() == Color::white)
				{
					whiteKing = Position{x, y};
				}
				else if (board[x][y].isKing() and board[x][y].getFigureColor() == Color::black)
				{
					blackKing = Position{x, y};
				}
			}
		}
		return std::make_pair(whiteKing, blackKing);
	}

	bool isKingOnPath(const int x, const int y, const std::array<std::array<Field, 8>, 8>& board)
	{
		const Figure::Directions figureDirection{board[x][y].getFigureSchema().direction};
		const auto kings = getKingPosition(board);

		const Position& enemyKingPosition = board[x][y].getFigureColor() == Color::white
			                                    ? kings.second
			                                    : kings.first;

		Position fieldData = Position{x, y};
		const std::pair<Position, Position> obstacleData = std::make_pair(fieldData, enemyKingPosition);

		int diff{x - enemyKingPosition.x};
		int diffY{y - enemyKingPosition.y};

		int modX{diff < 0 ? 1 : -1};
		int temp = modX;
		int modY{diffY < 0 ? 1 : -1};
		int tempY = modY;

		int n{diff < 0 ? -diff : diff};

		switch (figureDirection)
		{
		case Figure::Directions::vertical:
			for (int i{0}; i < 1; ++i)
			{
				if (!checkForObstacles(obstacleData, board) and !isSubscriptOutOfRange(x + modX, y + modY) and board[x +
						modX]
					[y].isKing() and board[x][y].getFigureColor() != board[x + modX][y].getFigureColor())
				{
					return true;
				}
				modX += temp;
			}
			return false;


		case Figure::Directions::horizontalAndVertical:
			for (int i{0}; i < n; ++i)
			{
				if (!checkForObstacles(obstacleData, board) and !isSubscriptOutOfRange(x + modX, y + modY))
				{
					if (board[x + modX][y].isKing() and board[x][y].getFigureColor() != board[x + modX][y].
						getFigureColor())
					{
						return true;
					}
					if (board[x][y + modY].isKing() and board[x][y].getFigureColor() != board[x][y + modY].
						getFigureColor())
					{
						return true;
					}
				}
				modX += temp;
				modY += tempY;
			}
			return false;

		case Figure::Directions::diagonal:
			for (int i{0}; i < n; ++i)
			{
				if (!checkForObstacles(obstacleData, board) and !isSubscriptOutOfRange(x + modX, y + modY) and board[x +
						modX]
					[y + modY].isKing() and board[x][y].getFigureColor() != board[x + modX][y + modY].
					getFigureColor())
				{
					return true;
				}
				modX += temp;
				modY += tempY;
			}
			return false;

		case Figure::Directions::all:
			for (int i{0}; i < n; ++i)
			{
				if (!checkForObstacles(obstacleData, board) and !isSubscriptOutOfRange(x + modX, y + modY))
				{
					if (board[x + modX][y].isKing() and board[x][y].getFigureColor() != board[x + modX][y].
						getFigureColor())
					{
						return true;
					}
					if (board[x][y + modY].isKing() and board[x][y].getFigureColor() != board[x][y + modY].
						getFigureColor())
					{
						return true;
					}
					if (board[x + modX][y + modY].isKing() and board[x][y].getFigureColor() != board[x + modX][y +
						modY].getFigureColor())
					{
						return true;
					}
				}
				modX += temp;
				modY += tempY;
			}
			return false;

		case Figure::Directions::knight:

			if (x + 1 <= 7 and y + 2 <= 7 and board[x + 1][y + 2].isKing() and board[x][y].getFigureColor() != board[
				x + 1][y + 2].getFigureColor())
			{
				return true;
			}

			if (x + 1 <= 7 and y - 2 >= 0 and board[x + 1][y - 2].isKing() and board[x][y].getFigureColor() != board[
				x + 1][y - 2].getFigureColor())
			{
				return true;
			}

			if (x - 1 >= 0 and y + 2 <= 7 and board[x - 1][y + 2].isKing() and board[x][y].getFigureColor() != board[
				x - 1][y + 2].getFigureColor())
			{
				return true;
			}

			if (x - 1 >= 0 and y - 2 >= 0 and board[x - 1][y - 2].isKing() and board[x][y].getFigureColor() != board[
				x - 1][y - 2].getFigureColor())
			{
				return true;
			}

			if (x + 2 <= 7 and y - 1 >= 0 and board[x + 2][y - 1].isKing() and board[x][y].getFigureColor() != board[
				x + 2][y - 1].getFigureColor())
			{
				return true;
			}

			if (x - 2 >= 0 and y + 1 <= 7 and board[x - 2][y + 1].isKing() and board[x][y].getFigureColor() != board[
				x - 2][y + 1].getFigureColor())
			{
				return true;
			}

			if (x - 2 >= 0 and y - 1 >= 0 and board[x - 2][y - 1].isKing() and board[x][y].getFigureColor() != board[
				x - 2][y - 1].getFigureColor())
			{
				return true;
			}

			if (x + 2 <= 7 and y + 1 <= 7 and board[x + 2][y + 1].isKing() and board[x][y].getFigureColor() != board[
				x + 2][y + 1].getFigureColor())
			{
				return true;
			}
			return false;
		default:
			return false;
		}
	}

	bool checkCheck(const std::array<std::array<Field, 8>, 8>& board)
	{
		for (int x{0}; x < 8; ++x)
		{
			for (int y{0}; y < 8; ++y)
			{
				if (!board[x][y].isEmpty())
				{
					if (turn != board[x][y].getFigureColor())
					{
						if (isKingOnPath(x, y, board))
						{
							std::cout << "check" << x << ' ' << y;
							checkingFigure = {x, y};
							return true;
						}
					}
				}
			}
		}
		return false;
	}

	void checkFieldsNearKing(const int x, const int y, std::map<Position, bool> kingMoveMap,
	                         const std::array<std::array<Field, 8>, 8>& board)
	{
		const Figure::Directions figureDirection{board[x][y].getFigureSchema().direction};
		const auto kings = getKingPosition(board);

		const Position& enemyKingPosition = board[x][y].getFigureColor() == Color::white
			                                    ? kings.second
			                                    : kings.first;

		Position fieldData = Position{x, y};
		const std::pair<Position, Position> obstacleData = std::make_pair(fieldData, enemyKingPosition);

		for (int i : {-1, 0, 1})
		{
			for (int j : {-1, 0, 1})
			{
				if (!isSubscriptOutOfRange(enemyKingPosition.x + i, enemyKingPosition.y + j))
				{
					if ((i == -1 or i == 1) and j == 0)
					{
						if (board[enemyKingPosition.x + i][enemyKingPosition.y + j].isEmpty())
						{
							kingMoveMap[Position{enemyKingPosition.x + i, enemyKingPosition.y}] = true;
						}
						else
						{
							kingMoveMap[Position{enemyKingPosition.x + i, enemyKingPosition.y}] = false;
						}
					}
					if (i == 0 and (j == -1 or j == 1))
					{
						if (board[enemyKingPosition.x + i][enemyKingPosition.y + j].isEmpty())
						{
							kingMoveMap[Position{enemyKingPosition.x, enemyKingPosition.y + j}] = true;
						}
						else
						{
							kingMoveMap[Position{enemyKingPosition.x, enemyKingPosition.y + j}] = false;
						}
					}
					if (board[enemyKingPosition.x + i][enemyKingPosition.y + j].isEmpty() and i != 0 and j != 0)
					{
						kingMoveMap[Position{enemyKingPosition.x + i, enemyKingPosition.y + j}] = true;
					}
					else
					{
						kingMoveMap[Position{enemyKingPosition.x + i, enemyKingPosition.y + j}] = false;
					}
				}
			}
		}

		int diffX{x - enemyKingPosition.x};
		int diffY{y - enemyKingPosition.y};

		int modX{diffX < 0 ? 1 : -1};
		int tempX = modX;
		int modY{diffY < 0 ? 1 : -1};
		int tempY = modY;

		int n{diffX < 0 ? -diffX : diffX};

		switch (figureDirection)
		{
		case Figure::Directions::vertical:
			for (int i{0}; i < 1; ++i)
			{
				if (!checkForObstacles(obstacleData, board) and !isSubscriptOutOfRange(x + modX, y) and kingMoveMap.
					contains(
						Position{x + modX, y}))
				{
					kingMoveMap[Position{x + modX, y}] = false;
				}
				modX += tempX;
			}
			break;


		case Figure::Directions::horizontalAndVertical:
			for (int i{0}; i < n; ++i)
			{
				if (!checkForObstacles(obstacleData, board) and !isSubscriptOutOfRange(x + modX, y + modY))
				{
					if (kingMoveMap.contains(Position{x + modX, y}))
					{
						kingMoveMap[Position{x + modX, y}] = false;
					}
					if (kingMoveMap.contains(Position{x, y + modY}))
					{
						kingMoveMap[Position{x, y + modY}] = false;
					}
				}
				modX += tempX;
				modY += tempY;
			}
			break;

		case Figure::Directions::diagonal:
			for (int i{0}; i < n; ++i)
			{
				if (!checkForObstacles(obstacleData, board) and !isSubscriptOutOfRange(x + modX, y + modY) and
					kingMoveMap.
					contains(Position{x + modX, y + modY}))
				{
					kingMoveMap[Position{x + modX, y + modY}] = false;
				}

				modX += tempX;
				modY += tempY;
			}
			break;

		case Figure::Directions::all:
			for (int i{0}; i < n; ++i)
			{
				if (!checkForObstacles(obstacleData, board) and !isSubscriptOutOfRange(x + modX, y + modY) and
					kingMoveMap.
					contains(Position{x + modX, y}))
				{
					kingMoveMap[Position{x + modX, y}] = false;
				}

				if (!checkForObstacles(obstacleData, board) and !isSubscriptOutOfRange(x + modX, y + modY) and
					kingMoveMap.
					contains(Position{x, y + modY}))
				{
					kingMoveMap[Position{x, y + modY}] = false;
				}

				if (!checkForObstacles(obstacleData, board) and !isSubscriptOutOfRange(x + modX, y + modY) and
					kingMoveMap.
					contains(Position{x + modX, y + modY}))
				{
					kingMoveMap[Position{x + modX, y + modY}] = false;
				}

				modX += tempX;
				modY += tempY;
			}
			break;

		case Figure::Directions::knight:
			if (x + 2 <= 7 and y + 1 <= 7 and kingMoveMap.contains(Position{x + 2, y + 1}))
			{
				kingMoveMap[Position{x + 2, y + 1}] = false;
			}

			if (x + 2 <= 7 and y - 1 >= 0 and kingMoveMap.contains(Position{x + 2, y - 1}))
			{
				kingMoveMap[Position{x + 2, y - 1}] = false;
			}

			if (x - 2 >= 0 and y + 1 <= 7 and kingMoveMap.contains(Position{x - 2, y + 1}))
			{
				kingMoveMap[Position{x - 2, y + 1}] = false;
			}

			if (x - 2 >= 0 and y - 1 >= 0 and kingMoveMap.contains(Position{x - 2, y - 1}))
			{
				kingMoveMap[Position{x - 2, y - 1}] = false;
			}

			if (x + 1 <= 7 and y + 2 <= 7 and kingMoveMap.contains(Position{x + 1, y + 2}))
			{
				kingMoveMap[Position{x + 1, y + 2}] = false;
			}

			if (x + 1 <= 7 and y - 2 >= 0 and kingMoveMap.contains(Position{x + 1, y - 2}))
			{
				kingMoveMap[Position{x + 1, y - 2}] = false;
			}

			if (x - 1 >= 0 and y + 2 <= 7 and kingMoveMap.contains(Position{x - 1, y + 2}))
			{
				kingMoveMap[Position{x - 1, y + 2}] = false;
			}

			if (x - 1 >= 0 and y - 2 >= 0 and kingMoveMap.contains(Position{x - 1, y - 2}))
			{
				kingMoveMap[Position{x - 1, y - 2}] = false;
			}
			break;
		case Figure::Directions::pawn:
			if (!checkForObstacles(obstacleData, board) and !isSubscriptOutOfRange(x + modX, y + modY) and
				kingMoveMap.
				contains(Position{x + modX, y + modY}))
			{
				kingMoveMap[Position{x + modX, y + modY}] = false;
			}
			break;
		}
	}

	bool canKingMove(const std::array<std::array<Field, 8>, 8>& board)
	{
		std::map<Position, bool> kingMoveMap = {};

		for (int x{0}; x < 8; ++x)
		{
			for (int y{0}; y < 8; ++y)
			{
				if (!board[x][y].isEmpty())
				{
					if (turn != board[x][y].getFigureColor())
					{
						checkFieldsNearKing(x, y, kingMoveMap, board);
					}
				}
			}
		}

		return std::ranges::any_of(kingMoveMap, [](const auto& it) { return it.second; });
	}

	bool isCheckingFigureOnPathOf(const int x, const int y, const std::array<std::array<Field, 8>, 8>& board)
	{
		const Figure::Directions figureDirection{board[x][y].getFigureSchema().direction};

		Position fieldData = Position{x, y};
		const std::pair<Position, Position> obstacleData = std::make_pair(fieldData, checkingFigure);

		int diff{x - checkingFigure.x};
		int diffY{y - checkingFigure.y};

		int modX{diff < 0 ? 1 : -1};
		int temp = modX;
		int modY{diffY < 0 ? 1 : -1};
		int tempY = modY;

		int n{diff < 0 ? -diff : diff};

		switch (figureDirection)
		{
		case Figure::Directions::vertical:
			for (int i{0}; i < 1; ++i)
			{
				if (!checkForObstacles(obstacleData, board) and !isSubscriptOutOfRange(x + modX, y) and x + modX ==
					checkingFigure.x and y == checkingFigure.y)
				{
					return true;
				}
				modX += temp;
			}
			return false;


		case Figure::Directions::horizontalAndVertical:
			for (int i{0}; i < n; ++i)
			{
				if (!checkForObstacles(obstacleData, board) and !isSubscriptOutOfRange(x + modX, y + modY))
				{
					if (x + modX == checkingFigure.x and y == checkingFigure.y)
					{
						return true;
					}
					if (x == checkingFigure.x and y + modY == checkingFigure.y)
					{
						return true;
					}
				}
				modX += temp;
				modY += tempY;
			}
			return false;

		case Figure::Directions::diagonal:
			for (int i{0}; i < n; ++i)
			{
				if (!checkForObstacles(obstacleData, board) and !isSubscriptOutOfRange(x + modX, y + modY) and x + modX
					==
					checkingFigure.x and x + modY == checkingFigure.y)
				{
					return true;
				}
				modX += temp;
				modY += tempY;
			}
			return false;

		case Figure::Directions::all:
			for (int i{0}; i < n; ++i)
			{
				if (!checkForObstacles(obstacleData, board) and !isSubscriptOutOfRange(x + modX, y + modY))
				{
					if (x + modX == checkingFigure.x and y == checkingFigure.y)
					{
						return true;
					}
					if (x == checkingFigure.x and y + modY == checkingFigure.y)
					{
						return true;
					}
					if (x + modX == checkingFigure.x and y + modY == checkingFigure.y)
					{
						return true;
					}
				}
				modX += temp;
				modY += tempY;
			}
			return false;

		case Figure::Directions::knight:
			if (!isSubscriptOutOfRange(x + 2, y + 2) or !isSubscriptOutOfRange(x + 2, y - 2) or !
				isSubscriptOutOfRange(x - 2, y + 2) or !isSubscriptOutOfRange(x - 2, y - 2))
			{
				if (x + 2 == checkingFigure.x and y + 1 == checkingFigure.y)
				{
					return true;
				}
				if (x + 2 == checkingFigure.x and y - 1 == checkingFigure.y)
				{
					return true;
				}
				if (x - 2 == checkingFigure.x and y + 1 == checkingFigure.y)
				{
					return true;
				}
				if (x - 2 == checkingFigure.x and y - 1 == checkingFigure.y)
				{
					return true;
				}
				if (x + 1 == checkingFigure.x and y + 2 == checkingFigure.y)
				{
					return true;
				}
				if (x + 1 == checkingFigure.x and y - 2 == checkingFigure.y)
				{
					return true;
				}
				if (x - 1 == checkingFigure.x and y + 2 == checkingFigure.y)
				{
					return true;
				}
				if (x - 1 == checkingFigure.x and y - 2 == checkingFigure.y)
				{
					return true;
				}
			}
			return false;
		case Figure::Directions::pawn:
		default:
			return false;
		}
	}

	bool canKillCheckingFigure(const std::array<std::array<Field, 8>, 8>& board)
	{
		for (int x{0}; x < 8; ++x)
		{
			for (int y{0}; y < 8; ++y)
			{
				if (!board[x][y].isEmpty())
				{
					if (turn == board[x][y].getFigureColor())
					{
						return isCheckingFigureOnPathOf(x, y, board);
					}
				}
			}
		}
		return false;
	}

	std::vector<Position> getCheckingFigurePath(Position checkingFig, const std::array<std::array<Field, 8>, 8>& board)
	{
		std::vector<Position> checkingFigurePath;
		const Figure::Directions figureDirection{board[checkingFig.x][checkingFig.y].getFigureSchema().direction};

		const auto kings = getKingPosition(board);
		const Position& enemyKingPosition = board[checkingFig.x][checkingFig.y].getFigureColor() ==
		                                    Color::white
			                                    ? kings.second
			                                    : kings.first;

		int diff{checkingFig.x - enemyKingPosition.x};
		int diffY{checkingFig.y - enemyKingPosition.y};

		int modX{diff < 0 ? 1 : -1};
		int temp = modX;
		int modY{diffY < 0 ? 1 : -1};
		int tempY = modY;

		int n{diff < 0 ? -diff : diff};

		switch (figureDirection)
		{
		case Figure::Directions::vertical:
			for (int i{0}; i < n - 1; ++i)
			{
				if (!isSubscriptOutOfRange(checkingFig.x + modX, checkingFig.y + modX))
				{
					checkingFigurePath.emplace_back(Position{checkingFig.x + modX, checkingFig.y});
				}
				modX += temp;
			}
			return checkingFigurePath;


		case Figure::Directions::horizontalAndVertical:
			for (int i{0}; i < n - 1; ++i)
			{
				if (!isSubscriptOutOfRange(checkingFig.x + modX, checkingFig.y + modY))
				{
					if (diffY == 0)
					{
						checkingFigurePath.emplace_back(Position{checkingFig.x + modX, checkingFig.y});
					}
					if (diff == 0)
					{
						checkingFigurePath.emplace_back(Position{checkingFig.x, checkingFig.y + modY});
					}
				}
				modX += temp;
				modY += tempY;
			}
			return checkingFigurePath;

		case Figure::Directions::diagonal:
			for (int i{0}; i < n - 1; ++i)
			{
				if (!isSubscriptOutOfRange(checkingFig.x + modX, checkingFig.y + modY))
				{
					checkingFigurePath.emplace_back(Position{checkingFig.x + modX, checkingFig.y + modY});
				}
				modX += temp;
				modY += tempY;
			}
			return checkingFigurePath;

		case Figure::Directions::all:
			for (int i{0}; i < n - 1; ++i)
			{
				if (!isSubscriptOutOfRange(checkingFig.x + modX, checkingFig.y + modY))
				{
					if (diffY == 0)
					{
						checkingFigurePath.emplace_back(Position{checkingFig.x + modX, checkingFig.y});
					}
					if (diff == 0)
					{
						checkingFigurePath.emplace_back(Position{checkingFig.x, checkingFig.y + modY});
					}
					if (diff == diffY)
					{
						checkingFigurePath.emplace_back(Position{checkingFig.x + modX, checkingFig.y + modY});
					}
				}
				modX += temp;
				modY += tempY;
			}
			return checkingFigurePath;

		case Figure::Directions::knight:
		case Figure::Directions::pawn:
		default:
			return checkingFigurePath;
		}
	}

	bool canBlockPathOfCheckingFigure(const int x, const int y, Position checkingFig,
	                                  const std::array<std::array<Field, 8>, 8>& board)
	{
		const std::vector<Position> checkingFigurePath = getCheckingFigurePath(checkingFig, board);
		const Figure::Directions figureDirection{board[x][y].getFigureSchema().direction};


		int diffX{x - checkingFig.x};
		int diffY{y - checkingFig.y};

		int modX{diffX < 0 ? 1 : -1};
		int tempX = modX;
		int modY{diffY < 0 ? 1 : -1};
		int tempY = modY;

		int n{diffX < 0 ? -diffX : diffX};

		switch (figureDirection)
		{
		case Figure::Directions::vertical:
			for (int i{0}; i < n - 1; ++i)
			{
				if (!isSubscriptOutOfRange(checkingFig.x + modX, checkingFig.y) and checkForObstacles(
					std::make_pair(Position{x, y}, checkingFig), board))
				{
					if (diffY == 0)
					{
						for (auto& pathField : checkingFigurePath)
						{
							if (pathField == Position{x + modX, y})
							{
								return true;
							}
						}
					}
					if (diffX == 0)
					{
						for (auto& pathField : checkingFigurePath)
						{
							if (pathField == Position{x, y + modY})
							{
								return true;
							}
						}
					}
				}
				modX += tempX;
			}
			return false;


		case Figure::Directions::horizontalAndVertical:
			for (int i{0}; i < n - 1; ++i)
			{
				if (!isSubscriptOutOfRange(checkingFig.x + modX, checkingFig.y + modY) and checkForObstacles(
					std::make_pair(Position{x, y}, checkingFig), board))
				{
					for (auto& pathField : checkingFigurePath)
					{
						if (pathField == Position{x + modX, y})
						{
							return true;
						}
					}
				}
				modX += tempX;
				modY += tempY;
			}
			return false;


		case Figure::Directions::diagonal:
			for (int i{0}; i < n - 1; ++i)
			{
				if (!isSubscriptOutOfRange(checkingFig.x + modX, checkingFig.y + modY) and checkForObstacles(
					std::make_pair(Position{x, y}, checkingFig), board))
				{
					for (auto& pathField : checkingFigurePath)
					{
						if (pathField == Position{x + modX, y + modY})
						{
							return true;
						}
					}
				}
				modX += tempX;
				modY += tempY;
			}
			return false;


		case Figure::Directions::all:
			for (int i{0}; i < n - 1; ++i)
			{
				if (!isSubscriptOutOfRange(checkingFig.x + modX, checkingFig.y + modY) and checkForObstacles(
					std::make_pair(Position{x, y}, checkingFig), board))
				{
					if (diffY == 0)
					{
						for (auto& pathField : checkingFigurePath)
						{
							if (pathField == Position{x + modX, y})
							{
								return true;
							}
						}
					}
					if (diffX == 0)
					{
						for (auto& pathField : checkingFigurePath)
						{
							if (pathField == Position{x, y + modY})
							{
								return true;
							}
						}
					}
					if (diffX == diffY)
					{
						for (auto& pathField : checkingFigurePath)
						{
							if (pathField == Position{x + modX, y + modY})
							{
								return true;
							}
						}
					}
				}
				modX += tempX;
				modY += tempY;
			}
			return false;

		case Figure::Directions::knight:
		case Figure::Directions::pawn:
		default:
			return false;
		}
	}

	bool canDefendKing(const std::array<std::array<Field, 8>, 8>& board)
	{
		for (int x{0}; x < 8; ++x)
		{
			for (int y{0}; y < 8; ++y)
			{
				if (!board[x][y].isEmpty())
				{
					if (turn == board[x][y].getFigureColor() and canBlockPathOfCheckingFigure(
						x, y, checkingFigure, board))
					{
						return true;
					}
				}
			}
		}
		return false;
	}

	void isCheckMate(const std::array<std::array<Field, 8>, 8>& board)
	{
		if (checkCheck(board))
		{
			if (!canKingMove(board) and !canKillCheckingFigure(board) and !canDefendKing(board))
			{
				std::cout << "checkmate";
				checkMate = true;
			}
		}
	}

	bool checkMoveDataForNullptr(const auto& moveData, const std::array<std::array<Field, 8>, 8>& board)
	{
		return board[moveData.first.x][moveData.first.y].isEmpty();
	}

	bool checkIfMoveIsPossible(const auto& moveData)
	{
		auto fieldsCopy{fields};

		if (turn != fieldsCopy[moveData.first.x][moveData.first.y].getFigureColor())
		{
			return false;
		}

		if (!checkIfFigureMoveIsCorrect(moveData, fieldsCopy) and checkForObstacles(moveData, fieldsCopy))
		{
			return false;
		}

		fieldsCopy[moveData.second.x][moveData.second.y].placeFigure(
			std::move(fieldsCopy[moveData.first.x][moveData.first.y].pickFigure()));

		if (checkCheck(fieldsCopy))
		{
			return false;
		}

		return true;
	}


	void move(const auto& moveData)
	{
		if (checkIfMoveIsPossible(moveData))
		{
			fields[moveData.second.x][moveData.second.y].placeFigure(
				std::move(fields[moveData.first.x][moveData.first.y].pickFigure()));

			if (fields[moveData.second.x][moveData.second.y].isPawn() and (moveData.second.x == 0 or moveData.second.x
				==
				7))
			{
				promote(moveData);
			}

			enemyKing = getKingPosition(fields);

			if (fields[moveData.second.x][moveData.second.y].isPawn())
			{
				fields[moveData.second.x][moveData.second.y].pawnFirstMoveDone();
			}
		}
	}

	friend std::ostream& operator <<(std::ostream& out, const Board& b)
	{
		out << ' ';
		for (char letter{'a'}; letter < 'a' + 8; ++letter)
		{
			out << ' ' << letter << ' ';
		}
		for (int row{0}; row < 8; ++row)
		{
			out << '\n';
			out << row + 1;

			for (int col{0}; col < 8; ++col)
			{
				out << b.fields[row][col];
			}
		}
		return out;
	}

private:
	bool check{false};
	Position checkingFigure{};
	bool checkMate{false};
	std::pair<Position, Position> enemyKing{};
	std::array<std::array<Field, 8>, 8> fields{};
	const Color& turn;
};
