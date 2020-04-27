#include "Text.h"

#include <glut.h>

void Text::draw()
{
	glColor3dv(this->color);
	for (int i = 0; this->text[i] != '\0'; i++)
	{
		glRasterPos2d(this->cX + i * 10, this->cY);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, this->text[i]);
	}
}

bool Text::isFocused(int x, int y)
{
	return false;
}