#include "Arrow.h"

#include <glut.h>
#include <math.h>

Arrow::Arrow(Ellip* start, Ellip* finish, bool isF, bool isEl, double weight, double angle, double length, double* color)
	:weight(weight), angle(angle), length(length), color(color), isFocus(isF), isEllip(isEl)
{
	double len = pow(pow(finish->cX - start->cX, 2.0) + pow(finish->cY - start->cY, 2.0), 0.5);
	double cos = (finish->cX - start->cX) / len;
	double sin = (finish->cY - start->cY) / len;
	this->sX = start->cX + cos * (start->rA + ((isEl) ? 0 : 10));
	this->sY = start->cY + sin * (start->rB + ((isEl) ? 0 : 10));
	this->fX = finish->cX - cos * (finish->rA + ((isEl) ? 0 : 25));
	this->fY = finish->cY - sin * (finish->rB + ((isEl) ? 0 : 25));
}

Arrow::Arrow(Ellip* start, int x, int y, double weight, double angle, double length, double* color)
	:weight(weight), angle(angle), length(length), color(color), isFocus(false), isEllip(false)
{
	double len = pow(pow(x - start->cX, 2.0) + pow(y - start->cY, 2.0), 0.5);
	double cos = (x - start->cX) / len;
	double sin = (y - start->cY) / len;
	this->sX = start->cX + cos * start->rA;
	this->sY = start->cY + sin * start->rB;
	this->fX = x - cos * this->length;
	this->fY = y - sin * this->length;
}

void Arrow::setArrow(double weight, double* color)
{
	this->weight = weight;
	this->color = color;
}

void Arrow::setXYforEllip(double* x, double* y, int length)
{
	double len = pow(pow(fX - sX, 2.0) + pow(fY - sY, 2.0), 0.5);
	double cs = (fX - sX) / len;
	double sn = (fY - sY) / len;

	double t0 = (cs < 0) ? -1.0 : 1.0;
	double t1 = (sn < 0) ? -1.0 : 1.0;

	cs = fabs(cs);
	sn = fabs(sn);

	char buffer[20];
	myitoa(length, buffer, 10);
	int str = strlen(buffer);

	if (this->isEllip)
	{
		double step = M_PI / 180;

		double rA = len / 2.0;
		double rB = 20.0;

		double X0 = this->sX + rA * cs * t0;
		double Y0 = this->sY + rA * sn * t1;

		for (double angle = 0; angle <= M_PI; angle += step)
		{
			double X = rA * cos(angle);
			double Y = rB * sin(angle);

			double nX = X * t0 * cs - Y * t1 * sn;
			double nY = X * t1 * sn + Y * t0 * cs;

			double nnX = X0 - nX;
			double nnY = Y0 - nY;

			double fl = pow(pow(this->fX - nnX, 2) + pow(this->fY - nnY, 2), 0.5);

			if (fl <= str*5 + 45)
			{
				*x = nnX;
				*y = nnY;
				break;
			}
		}
	}
	else
	{
		*x = this->sX + cs * t0 * (len - 45);
		*y = this->sY + sn * t1 * (len - 45);
	}
}

