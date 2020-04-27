#include "Line.h"

#include <glut.h>

void Line::draw()
{
	glLineWidth((float)this->weight);
	glBegin(GL_LINES);
	glColor3dv(this->color);
	glVertex2d(this->sX, this->sY);
	glVertex2d(this->fX, this->fY);
	glEnd();
}

bool Line::isFocused(int, int)
{
	return false;
}
