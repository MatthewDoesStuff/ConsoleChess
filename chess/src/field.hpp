#pragma once

#include <iostream>

#include "Color.hpp"
#include "Figure.hpp"
#include "Pawn.hpp"

class Field
{
public:
	Field() = default;
	~Field() = default;

	void setColor(Color);

	void setFigure(std::shared_ptr<Figure>);

	Color getFigureColor() const;

	Figure::Figures getFigureFromField() const;

	Figure::MoveSchema getFigureSchema() const;

	bool isEmpty() const;

	bool isKing() const;

	void pawnFirstMoveDone();

	bool isPawn() const;

	std::shared_ptr<Figure> pickFigure();

	void placeFigure(std::shared_ptr<Figure>);

	friend std::ostream& operator <<(std::ostream&, const Field&);

private:
	Color fieldColor;
	std::shared_ptr<Figure> figure;
};
