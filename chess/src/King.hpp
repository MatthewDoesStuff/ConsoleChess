#pragma once

#include "figure.hpp"

class King : public Figure
{
public:
	King(FigureColor fc) : Figure(Figures::king, fc) {}


	MoveSchema getMoveSchema() const override
	{
		MoveSchema ms{ Directions::all, Length::one, Modifiers::king };

		return ms;
	}

private:
};

