#pragma once

#include <iostream>
#include <map>

#include "Color.hpp"

class Figure
{
public:
	enum class Figures
	{
		pawn,
		rook,
		knight,
		bishop,
		queen,
		king
	};

	enum class Directions
	{
		vertical,
		diagonal,
		horizontalAndVertical,
		all,
		knight,
		pawn
	};

	enum class Length
	{
		noLimit,
		one,
		two,
		knight
	};

	enum class Modifiers
	{
		onlyTowardsEnemy,
		none,
		king
	};

	struct MoveSchema
	{
		Directions direction;
		Length length;
		Modifiers modifier;
	};

	//std::map<Figures, char> figureToChar;

	Figure(Figures, Color);
	virtual ~Figure();

	void setFigureColor(Color);

	Color getColor() const;

	Figures getFigure() const;

	virtual MoveSchema getMoveSchema() const = 0;

	friend std::ostream& operator <<(std::ostream&, const Figure&);

private:
	Figures figureN;
	Color figureColor;
};
