#pragma once

#include "Figure.h"

#include "AppFunc.h"
#include "Ellip.h"

extern const double M_PI;

class Arrow : public Figure
{
private:
	double sX, sY, fX, fY;
	double angle, length, weight;
	double* color;
	bool isEllip;

public:
	Arrow(Ellip* start, Ellip* finish, bool isEl = false, double weight = 1.0, double angle = M_PI / 6.0, double length = 20.0, double* color = defaultColorAlt);

	Arrow(Ellip* start, int x, int y, double weight = 1.0, double angle = M_PI / 6.0, double length = 20.0, double* color = defaultColorAlt);

	void setEllip(bool isE) { this->isEllip = isE; }

	double getSX() { return this->sX; }
	double getSY() { return this->sY; }
	double getFX() { return this->fX; }
	double getFY() { return this->fY; }

	void draw();
	bool isFocused(int, int);

};

