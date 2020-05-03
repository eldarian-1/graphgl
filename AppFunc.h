#pragma once

static const double M_PI = 3.14159265358979323846;
static const int APP_WIDTH = 1280;
static const int APP_HEIGHT = 720;
static const int APP_SHIFT = 15;

char* myitoa(int number, char* destination, int base);

int fibonachi(int num);

double squareTriangle(double x0, double y0, double x1, double y1, double x2, double y2);