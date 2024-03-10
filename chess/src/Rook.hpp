#pragma once

#include "Figure.hpp"
#include "Color.hpp"

class Rook : public Figure
{
public:
	Rook(Color);

	MoveSchema getMoveSchema() const override;

private:
	MoveSchema ms{Directions::horizontalAndVertical, Length::noLimit, Modifiers::none};
};
