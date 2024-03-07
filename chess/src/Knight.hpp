#pragma once

#include "Figure.hpp"
#include "Color.hpp"

class Knight : public Figure
{
public:
	Knight(Color fc) : Figure(Figures::knight, fc)
	{
	}


	MoveSchema getMoveSchema() const override
	{
		return ms;
	}

private:
	MoveSchema ms{Directions::knight, Length::knight, Modifiers::none};
};
