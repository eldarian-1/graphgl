#pragma once

#include "Figure.h"

extern double defaultWeight;
extern double* defaultColorMain;
extern double* defaultColorAlt;

class Line : public Figure
{
protected:
	double sX, sY, fX, fY, weight;
	double* color;

public:
	Line(double x0, double y0, double x1, double y1, double w = 0, double* c = nullptr)
		: sX(x0), sY(y0), fX(x1), fY(y1), weight((w) ? w : defaultWeight), color((c) ? c : defaultColorAlt) {};

	virtual void draw();
	bool isFocused(int, int);

};
