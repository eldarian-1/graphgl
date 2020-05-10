#include "Text.h"

#include <glut.h>

void Text::set(const char* t, Ellip* ellipse, double* c)
{
	this->text = t;
	this->cX = ellipse->getCX() - ellipse->getRA() + (ellipse->getRA() * 2.0 - strlen(t) * 10.0) / 2.0;
	this->cY = ellipse->getCY() - ellipse->getRB() + (ellipse->getRB() * 2.0 - 10.0) / 2.0 + 10;
	this->color = c;
}

void Text::draw()
{
	glColor3dv((this->color)?this->color:defaultColorAlt);

	for (int i = 0; this->text[i] != '\0'; i++)
	{
		glRasterPos2d(this->cX + i * this->dist, this->cY);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, this->text[i]);
	}
}

bool Text::isFocused(int x, int y)
{
	return false;
}