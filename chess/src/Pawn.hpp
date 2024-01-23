#pragma once

#include "figure.hpp"

class Pawn : public Figure
{
public:
	Pawn(FigureColor fc) : Figure(Figures::pawn, fc) {}

	void firstMoveDone()
	{
		firstMove = false;
	}

	MoveSchema getMoveSchema() const override
	{
		MoveSchema ms{ Directions::vertical, Length::two, Modifiers::onlyTowardsEnemy };
		ms.length = firstMove ? Length::two : Length::one;

		return ms;
	}



protected:
	bool firstMove{ true };

};

