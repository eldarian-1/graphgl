#include "Rect.h"

#include <glut.h>

void Rect::draw()
{
	if (this->weight != 0)
	{
		glBegin(GL_QUADS);
		glColor3dv(this->colorBorder);
		glVertex2d(this->cX, this->cY);
		glVertex2d(this->cX, this->cY + this->height);
		glVertex2d(this->cX + this->width, this->cY + this->height);
		glVertex2d(this->cX + this->width, this->cY);
		glEnd();
	}

	glBegin(GL_QUADS);

	if(isFocus)
		glColor3dv(this->colorFocus);
	else
		glColor3dv(this->colorMain);

	glVertex2d(this->cX + this->weight, this->cY + this->weight);
	glVertex2d(this->cX + this->weight, this->cY + this->height - this->weight);
	glVertex2d(this->cX + this->width - this->weight, this->cY + this->height - this->weight);
	glVertex2d(this->cX + this->width - this->weight, this->cY + this->weight);
	glEnd();
}

bool Rect::isFocused(int x, int y)
{
	this->isFocus = ((this->cX <= x) && ((this->cX + this->width) >= x) && (this->cY <= y) && ((this->cY + this->height) >= y));
	return this->isFocus;
}