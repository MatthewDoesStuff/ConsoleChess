#include "Figure.hpp"

namespace
{
	std::map<Figure::Figures, char> figureToChar = {
		{Figure::Figures::pawn, 'P'},
		{Figure::Figures::rook, 'R'},
		{Figure::Figures::knight, 'N'},
		{Figure::Figures::bishop, 'B'},
		{Figure::Figures::queen, 'Q'},
		{Figure::Figures::king, 'K'}
	};
}

Figure::Figure(Figures fn, Color fc) : figureN(fn), figureColor(fc)
{
}

Figure::~Figure() = default;

void Figure::setFigureColor(Color fc)
{
	figureColor = fc;
}

Color Figure::getColor() const
{
	return figureColor;
}

Figure::Figures Figure::getFigure() const
{
	return figureN;
}

std::ostream& operator <<(std::ostream& out, const Figure& fig)
{
	out << figureToChar.at(fig.figureN);
	return out;
}
