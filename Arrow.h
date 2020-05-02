#pragma once

#include "Figure.h"

#include "AppFunc.h"
#include "Ellip.h"

extern const double M_PI;

class Arrow : public Figure
{
private:
	double sX, sY, fX, fY, weight;
	double* color;
	double angle, length;
	bool isEllip;

public:
	Arrow(Ellip* start, Ellip* finish, bool isEl = false, double weight = 1.0, double angle = M_PI / 6.0, double length = 10.0, double* color = defaultColorAlt);

	Arrow(Ellip* start, int x, int y, double weight = 1.0, double angle = M_PI / 6.0, double length = 20.0, double* color = defaultColorAlt);

	void draw();
	bool isFocused(int, int);

};

