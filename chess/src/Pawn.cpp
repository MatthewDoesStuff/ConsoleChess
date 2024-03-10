#include "Pawn.hpp"

Pawn::Pawn(Color fc) : Figure(Figures::pawn, fc)
{
}

void Pawn::firstMoveDone()
{
	firstMove = false;
}

Pawn::MoveSchema Pawn::getMoveSchema() const
{
	MoveSchema ms{Directions::vertical, Length::two, Modifiers::onlyTowardsEnemy};
	ms.length = firstMove ? Length::two : Length::one;

	return ms;
}
