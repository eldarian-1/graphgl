#include "Ellip.h"

#include <glut.h>
#include <math.h>
#include "AppFunc.h"

void Ellip::setCoords(double x, double y)
{
	this->cX = x;
	this->cY = y;
}

void Ellip::setCoords(double x, double y, double r)
{
	this->cX = x;
	this->cY = y;
	this->rA = r;
	this->rB = r;
}

void Ellip::setCoords(double x, double y, double a, double b)
{
	this->cX = x;
	this->cY = y;
	this->rA = a;
	this->rB = b;
}

void Ellip::draw()
{
	if (this->weight != 0)
		drawEllipse(this->colorBorder, this->cX, this->cY, this->rA, this->rB);

	if (isFocus)
		drawEllipse(this->colorFocus, this->cX, this->cY, this->rA - this->weight, this->rB - this->weight);
	else
		drawEllipse(this->colorMain, this->cX, this->cY, this->rA - this->weight, this->rB - this->weight);
}

bool Ellip::isFocused(int x, int y)
{
	this->isFocus = ((pow(this->cX - x, 2.0) / pow(this->rA, 2.0) + pow(this->cY - y, 2.0) / pow(this->rB, 2.0)) <= 1.0);
	return this->isFocus;
}

void drawEllipse(double* color, double cX, double cY, double rA, double rB)
{
	double step = M_PI / 180.0;

	glBegin(GL_TRIANGLE_FAN);
	glColor3dv(color);
	glVertex2d(cX, cY);
	for (double angle = 0.0; angle <= 2.0 * M_PI; angle += step)
	{
		double t = (fabs(angle - 2 * M_PI) < 0.00001) ? 0.0 : angle;
		double dx = rA * cos(t);
		double dy = rB * sin(t);
		glVertex2d(dx + cX, dy + cY);
	}
	glEnd();
}