void Arrow::draw()
{
	double len = pow(pow(fX - sX, 2.0) + pow(fY - sY, 2.0), 0.5);
	double cs = (fX - sX) / len;
	double sn = (fY - sY) / len;

	double t0 = (cs < 0) ? -1.0 : 1.0;
	double t1 = (sn < 0) ? -1.0 : 1.0;

	double x1, x2, x3, y1, y2, y3;

	cs = fabs(cs);
	sn = fabs(sn);

	if (this->isEllip)
	{
		double step = M_PI / 180;

		double rA = len / 2.0;
		double rB = 20.0;

		double X0 = this->sX + rA * cs * t0;
		double Y0 = this->sY + rA * sn * t1;

		if (this->isFocus)
			glLineWidth(3);
		else
			glLineWidth(this->weight);

		glBegin(GL_LINE_STRIP);

		if(this->isFocus)
			glColor3dv(defaultColorArrowFocus);
		else
			glColor3dv(this->color);

		for (double angle = 0; angle <= M_PI; angle += step)
		{
			double X = rA * cos(angle);
			double Y = rB * sin(angle);

			double nX = X * t0 * cs - Y * t1 * sn;
			double nY = X * t1 * sn + Y * t0 * cs;

			double nnX = X0 - nX;
			double nnY = Y0 - nY;

			double sl = pow(this->sX - nnX, 2) + pow(this->sY - nnY, 2);
			double fl = pow(this->fX - nnX, 2) + pow(this->fY - nnY, 2);

			if (sl <= 100)
				continue;
			else if (fl <= 900)
			{
				this->fX = nnX;
				this->fY = nnY;
				break;
			}

			glVertex2d(nnX, nnY);
		}
		glVertex2d(this->fX, this->fY);
		glEnd();
	}
	else
	{
		glLineWidth((float)this->weight);
		glBegin(GL_LINES);
		
		if (this->isFocus)
			glColor3dv(defaultColorArrowFocus);
		else
			glColor3dv(defaultColorArrowMain);

		glVertex2d(this->sX, this->sY);
		glVertex2d(this->fX, this->fY);
		glEnd();
	}

	x1 = this->fX + t0 * this->length * (cs * 0.666 + cos(acos(cs) - this->angle / 2.0 + M_PI));
	y1 = this->fY + t1 * this->length * (sn * 0.666 + sin(acos(cs) - this->angle / 2.0 + M_PI));

	x2 = this->fX + t0 * this->length * (cs * 0.666 + cos(acos(cs) + this->angle / 2.0 + M_PI));
	y2 = this->fY + t1 * this->length * (sn * 0.666 + sin(acos(cs) + this->angle / 2.0 + M_PI));

	x3 = this->fX + t0 * cs * this->length;
	y3 = this->fY + t1 * sn * this->length;

	glBegin(GL_TRIANGLE_FAN);
	
	if (this->isFocus)
		glColor3dv(defaultColorArrowFocus);
	else
		glColor3dv(defaultColorArrowMain);

	glVertex2d(this->fX, this->fY);
	glVertex2d(x1, y1);
	glVertex2d(x3, y3);
	glVertex2d(x2, y2);
	glEnd();
}

bool Arrow::isFocused(int x, int y)
{
	double len = pow(pow(fX - sX, 2.0) + pow(fY - sY, 2.0), 0.5);
	double cs = (fX - sX) / len;
	double sn = (fY - sY) / len;

	double t0 = (cs < 0) ? -1.0 : 1.0;
	double t1 = (sn < 0) ? -1.0 : 1.0;

	cs = fabs(cs);
	sn = fabs(sn);

	double x1, x2, x3, y1, y2, y3;

	x1 = this->fX + t0 * this->length * (cs * 0.666 + cos(acos(cs) - this->angle / 2.0 + M_PI));
	y1 = this->fY + t1 * this->length * (sn * 0.666 + sin(acos(cs) - this->angle / 2.0 + M_PI));

	x2 = this->fX + t0 * this->length * (cs * 0.666 + cos(acos(cs) + this->angle / 2.0 + M_PI));
	y2 = this->fY + t1 * this->length * (sn * 0.666 + sin(acos(cs) + this->angle / 2.0 + M_PI));

	x3 = this->fX + t0 * cs * this->length;
	y3 = this->fY + t1 * sn * this->length;

	double sq0 = squareTriangle(x1, y1, x2, y2, x3, y3);
	double sq1 = squareTriangle(x1, y1, x3, y3, x, y);
	double sq2 = squareTriangle(x2, y2, x3, y3, x, y);
	double sq3 = squareTriangle(x1, y1, x2, y2, x, y);

	if (isnan(sq1))
		sq1 = 0;
	if (isnan(sq2))
		sq2 = 0;
	if (isnan(sq3))
		sq3 = 0;

	double sum = sq1 + sq2 + sq3;

	return (round(sum * 100) / 100 <= round(sq0 * 100) / 100);
}