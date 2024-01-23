#pragma once

#include <iostream>
#include "figure.hpp"
#include "Pawn.hpp"

class Field {
public:
	enum class Color {
		white,
		black
	};

	Field() = default;

	void setColor(Color c)
	{
		fieldColor = c;
	}

	void setFigure(std::unique_ptr<Figure> fi)
	{
		figure = std::move(fi);
	}

	Figure::FigureColor getFigureColor()
	{
		return figure->getColor();
	}

	Figure::Figures getFigureFromField()
	{
		return figure->getFigure();
	}

	Figure::MoveSchema getFigureSchema()
	{
		return figure->getMoveSchema();
	}

	bool isEmpty()
	{
		return !figure;
	}

	bool isKing()
	{
		if(!isEmpty() and figure->getFigure() == Figure::Figures::king)
		{
			return true;
		}
		return false;
	}

	void pawnFirstMoveDone()
	{
		dynamic_cast<Pawn*>(figure.get())->firstMoveDone();

	}

	bool isPawn()
	{
		if(!isEmpty() and figure->getFigure()==Figure::Figures::pawn)
		{
			return true;
		}
		return false;
	}

	friend std::ostream& operator << (std::ostream& out, const Field& fie) {
		if (fie.fieldColor == Field::Color::white)
		{
			out << "\x1b[0;47m" << ' ';
			if (fie.figure)
			{
				if (fie.figure->getColor() == Figure::FigureColor::white) {
					out << "\x1b[32m" << *fie.figure << ' ' << "\x1b[0;47m"; 
				}
				else if (fie.figure->getColor() == Figure::FigureColor::black)
				{
					out << "\x1b[31m" << *fie.figure << ' ' << "\x1b[0;47m";
				}
			}
			else
			{
				out << ' ' << ' ';
			}
		}
		else if (fie.fieldColor == Field::Color::black)
		{
			out << "\x1b[0;40m" << ' ';
			if (fie.figure)
			{
				if (fie.figure->getColor() == Figure::FigureColor::white) {
					out << "\x1b[32m" << *fie.figure << ' ' << "\x1b[0;40m";
				}
				else if (fie.figure->getColor() == Figure::FigureColor::black)
				{
					out << "\x1b[31m" << *fie.figure << ' ' << "\x1b[0;40m";
				}
			}
			else
			{
				out << ' ' << ' ';
			}
		}
		out << "\x1b[0;0m";
		return out;
	}

	std::unique_ptr<Figure> pickFigure()
	{
		return std::move(figure);
	}

	void placeFigure(std::unique_ptr<Figure> pf)
	{
		figure = std::move(pf);
	}

private:
	Color fieldColor;
	std::unique_ptr<Figure> figure;
};
