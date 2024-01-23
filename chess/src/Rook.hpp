#pragma once

#include "figure.hpp"

class Rook : public Figure
{
public:
	Rook(FigureColor fc) : Figure(Figures::rook, fc) {}


	MoveSchema getMoveSchema() const override
	{
		MoveSchema ms{ Directions::horizontalAndVertical, Length::noLimit, Modifiers::none };

		return ms;
	}

private:

};

