#pragma once

#include <algorithm>
#include <array>
#include <iostream>
#include <ranges>
#include <unordered_map>

#include "Bishop.hpp"
#include "chess.hpp"
#include "field.hpp"
#include "figure.hpp"
#include "King.hpp"
#include "Knight.hpp"
#include "Pawn.hpp"
#include "Queen.hpp"
#include "Rook.hpp"

class Board {
public:
	Board()
	{
		for (int row{ 0 }; row < 8; ++row) {
			for (int col{ 0 }; col < 8; ++col) {
				if (row == 1)
				{
					fields[row][col].setFigure(std::make_unique<Pawn>(Figure::FigureColor::black)); //red figure color to distinct it from fields
				}
				if (row == 6)
				{
					fields[row][col].setFigure(std::make_unique<Pawn>(Figure::FigureColor::white)); //green
				}
				if ((col + row) % 2 == 0) {
					fields[row][col].setColor(Field::Color::white);

				}
				else {
					fields[row][col].setColor(Field::Color::black);
				}
			}
		}

		fields[0][0].setFigure(std::make_unique<Rook>(Figure::FigureColor::black));
		fields[0][7].setFigure(std::make_unique<Rook>(Figure::FigureColor::black));
		fields[0][1].setFigure(std::make_unique<Knight>(Figure::FigureColor::black));
		fields[0][6].setFigure(std::make_unique<Knight>(Figure::FigureColor::black));
		fields[0][2].setFigure(std::make_unique<Bishop>(Figure::FigureColor::black));
		fields[0][5].setFigure(std::make_unique<Bishop>(Figure::FigureColor::black));
		fields[0][4].setFigure(std::make_unique<King>(Figure::FigureColor::black));
		fields[0][3].setFigure(std::make_unique<Queen>(Figure::FigureColor::black));

		fields[7][0].setFigure(std::make_unique<Rook>(Figure::FigureColor::white));
		fields[7][7].setFigure(std::make_unique<Rook>(Figure::FigureColor::white));
		fields[7][1].setFigure(std::make_unique<Knight>(Figure::FigureColor::white));
		fields[7][6].setFigure(std::make_unique<Knight>(Figure::FigureColor::white));
		fields[7][2].setFigure(std::make_unique<Bishop>(Figure::FigureColor::white));
		fields[7][5].setFigure(std::make_unique<Bishop>(Figure::FigureColor::white));
		fields[7][4].setFigure(std::make_unique<King>(Figure::FigureColor::white));
		fields[7][3].setFigure(std::make_unique<Queen>(Figure::FigureColor::white));

	}

	bool canPawnAttack(auto moveData)
	{
		if (checkModifier(moveData) and abs(moveData.first.x - moveData.second.x) == 1 and abs(moveData.first.y - moveData.second.y) == 1 and !fields[moveData.second.x][moveData.second.y].isEmpty())
		{
			return true;
		}
		return false;
	}

	bool canPawnMove(auto moveData)
	{
		auto length = fields[moveData.first.x][moveData.first.y].getFigureSchema().length;
		int n{ length == Figure::Length::one ? 1 : 2 };

		for (int i{ 0 }; i < n; ++i)
		{
			if (!fields[moveData.first.x + i][moveData.first.y].isEmpty())
			{
				return false;
			}
		}
		return true;
	}

	bool isHorizontal(auto moveData)
	{
		if (moveData.first.x == moveData.second.x)
		{
			return true;
		}
		return false;
	}

	bool isVertical(auto moveData)
	{
		if (moveData.first.y == moveData.second.y)
		{
			return true;
		}
		return false;
	}

	bool isDiagonal(auto moveData)
	{
		if (abs(moveData.first.x - moveData.second.x) == abs(moveData.first.y - moveData.second.y))
		{
			return true;
		}
		return false;
	}

	bool isKnight(auto moveData) {

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

	bool isPawn(auto moveData)
	{
		if (moveData.first.y == moveData.second.y)
		{
			return true;
		}
		return canPawnAttack(moveData);

	}

	bool checkDirection(auto moveData)
	{
		Figure::Directions figureDirection{fields[moveData.first.x][moveData.first.y].getFigureSchema().direction};

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
			return isPawn(moveData);
		}
		return false;
	}

