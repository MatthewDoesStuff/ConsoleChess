#include "Knight.hpp"

Knight::Knight(Color fc) : Figure(Figures::knight, fc)
{
}

Knight::MoveSchema Knight::getMoveSchema() const
{
	return ms;
}
