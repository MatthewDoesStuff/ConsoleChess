#pragma once

#include "Figure.hpp"
#include "Color.hpp"

class Rook : public Figure
{
public:
	Rook(Color fc) : Figure(Figures::rook, fc)
	{
	}


	MoveSchema getMoveSchema() const override
	{
		return ms;
	}

private:
	MoveSchema ms{Directions::horizontalAndVertical, Length::noLimit, Modifiers::none};
};
