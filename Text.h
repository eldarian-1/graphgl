#pragma once

#include "Figure.h"

#include "Rect.h"
#include "Ellip.h"

#include <string.h>

extern double defaultWeight;
extern double* defaultColorMain;
extern double* defaultColorAlt;

class Text : public Figure
{
private:
	double cX, cY, dist;
	const char* text;
	double* color;

public:
	Text(const char* t = nullptr, double* c = defaultColorAlt, double x = 0, double y = 0, double d = 10)
		: text(t), color(c), cX(x), cY(y), dist(d) {};

	Text(const char* t, Rect* rect, double* c = nullptr)
		: Text(t, c,
			rect->getCX() + (rect->getWidth() - strlen(t) * 10.0) / 2.0,
			rect->getCY() + (rect->getHeight() - 10.0) / 2.0 + 10.0
		) {};

	Text(const char* t, Ellip* ellipse, double* c = nullptr)
		: Text(t, c,
			ellipse->getCX() - ellipse->getRA() + (ellipse->getRA() * 2.0 - strlen(t) * 10.0) / 2.0,
			ellipse->getCY() - ellipse->getRB() + (ellipse->getRB() * 2.0 - 10.0) / 2.0 + 10
		) {};

	void set(const char* t, Ellip* ellipse, double* c = defaultColorAlt);

	int length() { return strlen(this->text); }
	const char* getText() { return this->text; }

	void draw();
	bool isFocused(int x, int y);

};