	bool checkLength(auto moveData)
	{
		Figure::Length figureLength{fields[moveData.first.x][moveData.first.y].getFigureSchema().length};

		if (figureLength == Figure::Length::noLimit)
		{
			return true;
		}
		if (figureLength == Figure::Length::one)
		{
			if ((abs(moveData.first.x - moveData.second.x) == 1 and moveData.first.y == moveData.second.y) or (abs(moveData.first.y - moveData.second.y) == 1 and moveData.first.x == moveData.second.x)
				or abs(moveData.first.x - moveData.second.x) == 1 and abs(moveData.first.y - moveData.second.y == 1))
			{
				return true;
			}
		}
		if (figureLength == Figure::Length::knight)
		{
			if ((abs(moveData.first.x - moveData.second.x) == 2 and abs(moveData.first.y - moveData.second.y) == 1) or (abs(moveData.first.y - moveData.second.y) == 2 and abs(moveData.first.x - moveData.second.x) == 1))
			{
				return true;
			}
		}
		if (figureLength == Figure::Length::two)
		{
			if (abs(moveData.first.x - moveData.second.x) == 2 or abs(moveData.first.x - moveData.second.x)==1)
			{
				return true;
			}
		}
		return false;
	}

	bool checkModifier(auto moveData)
	{
		Figure::Modifiers figureModifier{fields[moveData.first.x][moveData.first.y].getFigureSchema().modifier};

		if (figureModifier == Figure::Modifiers::none)
		{
			return true;
		}

		if (figureModifier == Figure::Modifiers::onlyTowardsEnemy)
		{
			if (fields[moveData.first.x][moveData.first.y].getFigureColor() == Figure::FigureColor::white and moveData.first.x > moveData.second.x)
			{
				return true;
			}
			if (fields[moveData.first.x][moveData.first.y].getFigureColor() == Figure::FigureColor::black and moveData.first.x < moveData.second.x)
			{
				return true;
			}
		}

		if (figureModifier == Figure::Modifiers::king)
		{
			auto kings = getKingPosition();

			int diffX{ kings.first.x - kings.second.x };
			int diffY{ kings.first.y - kings.second.y };

			int tempX{ diffX < 0 ? -1 : 1 };
			int tempY{ diffY < 0 ? -1 : 1 };

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

	bool checkIfMovePossible(auto moveData)
	{
		if (checkDirection(moveData) and checkLength(moveData) and checkModifier(moveData))
		{
			return true;
		}
		return false;
	}

	bool isSubscriptOutOfRange(int x, int y)
	{
		if (x >= 0 and y >= 0 and x <= 7 and y <= 7)
		{
			return false;
		}
		return true;
	}

	bool checkForObstacles(auto ObstacleData)
	{
		Figure::Directions figureDirection{fields[ObstacleData.first.x][ObstacleData.first.y].getFigureSchema().direction};

		int diff{ ObstacleData.first.x - ObstacleData.second.x };
		int diffY{ ObstacleData.first.y - ObstacleData.second.y };

		int modX{ diff < 0 ? 1 : -1 };
		int temp = modX;
		int modY{ diffY < 0 ? 1 : -1 };
		int tempY = modY;

		int n{ diff < 0 ? -diff : diff };
		int x{ ObstacleData.first.x };
		int y{ ObstacleData.first.y };

		switch (figureDirection)
		{
		case Figure::Directions::vertical:
			for (int i{ 0 }; i < n - 1; ++i)
			{
				if (!fields[x + modX][y].isEmpty())
				{
					return true;
				}
				modX += temp;
			}
			return false;

		case Figure::Directions::horizontalAndVertical:
			for (int i{ 0 }; i < n - 2; ++i)
			{
				if (!fields[x + modX][y].isEmpty())
				{
					return true;
				}
				if (!fields[x][y + modY].isEmpty())
				{
					return true;
				}
				modX += temp;
				modX += tempY;
			}
			return false;

		case Figure::Directions::diagonal:
			for (int i{ 0 }; i < n - 2; ++i)
			{
				if (!fields[x + modX][y + modY].isEmpty())
				{
					return true;
				}
				modX += temp;
				modY += tempY;
			}
			return false;

		case Figure::Directions::all:
			for (int i{ 0 }; i < n - 2; ++i)
			{
				if (!fields[x + modX][y].isEmpty() or !fields[x][y + modY].isEmpty() or !fields[x + modX][y + modY].isEmpty())
				{
					return true;
				}
				modX += temp;
			}
			return false;

		case Figure::Directions::pawn:
			return canPawnMove(ObstacleData);

		case Figure::Directions::knight:
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

	void promote(auto moveData)
	{
		auto color = fields[moveData.second.x][moveData.second.y].getFigureColor();
		int figureChoice = promoteFigureChoice();

		while (figureChoice < 1 or figureChoice > 4)
		{
			std::cout << "wrong number";
			promoteFigureChoice();
		}

		switch (figureChoice)
		{
		case 1:
			fields[moveData.second.x][moveData.second.y].setFigure(std::make_unique<Queen>(color));
		case 2:
			fields[moveData.second.x][moveData.second.y].setFigure(std::make_unique<Knight>(color));
		case 3:
			fields[moveData.second.x][moveData.second.y].setFigure(std::make_unique<Bishop>(color));
		case 4:
			fields[moveData.second.x][moveData.second.y].setFigure(std::make_unique<Rook>(color));

		}
	}

	std::pair<Position, Position> getKingPosition()
	{
		Position whiteKing{};
		Position blackKing{};

		for (int x{ 0 }; x < 8; ++x)
		{
			for (int y{ 0 }; y < 8; ++y)
			{
				if (fields[x][y].isKing() and fields[x][y].getFigureColor() == Figure::FigureColor::white)
				{
					whiteKing = Position{ x,y };
				}
				else if (fields[x][y].isKing() and fields[x][y].getFigureColor() == Figure::FigureColor::black)
				{
					blackKing = Position{ x,y };
				}
			}
		}
		return std::make_pair(whiteKing, blackKing);
	}

	bool isKingOnPath(int x, int y)
	{

		Figure::Directions figureDirection{fields[x][y].getFigureSchema().direction};
		auto kings = getKingPosition();

		const Position& enemyKingPosition = fields[x][y].getFigureColor() == Figure::FigureColor::white ? kings.second : kings.first;

		Position fieldData = Position{ x,y };
		std::pair<Position, Position> obstacleData = std::make_pair(fieldData, enemyKingPosition);

		int diff{ x - enemyKingPosition.x };
		int diffY{ y - enemyKingPosition.y };

		int modX{ diff < 0 ? 1 : -1 };
		int temp = modX;
		int modY{ diffY < 0 ? 1 : -1 };
		int tempY = modY;

		int n{ diff < 0 ? -diff : diff };

		switch (figureDirection)
		{
		case Figure::Directions::vertical:
			for (int i{ 0 }; i < 1; ++i)
			{
				if (!checkForObstacles(obstacleData) and !isSubscriptOutOfRange(x + modX, y + modY) and fields[x + modX][y].isKing() and fields[x][y].getFigureColor() != fields[x + modX][y].getFigureColor())
				{
					return true;
				}
				modX += temp;
			}
			return false;


		case Figure::Directions::horizontalAndVertical:
			for (int i{ 0 }; i < n; ++i)
			{
				if (!checkForObstacles(obstacleData) and !isSubscriptOutOfRange(x + modX, y + modY))
				{

					if (fields[x + modX][y].isKing() and fields[x][y].getFigureColor() != fields[x + modX][y].getFigureColor()) 
					{
						return true;
					}
					if (fields[x][y + modY].isKing() and fields[x][y].getFigureColor() != fields[x][y + modY].getFigureColor())
					{
						return true;
					}

				}
				modX += temp;
				modY += tempY;

			}
			return false;

		case Figure::Directions::diagonal:
			for (int i{ 0 }; i < n; ++i)
			{
				if (!checkForObstacles(obstacleData) and !isSubscriptOutOfRange(x + modX, y + modY) and fields[x + modX][y + modY].isKing() and fields[x][y].getFigureColor() != fields[x + modX][y + modY].getFigureColor())
				{
					return true;
				}
				modX += temp;
				modY += tempY;
			}
			return false;

		case Figure::Directions::all:
			for (int i{ 0 }; i < n; ++i)
			{
				if (!checkForObstacles(obstacleData) and !isSubscriptOutOfRange(x + modX, y + modY))
				{

					if (fields[x + modX][y].isKing() and fields[x][y].getFigureColor() != fields[x + modX][y].getFigureColor())
					{
						return true;
					}
					if (fields[x][y + modY].isKing() and fields[x][y].getFigureColor() != fields[x][y + modY].getFigureColor())
					{
						return true;
					}
					if (fields[x + modX][y + modY].isKing() and fields[x][y].getFigureColor() != fields[x + modX][y + modY].getFigureColor())
					{
						return true;
					}
				}
				modX += temp;
				modY += tempY;
			}
			return false;

		case Figure::Directions::knight:

			if (x + 1 <= 7 and y + 2 <= 7 and fields[x + 1][y + 2].isKing() and fields[x][y].getFigureColor() != fields[x + 1][y + 2].getFigureColor())
			{
				return true;
			}

			if (x + 1 <= 7 and y - 2 >= 0 and fields[x + 1][y - 2].isKing() and fields[x][y].getFigureColor() != fields[x + 1][y - 2].getFigureColor())
			{
				return true;
			}

			if (x - 1 >= 0 and y + 2 <= 7 and fields[x - 1][y + 2].isKing() and fields[x][y].getFigureColor() != fields[x - 1][y + 2].getFigureColor())
			{
				return true;
			}

			if (x - 1 >= 0 and y - 2 >= 0 and fields[x - 1][y - 2].isKing() and fields[x][y].getFigureColor() != fields[x - 1][y - 2].getFigureColor())
			{
				return true;
			}

			if (x + 2 <= 7 and y - 1 >= 0 and fields[x + 2][y - 1].isKing() and fields[x][y].getFigureColor() != fields[x + 2][y - 1].getFigureColor())
			{
				return true;
			}

			if (x - 2 >= 0 and y + 1 <= 7 and fields[x - 2][y + 1].isKing() and fields[x][y].getFigureColor() != fields[x - 2][y + 1].getFigureColor())
			{
				return true;
			}

			if (x - 2 >= 0 and y - 1 >= 0 and fields[x - 2][y - 1].isKing() and fields[x][y].getFigureColor() != fields[x - 2][y - 1].getFigureColor())
			{
				return true;
			}

			if (x + 2 <= 7 and y + 1 <= 7 and fields[x + 2][y + 1].isKing() and fields[x][y].getFigureColor() != fields[x + 2][y + 1].getFigureColor())
			{
				return true;
			}
			return false;
		}
	}

	bool checkCheck()
	{
		for (int x{ 0 }; x < 8; ++x)
		{
			for (int y{ 0 }; y < 8; ++y)
			{
				if (!fields[x][y].isEmpty())
				{
					if (Chess::getTurn() and fields[x][y].getFigureColor() == Figure::FigureColor::black)
					{
						if (isKingOnPath(x, y))
						{
							std::cout << "check" << x << ' ' << y;
							checkingFigure = { x,y };
							return true;
						}
					}
					if (!Chess::getTurn() and fields[x][y].getFigureColor() == Figure::FigureColor::white)
					{
						if (isKingOnPath(x, y))
						{
							std::cout << "check" << x << ' ' << y;
							checkingFigure = { x,y };
							return true;
						}
					}
				}
			}
		}
		return false;

	}

	void checkFieldsNearKing(int x, int y, std::map<Position, bool> kingMoveMap)
	{
		Figure::Directions figureDirection{fields[x][y].getFigureSchema().direction};
		auto kings = getKingPosition();

		const Position& enemyKingPosition = fields[x][y].getFigureColor() == Figure::FigureColor::white ? kings.second : kings.first;

		Position fieldData = Position{ x,y };
		std::pair<Position, Position> obstacleData = std::make_pair(fieldData, enemyKingPosition);

		for (int i : {-1, 0, 1})
		{
			for (int j : {-1, 0, 1}) {
				if (!isSubscriptOutOfRange(enemyKingPosition.x + i, enemyKingPosition.y + j)) {
					if ((i == -1 or i == 1) and j == 0)
					{
						if (fields[enemyKingPosition.x + i][enemyKingPosition.y + j].isEmpty()) {
							kingMoveMap[Position(enemyKingPosition.x + i, enemyKingPosition.y)] = true;
						}
						else
						{
							kingMoveMap[Position(enemyKingPosition.x + i, enemyKingPosition.y)] = false;
						}
					}
					if (i == 0 and (j == -1 or j == 1))
					{
						if (fields[enemyKingPosition.x + i][enemyKingPosition.y + j].isEmpty()) {
							kingMoveMap[Position(enemyKingPosition.x, enemyKingPosition.y + j)] = true;
						}
						else
						{
							kingMoveMap[Position(enemyKingPosition.x, enemyKingPosition.y + j)] = false;
						}
					}
					if (fields[enemyKingPosition.x + i][enemyKingPosition.y + j].isEmpty() and i != 0 and j != 0) {
						kingMoveMap[Position(enemyKingPosition.x + i, enemyKingPosition.y + j)] = true;
					}
					else
					{
						kingMoveMap[Position(enemyKingPosition.x + i, enemyKingPosition.y + j)] = false;
					}
				}
			}
		}

		int diffX{ x - enemyKingPosition.x };
		int diffY{ y - enemyKingPosition.y };

		int modX{ diffX < 0 ? 1 : -1 };
		int tempX = modX;
		int modY{ diffY < 0 ? 1 : -1 };
		int tempY = modY;

		int n{ diffX < 0 ? -diffX : diffX };

		switch (figureDirection)
		{
		case Figure::Directions::vertical:
			for (int i{ 0 }; i < 1; ++i)
			{
				if (!checkForObstacles(obstacleData) and !isSubscriptOutOfRange(x + modX, y) and kingMoveMap.contains(Position(x + modX, y)))
				{
					kingMoveMap[Position(x + modX, y)] = false;
				}
				modX += tempX;
			}


		case Figure::Directions::horizontalAndVertical:
			for (int i{ 0 }; i < n; ++i)
			{
				if (!checkForObstacles(obstacleData) and !isSubscriptOutOfRange(x + modX, y + modY))
				{
					if (kingMoveMap.contains(Position(x + modX, y)))
					{
						kingMoveMap[Position(x + modX, y)] = false;
					}
					if (kingMoveMap.contains(Position(x, y + modY)))
					{
						kingMoveMap[Position(x, y + modY)] = false;
					}
				}
				modX += tempX;
				modY += tempY;

			}

		case Figure::Directions::diagonal:
			for (int i{ 0 }; i < n; ++i)
			{
				if (!checkForObstacles(obstacleData) and !isSubscriptOutOfRange(x + modX, y + modY) and kingMoveMap.contains(Position(x + modX, y + modY))) {}
				{
					kingMoveMap[Position(x + modX, y + modY)] = false;
				}

				modX += tempX;
				modY += tempY;
			}

		case Figure::Directions::all:
			for (int i{ 0 }; i < n; ++i)
			{
				if (!checkForObstacles(obstacleData) and !isSubscriptOutOfRange(x + modX, y + modY) and kingMoveMap.contains(Position(x + modX, y)))
				{
					kingMoveMap[Position(x + modX, y)] = false;
				}

				if (!checkForObstacles(obstacleData) and !isSubscriptOutOfRange(x + modX, y + modY) and kingMoveMap.contains(Position(x, y + modY)))
				{
					kingMoveMap[Position(x, y + modY)] = false;

				}

				if (!checkForObstacles(obstacleData) and !isSubscriptOutOfRange(x + modX, y + modY) and kingMoveMap.contains(Position(x + modX, y + modY)))
				{
					kingMoveMap[Position(x + modX, y + modY)] = false;

				}

				modX += tempX;
				modY += tempY;
			}

		case Figure::Directions::knight:
				if (x+2<=7 and y+1<=7 and kingMoveMap.contains(Position(x + 2, y + 1)))
				{
					kingMoveMap[Position(x + 2, y + 1)] = false;
				}

				if (x + 2 <= 7 and y - 1 >= 0 and kingMoveMap.contains(Position(x + 2, y - 1)))
				{
					kingMoveMap[Position(x + 2, y - 1)] = false;
				}

				if (x - 2 >=0 and y + 1 <= 7 and kingMoveMap.contains(Position(x - 2, y + 1)))
				{
					kingMoveMap[Position(x - 2, y + 1)] = false;
				}

				if (x - 2 >= 0 and y - 1 >=0 and kingMoveMap.contains(Position(x - 2, y - 1)))
				{
					kingMoveMap[Position(x - 2, y - 1)] = false;
				}

				if (x + 1 <= 7 and y + 2 <= 7 and kingMoveMap.contains(Position(x + 1, y + 2)))
				{
					kingMoveMap[Position(x + 1, y + 2)] = false;
				}

				if (x + 1 <= 7 and y - 2 >=0 and  kingMoveMap.contains(Position(x + 1, y - 2)))
				{
					kingMoveMap[Position(x + 1, y - 2)] = false;
				}

				if (x - 1 >= 0 and y + 2 <= 7 and kingMoveMap.contains(Position(x - 1, y + 2)))
				{
					kingMoveMap[Position(x - 1, y + 2)] = false;
				}

				if (x - 1 >= 0 and y - 2 >= 0 and kingMoveMap.contains(Position(x - 1, y - 2)))
				{
					kingMoveMap[Position(x - 1, y - 2)] = false;
				}
		}
	}

	bool canKingMove()
	{
		std::map <Position, bool>  kingMoveMap = { };

		for (int x{ 0 }; x < 8; ++x)
		{
			for (int y{ 0 }; y < 8; ++y)
			{
				if (!fields[x][y].isEmpty())
				{
					if (Chess::getTurn() and fields[x][y].getFigureColor() == Figure::FigureColor::black)
					{
						checkFieldsNearKing(x, y, kingMoveMap);
					}
					if (!Chess::getTurn() and fields[x][y].getFigureColor() == Figure::FigureColor::white)
					{
						checkFieldsNearKing(x, y, kingMoveMap);
					}
				}
			}
		}

		return std::any_of(kingMoveMap.begin(), kingMoveMap.end(), [](const auto& it) { return it.second; });

	}

	bool isCheckingFigureOnPathOf(int x, int y)
	{
		Figure::Directions figureDirection{fields[x][y].getFigureSchema().direction};

		Position fieldData = Position{ x,y };
		std::pair<Position, Position> obstacleData = std::make_pair(fieldData, checkingFigure);

		int diff{ x - checkingFigure.x };
		int diffY{ y - checkingFigure.y };

		int modX{ diff < 0 ? 1 : -1 };
		int temp = modX;
		int modY{ diffY < 0 ? 1 : -1 };
		int tempY = modY;

		int n{ diff < 0 ? -diff : diff };

		switch (figureDirection)
		{
		case Figure::Directions::vertical:
			for (int i{ 0 }; i < 1; ++i)
			{
				if (!checkForObstacles(obstacleData) and !isSubscriptOutOfRange(x + modX, y) and x + modX == checkingFigure.x and y == checkingFigure.y)
				{
					return true;
				}
				modX += temp;
			}
			return false;


		case Figure::Directions::horizontalAndVertical:
			for (int i{ 0 }; i < n; ++i)
			{
				if (!checkForObstacles(obstacleData) and !isSubscriptOutOfRange(x + modX, y + modY))
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
			for (int i{ 0 }; i < n; ++i)
			{
				if (!checkForObstacles(obstacleData) and !isSubscriptOutOfRange(x + modX, y + modY) and x + modX == checkingFigure.x and x + modY == checkingFigure.y)
				{
					return true;
				}
				modX += temp;
				modY += tempY;
			}
			return false;

		case Figure::Directions::all:
			for (int i{ 0 }; i < n; ++i)
			{
				if (!checkForObstacles(obstacleData) and !isSubscriptOutOfRange(x + modX, y + modY))
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
			if (!isSubscriptOutOfRange(x + 2, y + 2) or !isSubscriptOutOfRange(x + 2, y - 2) or !isSubscriptOutOfRange(x - 2, y + 2) or !isSubscriptOutOfRange(x - 2, y - 2))
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
		}
	}

	bool canKillCheckingFigure()
	{
		for (int x{ 0 }; x < 8; ++x)
		{
			for (int y{ 0 }; y < 8; ++y)
			{
				if (!fields[x][y].isEmpty()) {
					if (Chess::getTurn() and fields[x][y].getFigureColor() == Figure::FigureColor::white)
					{
						return isCheckingFigureOnPathOf(x, y);
					}
					if (!Chess::getTurn() and fields[x][y].getFigureColor() == Figure::FigureColor::black)
					{
						return isCheckingFigureOnPathOf(x, y);
					}
				}
			}
		}
		return false;
	}

	std::vector<Position> getCheckingFigurePath(Position checkingFig)
	{
		std::vector<Position> checkingFigurePath;
		Figure::Directions figureDirection{fields[checkingFig.x][checkingFig.y].getFigureSchema().direction};

		auto kings = getKingPosition();
		const Position& enemyKingPosition = fields[checkingFig.x][checkingFig.y].getFigureColor() == Figure::FigureColor::white ? kings.second : kings.first;

		int diff{ checkingFig.x - enemyKingPosition.x };
		int diffY{ checkingFig.y - enemyKingPosition.y };

		int modX{ diff < 0 ? 1 : -1 };
		int temp = modX;
		int modY{ diffY < 0 ? 1 : -1 };
		int tempY = modY;

		int n{ diff < 0 ? -diff : diff };

		switch (figureDirection)
		{
		case Figure::Directions::vertical:
			for (int i{ 0 }; i < n - 1; ++i)
			{
				if (!isSubscriptOutOfRange(checkingFig.x + modX, checkingFig.y + modX))
				{
					checkingFigurePath.emplace_back(Position(checkingFig.x + modX, checkingFig.y));
				}
				modX += temp;
			}
			return checkingFigurePath;


		case Figure::Directions::horizontalAndVertical:
			for (int i{ 0 }; i < n - 1; ++i)
			{

				if (!isSubscriptOutOfRange(checkingFig.x + modX, checkingFig.y + modY))
				{
					if (diffY == 0)
					{
						checkingFigurePath.emplace_back(Position(checkingFig.x + modX, checkingFig.y));
					}
					if (diff == 0)
					{
						checkingFigurePath.emplace_back(Position(checkingFig.x, checkingFig.y + modY));

					}
				}
				modX += temp;
				modY += tempY;

			}
			return checkingFigurePath;

		case Figure::Directions::diagonal:
			for (int i{ 0 }; i < n - 1; ++i)
			{

				if (!isSubscriptOutOfRange(checkingFig.x + modX, checkingFig.y + modY))
				{
					checkingFigurePath.emplace_back(Position(checkingFig.x + modX, checkingFig.y + modY));

				}
				modX += temp;
				modY += tempY;
			}
			return checkingFigurePath;

		case Figure::Directions::all:
			for (int i{ 0 }; i < n - 1; ++i)
			{
				if (!isSubscriptOutOfRange(checkingFig.x + modX, checkingFig.y + modY))
				{
					if (diffY == 0)
					{
						checkingFigurePath.emplace_back(Position(checkingFig.x + modX, checkingFig.y));
					}
					if (diff == 0)
					{
						checkingFigurePath.emplace_back(Position(checkingFig.x, checkingFig.y + modY));

					}
					if (diff == diffY)
					{
						checkingFigurePath.emplace_back(Position(checkingFig.x + modX, checkingFig.y + modY));

					}
				}
				modX += temp;
				modY += tempY;
			}
			return checkingFigurePath;

		case Figure::Directions::knight:

			return checkingFigurePath;
		}
	}

	bool canBlockPathOfCheckingFigure(int x, int y, Position checkingFig)
	{
		std::vector<Position> checkingFigurePath = getCheckingFigurePath(checkingFig);
		Figure::Directions figureDirection{fields[x][y].getFigureSchema().direction};


		int diffX{ x - checkingFig.x };
		int diffY{ y - checkingFig.y };

		int modX{ diffX < 0 ? 1 : -1 };
		int tempX = modX;
		int modY{ diffY < 0 ? 1 : -1 };
		int tempY = modY;

		int n{ diffX < 0 ? -diffX : diffX };

		switch (figureDirection)
		{
		case Figure::Directions::vertical:
			for (int i{ 0 }; i < n - 1; ++i)
			{
				if (!isSubscriptOutOfRange(checkingFig.x + modX, checkingFig.y) and checkForObstacles(std::make_pair(Position(x, y), checkingFig)))
				{
					if (diffY == 0) {
						for (auto& pathField : checkingFigurePath)
						{
							if (pathField == Position(x + modX, y))
							{
								return true;
							}
						}
					}
					if (diffX == 0)
					{
						for (auto& pathField : checkingFigurePath)
						{
							if (pathField == Position(x, y + modY))
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
			for (int i{ 0 }; i < n - 1; ++i)
			{

				if (!isSubscriptOutOfRange(checkingFig.x + modX, checkingFig.y + modY) and checkForObstacles(std::make_pair(Position(x, y), checkingFig)))
				{
					for (auto& pathField : checkingFigurePath)
					{
						if (pathField == Position(x + modX, y))
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
			for (int i{ 0 }; i < n - 1; ++i)
			{

				if (!isSubscriptOutOfRange(checkingFig.x + modX, checkingFig.y + modY) and checkForObstacles(std::make_pair(Position(x, y), checkingFig)))
				{
					for (auto& pathField : checkingFigurePath)
					{
						if (pathField == Position(x + modX, y + modY))
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
			for (int i{ 0 }; i < n - 1; ++i)
			{
				if (!isSubscriptOutOfRange(checkingFig.x + modX, checkingFig.y + modY) and checkForObstacles(std::make_pair(Position(x, y), checkingFig)))
				{
					if (diffY == 0)
					{
						for (auto& pathField : checkingFigurePath)
						{
							if (pathField == Position(x + modX, y))
							{
								return true;
							}
						}
					}
					if (diffX == 0)
					{
						for (auto& pathField : checkingFigurePath)
						{
							if (pathField == Position(x, y + modY))
							{
								return true;
							}
						}
					}
					if (diffX == diffY)
					{
						for (auto& pathField : checkingFigurePath)
						{
							if (pathField == Position(x + modX, y + modY))
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

			return false;
		}

		return false;
	}

	bool canDefendKing()
	{
		for (int x{ 0 }; x < 8; ++x)
		{
			for (int y{ 0 }; y < 8; ++y)
			{
				if (!fields[x][y].isEmpty())
				{
					if (Chess::getTurn() and fields[x][y].getFigureColor() == Figure::FigureColor::white)
					{
						if (canBlockPathOfCheckingFigure(x, y, checkingFigure))
						{
							return true;
						}
					}
					if (!Chess::getTurn() and fields[x][y].getFigureColor() == Figure::FigureColor::black)
					{
						if (canBlockPathOfCheckingFigure(x, y, checkingFigure))
						{
							return true;
						}
					}
				}
			}
		}
		return false;
	}

	bool isCheckMate()
	{
		if (checkCheck()) {
			if (!canKingMove() and !canKillCheckingFigure() and !canDefendKing())
			{
				std::cout << "checkmate";
				return true;

			}
		}
		return false;
	}

	bool checkMoveDataForNullptr(auto moveData)
	{
		if (fields[moveData.first.x][moveData.first.y].isEmpty() or fields[moveData.second.x][moveData.second.y].isEmpty())
		{
			return true;
		}
		return false;
	}

	void move(auto moveData)
	{
		std::unique_ptr<Figure> tempFigure{};
		if(checkCheck())
		{
			std::cout << "check";
		}

		if (Chess::getTurn() and fields[moveData.first.x][moveData.first.y].getFigureColor() == Figure::FigureColor::white)
		{
			if (checkIfMovePossible(moveData) and !checkForObstacles(moveData))
			{
				tempFigure = fields[moveData.second.x][moveData.second.y].pickFigure();

				fields[moveData.second.x][moveData.second.y].placeFigure(std::move(fields[moveData.first.x][moveData.first.y].pickFigure()));

				if (checkCheck())
				{
					check = true;
				}

				if (!check and fields[moveData.second.x][moveData.second.y].isPawn() and moveData.second.x == 0)
				{
					promote(moveData);
				}

				if (check)
				{
					fields[moveData.first.x][moveData.first.y].placeFigure(std::move(fields[moveData.second.x][moveData.second.y].pickFigure()));
					fields[moveData.second.x][moveData.second.y].placeFigure(std::move(tempFigure));

					Chess::changeTurn();
				}

				enemyKing = getKingPosition();
				Chess::changeTurn();
			}

		}
		else if (!Chess::getTurn() and fields[moveData.first.x][moveData.first.y].getFigureColor() == Figure::FigureColor::black)
		{
			if (checkIfMovePossible(moveData) and !checkForObstacles(moveData))
			{
				tempFigure = fields[moveData.second.x][moveData.second.y].pickFigure();

				fields[moveData.second.x][moveData.second.y].placeFigure(std::move(fields[moveData.first.x][moveData.first.y].pickFigure()));

				if (checkCheck())
				{
					check = true;
				}

				if(!check and fields[moveData.second.x][moveData.second.y].isPawn() and moveData.second.x==7 )
				{
					promote(moveData);
				}



				if (check)
				{
					fields[moveData.first.x][moveData.first.y].placeFigure(std::move(fields[moveData.second.x][moveData.second.y].pickFigure()));
					fields[moveData.second.x][moveData.second.y].placeFigure(std::move(tempFigure));

					Chess::changeTurn();
				}
				enemyKing = getKingPosition();
				Chess::changeTurn();

			}
			else
			{
				std::cout << "wrong move\n" << std::endl;
			}
		}
		else if (Chess::getTurn() and fields[moveData.first.x][moveData.first.y].getFigureColor() == Figure::FigureColor::black or !Chess::getTurn() and fields[moveData.first.x][moveData.first.y].getFigureColor() == Figure::FigureColor::white)
		{
			std::cout << "wrong figure\n";
		}

		if(fields[moveData.second.x][moveData.second.y].isPawn())
		{
			fields[moveData.second.x][moveData.second.y].pawnFirstMoveDone();
		}

	}

	friend std::ostream& operator << (std::ostream& out, const Board& b) {
		out << ' ';
		for (char letter{ 'a' }; letter < 'a' + 8; ++letter)
		{
			out << ' ' << letter << ' ';
		}
		for (int row{ 0 }; row < 8; ++row) {
			out << std::endl;
			out << row + 1;

			for (int col{ 0 }; col < 8; ++col) {
				out << b.fields[row][col];
			}
		}
		return out;
	}

private:
	std::array<std::array<Field, 8>, 8> fields{};
	Position checkingFigure{};
	std::pair<Position, Position> enemyKing{};
	bool check{ false };

};
