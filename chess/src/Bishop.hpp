#pragma once

#include "Figure.hpp"
#include "Color.hpp"

class Bishop : public Figure
{
public:
	Bishop(Color fc) : Figure(Figures::bishop, fc)
	{
	}


	MoveSchema getMoveSchema() const override
	{
		return ms;
	}

private:
	MoveSchema ms{Directions::diagonal, Length::noLimit, Modifiers::none};
};
