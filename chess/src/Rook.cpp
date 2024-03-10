#include "Rook.hpp"

Rook::Rook(Color fc) : Figure(Figures::rook, fc)
{
}

Rook::MoveSchema Rook::getMoveSchema() const
{
	return ms;
}
