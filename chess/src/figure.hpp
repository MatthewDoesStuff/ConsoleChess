#pragma once

#include <iostream>
#include <map>

class Figure {
public:

	enum class Directions
	{
		horizontal,
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

	}; MoveSchema moveSchema;

	enum class Figures {
		pawn,
		rook,
		knight,
		bishop,
		queen,
		king
	};

	const std::map<Figures, char> Figure_To_Char = {
		{Figures::pawn, 'P'},
		{Figures::rook, 'R'},
		{Figures::knight, 'N'},
		{Figures::bishop, 'B'},
		{Figures::queen, 'Q'},
		{Figures::king, 'K'}
	};

	enum class FigureColor {
		white,
		black
	};

	const std::map<FigureColor, char> FigureColor_to_char = {
		{FigureColor::white, 'w'},
		{FigureColor::black, 'b'}
	};

	Figure() = default;
	Figure(Figures fn, FigureColor fc) : figureN(fn), figureColor(fc) { }

	void setFigureColor(FigureColor fc)
	{
		figureColor = fc;
	}

	FigureColor	getColor()
	{
		return figureColor;
	}

	Figures getFigure()
	{
		return figureN;
	}

	virtual MoveSchema getMoveSchema() const = 0;

	friend std::ostream& operator << (std::ostream& out, const Figure& fig)
	{
		out << fig.Figure_To_Char.at(fig.figureN);
		return out;
	}

private:
	Figures figureN;
	FigureColor figureColor;

};
