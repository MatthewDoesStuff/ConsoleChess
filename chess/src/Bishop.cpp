#include "Bishop.hpp"

Bishop::Bishop(Color fc) : Figure(Figures::bishop, fc)
{
}

Bishop::MoveSchema Bishop::getMoveSchema() const
{
	return ms;
}
