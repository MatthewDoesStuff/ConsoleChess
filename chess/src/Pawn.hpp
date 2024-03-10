#pragma once

#include "Figure.hpp"
#include "Color.hpp"

class Pawn : public Figure
{
public:
	Pawn(Color);

	void firstMoveDone();

	MoveSchema getMoveSchema() const override;

protected:
	bool firstMove{true};
};
