#pragma once

#include <iostream>
#include <map>

#include "Color.hpp"

class Figure
{
public:
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


	enum class Figures
	{
		pawn,
		rook,
		knight,
		bishop,
		queen,
		king
	};

	std::map<Figures, char> Figure_To_Char = {
		{Figures::pawn, 'P'},
		{Figures::rook, 'R'},
		{Figures::knight, 'N'},
		{Figures::bishop, 'B'},
		{Figures::queen, 'Q'},
		{Figures::king, 'K'}
	};

	Figure() = default;
	virtual ~Figure() = default;

	Figure(Figures fn, Color fc) : figureN(fn), figureColor(fc)
	{
	}

	void setFigureColor(Color fc)
	{
		figureColor = fc;
	}

	Color getColor() const
	{
		return figureColor;
	}

	Figures getFigure() const
	{
		return figureN;
	}

	virtual MoveSchema getMoveSchema() const = 0;

	friend std::ostream& operator <<(std::ostream& out, const Figure& fig)
	{
		out << fig.Figure_To_Char.at(fig.figureN);
		return out;
	}

private:
	Figures figureN;
	Color figureColor;
};
