#pragma once

#include "Figure.hpp"
#include "Color.hpp"

class King : public Figure
{
public:
	King(Color);

	MoveSchema getMoveSchema() const override;

private:
	MoveSchema ms{Directions::all, Length::one, Modifiers::king};
};
