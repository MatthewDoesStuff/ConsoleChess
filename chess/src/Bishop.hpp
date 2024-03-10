#pragma once

#include "Figure.hpp"
#include "Color.hpp"

class Bishop : public Figure
{
public:
	Bishop(Color);

	MoveSchema getMoveSchema() const override;

private:
	MoveSchema ms{Directions::diagonal, Length::noLimit, Modifiers::none};
};
