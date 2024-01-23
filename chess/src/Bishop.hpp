#pragma once

#include "figure.hpp"

class Bishop : public Figure
{
public:
	Bishop(FigureColor fc) : Figure(Figures::bishop,fc) {}


	MoveSchema getMoveSchema() const override
	{
		MoveSchema ms{ Directions::diagonal, Length::noLimit, Modifiers::none };

		return ms;
	}

private:

};

