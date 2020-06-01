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
	bool isFocus;
	bool isEllip;

public:
	Arrow(Ellip* start, Ellip* finish, bool isF = false, bool isEl = false, double weight = 1.0, double angle = M_PI / 6.0, double length = 20.0, double* color = defaultColorAlt);

	Arrow(Ellip* start, int x, int y, double weight = 1.0, double angle = M_PI / 6.0, double length = 20.0, double* color = defaultColorAlt);

	void setEllip(bool isE) { this->isEllip = isE; }

	void setFocus(bool isF) { this->isFocus = isF; }

	void setArrow(double weight = 1.0, double* color = defaultColorAlt);

	double getSX() { return this->sX; }
	double getSY() { return this->sY; }
	double getFX() { return this->fX; }
	double getFY() { return this->fY; }

	bool getFocus() { return this->isFocus; }

	void setXYforEllip(double* x, double *y, int length);

	void draw();
	bool isFocused(int, int);

};

