#pragma once

#include "Figure.hpp"
#include "Color.hpp"

class King : public Figure
{
public:
	King(Color fc) : Figure(Figures::king, fc)
	{
	}


	MoveSchema getMoveSchema() const override
	{
		return ms;
	}

private:
	MoveSchema ms{Directions::all, Length::one, Modifiers::king};
};
