#pragma once

#include <iostream>

#include "Color.hpp"
#include "Figure.hpp"
#include "Pawn.hpp"

class Field
{
public:
	Field() = default;

	void setColor(Color c)
	{
		fieldColor = c;
	}

	void setFigure(std::shared_ptr<Figure> fi)
	{
		figure = std::move(fi);
	}

	Color getFigureColor() const
	{
		return figure->getColor();
	}

	Figure::Figures getFigureFromField() const
	{
		return figure->getFigure();
	}

	Figure::MoveSchema getFigureSchema() const
	{
		return figure->getMoveSchema();
	}

	bool isEmpty() const
	{
		return !figure;
	}

	bool isKing() const
	{
		return !isEmpty() and figure->getFigure() == Figure::Figures::king;
	}

	void pawnFirstMoveDone()
	{
		dynamic_cast<Pawn*>(figure.get())->firstMoveDone();
	}

	bool isPawn() const
	{
		return !isEmpty() and figure->getFigure() == Figure::Figures::pawn;
	}

	friend std::ostream& operator <<(std::ostream& out, const Field& fie)
	{
		if (fie.fieldColor == Color::white)
		{
			out << "\x1b[0;47m" << ' ';
			if (fie.figure)
			{
				if (fie.figure->getColor() == Color::white)
				{
					out << "\x1b[32m" << *fie.figure << ' ' << "\x1b[0;47m";
				}
				else if (fie.figure->getColor() == Color::black)
				{
					out << "\x1b[31m" << *fie.figure << ' ' << "\x1b[0;47m";
				}
			}
			else
			{
				out << ' ' << ' ';
			}
		}
		else if (fie.fieldColor == Color::black)
		{
			out << "\x1b[0;40m" << ' ';
			if (fie.figure)
			{
				if (fie.figure->getColor() == Color::white)
				{
					out << "\x1b[32m" << *fie.figure << ' ' << "\x1b[0;40m";
				}
				else if (fie.figure->getColor() == Color::black)
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

	std::shared_ptr<Figure> pickFigure()
	{
		return std::move(figure);
	}

	void placeFigure(std::shared_ptr<Figure> pf)
	{
		figure = std::move(pf);
	}

private:
	Color fieldColor;
	std::shared_ptr<Figure> figure;
};
