#include "King.hpp"

King::King(Color fc) : Figure(Figures::king, fc)
{
}

King::MoveSchema King::getMoveSchema() const
{
	return ms;
}
