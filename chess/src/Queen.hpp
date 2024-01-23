#pragma once

#include "figure.hpp"

class Queen : public Figure
{
public:
	Queen(FigureColor fc) : Figure(Figures::queen, fc) {}


	MoveSchema getMoveSchema() const override
	{
		MoveSchema ms{ Directions::all, Length::noLimit, Modifiers::none };

		return ms;
	}

private:

};

