#include "Field.hpp"

void Field::setColor(Color c)
{
	fieldColor = c;
}

void Field::setFigure(std::shared_ptr<Figure> fi)
{
	figure = std::move(fi);
}

Color Field::getFigureColor() const
{
	return figure->getColor();
}

Figure::Figures Field::getFigureFromField() const
{
	return figure->getFigure();
}

Figure::MoveSchema Field::getFigureSchema() const
{
	return figure->getMoveSchema();
}

bool Field::isEmpty() const
{
	return figure == nullptr;
}

bool Field::isKing() const
{
	return !isEmpty() and figure->getFigure() == Figure::Figures::king;
}

void Field::pawnFirstMoveDone()
{
	dynamic_cast<Pawn*>(figure.get())->firstMoveDone();
}

bool Field::isPawn() const
{
	return !isEmpty() and figure->getFigure() == Figure::Figures::pawn;
}

std::shared_ptr<Figure> Field::pickFigure()
{
	return std::move(figure);
}

void Field::placeFigure(std::shared_ptr<Figure> pf)
{
	figure = std::move(pf);
}

std::ostream& operator <<(std::ostream& out, const Field& fie)
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
