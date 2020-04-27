#pragma once

#include "Figure.h"

extern double defaultWeight;
extern double* defaultColorMain;
extern double* defaultColorFocus;
extern double* defaultColorAlt;

class Ellip : public Figure
{
private:
	friend class Arrow;

	double cX, cY, rA, rB, weight;
	double* colorMain, * colorBorder, * colorFocus;
	bool isFocus;

public:
	Ellip() : cX(0), cY(0), rA(0), rB(0), weight(defaultWeight), colorMain(defaultColorMain), colorFocus(defaultColorFocus), colorBorder(defaultColorAlt), isFocus(false) {};
	Ellip(double x, double y, double r) : cX(x), cY(y), rA(r), rB(r), weight(defaultWeight), colorMain(defaultColorMain), colorFocus(defaultColorFocus), colorBorder(defaultColorAlt), isFocus(false) {};
	Ellip(double x, double y, double a, double b) : cX(x), cY(y), rA(a), rB(b), weight(defaultWeight), colorMain(defaultColorMain), colorFocus(defaultColorFocus), colorBorder(defaultColorAlt), isFocus(false) {};

	double getCX() { return this->cX; }
	double getCY() { return this->cY; }
	double getRA() { return this->rA; }
	double getRB() { return this->rB; }

	void setCoords(double x, double y, double r);
	void setCoords(double x, double y, double a, double b);

	void draw();
	bool isFocused(int x, int y);

};

void drawEllipse(double* color, double cX, double cY, double rA, double rB);