#include "AppFunc.h"

#include <math.h>

char* myitoa(int number, char* destination, int base)
{
	int count = 0;
	do
	{
		int digit = number % base;
		destination[count++] = (digit > 9) ? digit - 10 + 'A' : digit + '0';
	}
	while ((number /= base) != 0);
	destination[count] = '\0';
	int i;
	for (i = 0; i < count / 2; ++i)
	{
		char symbol = destination[i];
		destination[i] = destination[count - i - 1];
		destination[count - i - 1] = symbol;
	}
	return destination;
}

int fibonachi(int num)
{
	if (num <= 1)
		return 1;
	return num + fibonachi(num - 1);
}

double squareTriangle(double x0, double y0, double x1, double y1, double x2, double y2)
{
	double len0 = pow(pow(x0 - x1, 2) + pow(y0 - y1, 2), 0.5);
	double len1 = pow(pow(x0 - x2, 2) + pow(y0 - y2, 2), 0.5);
	double cs = (x1 + x2 - 2 * x0 + y1 + y2 - 2 * y0)/(len0 * len1);
	return fabs(0.5 * len0 * len1 * sin(acos(cs)));
}