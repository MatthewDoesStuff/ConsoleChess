#include "Queen.hpp"

Queen::Queen(Color fc) : Figure(Figures::queen, fc)
{
}

Queen::MoveSchema Queen::getMoveSchema() const
{
	return ms;
}
