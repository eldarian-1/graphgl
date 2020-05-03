#include "Path.h"

#include <math.h>

void Path::setEllip()
{
	for(int i = 0; i < this->to->paths; i++)
		if (this->from == this->to->ptrs[i].to)
		{
			if (this->arrow)
				delete this->arrow;

			this->isEllip = true;
			this->arrow = new Arrow(this->from->figure, this->to->figure, true);

			return;
		}

	if (this->arrow)
		delete this->arrow;

	this->isEllip = false;
	this->arrow = new Arrow(this->from->figure, this->to->figure, false);
}

void Path::draw()
{
	this->arrow->draw();
	char *buffer = new char[20];
	myitoa(this->length, buffer, 10);

	double sX = this->arrow->getSX(), sY = this->arrow->getSY(), fX = this->arrow->getFX(), fY = this->arrow->getFY();

	double len = pow(pow(fX - sX, 2) + pow(fY - sY, 2), 0.5);

	double cs = (fX - sX) / len;
	double sn = (fY - sY) / len;

	int str = strlen(buffer) * 10 / 2;

	double nX = sX + cs * (len / 2.0 - str);
	double nY = sY + sn * (len / 2.0 - 20.0);

	Text(buffer, nullptr, nX, nY, acos(cs)).draw();
	delete[] buffer;
}

bool Path::isFocused(int x, int y, void (View::* func)(int, int))
{
	if (this->arrow->isFocused(x, y))
	{
		this->isFocus = true;
		if (func != nullptr)
			(this->*((void (Path::*)(int, int))func))(x, y);
		else
			this->onFocused();
		return true;
	}
	else if (this->isFocus)
	{
		this->isFocus = false;
		this->onUnfocused();
	}
	return false;
}

void Path::onFocused()
{
	//printf("Button: onFocused on x: %d, y: %d\n", x, y);
}

void Path::onUnfocused()
{
	//printf("Button: onFocused on x: %d, y: %d\n", x, y);
}

void Path::onMouseLeftClick(int x, int y)
{
	//printf("Button: onMouseLeftClick on x: %d, y: %d\n", x, y);
}

void Path::onMouseRightClick(int x, int y)
{
	//printf("Button: onMouseRightClick on x: %d, y: %d\n", x, y);
}

void Path::onMouseLeftDown(int x, int y)
{
	//printf("Button: onMouseLeftDown on x: %d, y: %d\n", x, y);
}

void Path::onMouseLeftUp(int x, int y)
{
	//printf("Button: onMouseLeftUp on x: %d, y: %d\n", x, y);
}

void Path::onMouseRightDown(int x, int y)
{
	//printf("Button: onMouseRightDown on x: %d, y: %d\n", x, y);
}

void Path::onMouseRightUp(int x, int y)
{
	//printf("Button: onMouseRightUp on x: %d, y: %d\n", x, y);
}