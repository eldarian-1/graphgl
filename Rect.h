#pragma once

#include "Figure.h"

extern double defaultWeight;
extern double* defaultColorMain;
extern double* defaultColorFocus;
extern double* defaultColorAlt;

class Rect : public Figure
{
private:
	double cX, cY, width, height, weight;
	double *colorMain, * colorFocus, * colorBorder;
	bool isFocus;

public:
	Rect(double x, double y, double w, double h)
		: cX(x), cY(y), width(w), height(h), weight(defaultWeight), colorMain(defaultColorMain), colorFocus(defaultColorFocus), colorBorder(defaultColorAlt), isFocus(false) {};

	double getCX() { return this->cX; }
	double getCY() { return this->cY; }
	double getWidth() { return this->width; }
	double getHeight() { return this->height; }

	void draw();
	bool isFocused(int x, int y);

};