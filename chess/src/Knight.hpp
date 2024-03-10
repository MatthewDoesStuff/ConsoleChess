#pragma once

#include "Figure.hpp"
#include "Color.hpp"

class Knight : public Figure
{
public:
	Knight(Color);

	MoveSchema getMoveSchema() const override;

private:
	MoveSchema ms{Directions::knight, Length::knight, Modifiers::none};
};
