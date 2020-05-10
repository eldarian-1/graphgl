#pragma once

class Figure
{
public:
	virtual void draw() = 0;
	virtual bool isFocused(int, int) = 0;
};

static double defaultWeight = 1.0;

static double* defaultColorMain = new double[3]{ 0.95, 0.98, 1 };

static double* defaultColorFocus = new double[3]{ 0.95, 1, 0.94 };

static double* defaultColorAlt = new double[3]{ 0.0, 0.1, 0.15 };

static double* defaultColorArrowMain = new double[3]{ 0.0, 0.35, 0.4 };

static double* defaultColorArrowFocus = new double[3]{ 0.5, 0.0, 0.35 };