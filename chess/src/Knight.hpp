#pragma once

#include "figure.hpp"

class Knight : public Figure
{
public:
	Knight(FigureColor fc) : Figure(Figures::knight,fc) {}


	MoveSchema getMoveSchema() const override
	{
		MoveSchema ms{ Directions::knight, Length::knight, Modifiers::none };

		return ms;
	}

private:

};

