#pragma once

#include "Figure.hpp"
#include "Color.hpp"

class Queen : public Figure
{
public:
	Queen(Color fc) : Figure(Figures::queen, fc)
	{
	}


	MoveSchema getMoveSchema() const override
	{
		return ms;
	}

private:
	MoveSchema ms{Directions::all, Length::noLimit, Modifiers::none};
};
