#include "Arrow.h"

#include <glut.h>
#include <math.h>

Arrow::Arrow(Ellip* start, Ellip* finish, double weight, double angle, double length, double* color)
	:weight(weight), angle(angle), length(length), color(color)
{
	double len = pow(pow(finish->cX - start->cX, 2.0) + pow(finish->cY - start->cY, 2.0), 0.5);
	double cos = (finish->cX - start->cX) / len;
	double sin = (finish->cY - start->cY) / len;
	this->sX = start->cX + cos * start->rA;
	this->sY = start->cY + sin * start->rB;
	this->fX = finish->cX - cos * finish->rA;
	this->fY = finish->cY - sin * finish->rB;
}

void Arrow::draw()
{
	glLineWidth(this->weight);
	glBegin(GL_LINES);
	glColor3dv(this->color);
	glVertex2d(this->sX, this->sY);
	glVertex2d(this->fX, this->fY);
	glEnd();

	double len = pow(pow(fX - sX, 2.0) + pow(fY - sY, 2.0), 0.5);
	double cs = (fX - sX) / len;
	double sn = (fY - sY) / len;

	double t0 = (cs < 0) ? -1.0 : 1.0;
	double t1 = (sn < 0) ? -1.0 : 1.0;

	cs = fabsf(cs);
	sn = fabsf(sn);

	double x1 = this->fX + t0 * cos(M_PI + acos(cs) - this->angle / 2.0) * this->length;
	double y1 = this->fY + t1 * sin(M_PI + asin(sn) - this->angle / 2.0) * this->length;
	double x2 = this->fX + t0 * cos(M_PI + acos(cs) + this->angle / 2.0) * this->length;
	double y2 = this->fY + t1 * sin(M_PI + asin(sn) + this->angle / 2.0) * this->length;

	glBegin(GL_TRIANGLES);
	glColor3dv(this->color);
	glVertex2d(this->fX, this->fY);
	glVertex2d(x1, y1);
	glVertex2d(x2, y2);
	glEnd();
}

bool Arrow::isFocused(int, int)
{
	return false;
}