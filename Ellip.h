#pragma once

#include "Figure.h"

#include <string.h>

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
	Ellip()
		: cX(0), cY(0), rA(0), rB(0), weight(defaultWeight), colorMain(defaultColorMain), colorFocus(defaultColorFocus), colorBorder(defaultColorAlt), isFocus(false) {};

	Ellip(double x, double y, const char* text, double dop = 10, double w = defaultWeight, double* cM = defaultColorMain, double* cB = defaultColorAlt, double* cF = defaultColorFocus)
		: cX(x), cY(y), rA(strlen(text) * 5 + dop), rB(20), weight(w), colorMain(cM), colorFocus(cF), colorBorder(cB), isFocus(false) {};

	Ellip(double x, double y, double r, double w = defaultWeight, double* cM = defaultColorMain, double* cB = defaultColorAlt, double* cF = defaultColorFocus)
		: cX(x), cY(y), rA(r), rB(r), weight(w), colorMain(cM), colorFocus(cF), colorBorder(cB), isFocus(false) {};

	Ellip(double x, double y, double a, double b, double w = defaultWeight, double* cM = defaultColorMain, double* cB = defaultColorAlt, double* cF = defaultColorFocus)
		: cX(x), cY(y), rA(a), rB(b), weight(w), colorMain(cM), colorFocus(cF), colorBorder(cB), isFocus(false) {};

	double getCX() { return this->cX; }
	double getCY() { return this->cY; }
	double getRA() { return this->rA; }
	double getRB() { return this->rB; }

	void setCoords(double x, double y);
	void setCoords(double x, double y, double r);
	void setCoords(double x, double y, double a, double b);

	void set(double x, double y, const char* text, double dop = 10, double w = defaultWeight, double* cM = defaultColorMain, double* cB = defaultColorAlt, double* cF = defaultColorFocus);
	void setCircle() { this->rB = this->rA; }

	void updEllip(const char*, double = 10);

	void draw();
	bool isFocused(int x, int y);

};

void drawEllipse(double* color, double cX, double cY, double rA, double rB);