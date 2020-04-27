#pragma once

static const double M_PI = 3.14159265358979323846;
static const int APP_WIDTH = 1280;
static const int APP_HEIGHT = 720;
static const int APP_SHIFT = 15;

struct Control
{
	int sX, sY, fX, fY;
	const char* text;
	void (*func)();
};

char* myitoa(int number, char* destination, int base);

int fibonachi(int num);