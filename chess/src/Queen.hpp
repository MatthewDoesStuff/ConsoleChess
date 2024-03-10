#pragma once

#include "Figure.hpp"
#include "Color.hpp"

class Queen : public Figure
{
public:
	Queen(Color);

	MoveSchema getMoveSchema() const override;

private:
	MoveSchema ms{Directions::all, Length::noLimit, Modifiers::none};
};
