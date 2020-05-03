#include "Text.h"

#include <glut.h>

void Text::draw()
{
	glRotated(this->angle, 0, 0, 1.0);
	glColor3dv(this->color);

	/*glTranslated(this->cX, this->cY, 0);
	glCallLists(strlen(this->text), GL_UNSIGNED_BYTE, this->text);*/

	for (int i = 0; this->text[i] != '\0'; i++)
	{
		glRasterPos2d(this->cX + i * 10, this->cY);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, this->text[i]);
	}

	glRotated(-this->angle, 0, 0, 1.0);
}

bool Text::isFocused(int x, int y)
{
	return false;
}