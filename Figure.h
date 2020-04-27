#pragma once

class Figure
{
public:
	virtual void draw() = 0;
	virtual bool isFocused(int, int) = 0;
};

static double defaultWeight = 1.0;

static double* defaultColorMain = new double[3]{ 0.9, 0.9, 0.9 };

static double* defaultColorFocus = new double[3]{ 0.9, 1.0, 1.0 };

static double* defaultColorAlt = new double[3]{ 0.0, 0.0, 0.0 };