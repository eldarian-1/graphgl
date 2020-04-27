#include "Button.h"

void Button::draw()
{
	rect.draw();
	text.draw();
}

void Button::isFocused(int x, int y, void (View::* func)(int, int))
{
	if (rect.isFocused(x, y))
	{
		if (func == nullptr)
			this->onFocused();
		else
			(this->*((void (Button::*)(int, int))(func)))(x, y);
	}
	else
		this->onUnfocused();
}

void Button::onFocused()
{
	isFocus = true;
	//printf("Button: onFocused on x: %d, y: %d\n", x, y);
}

void Button::onUnfocused()
{
	isFocus = false;
	//printf("Button: onFocused on x: %d, y: %d\n", x, y);
}

void Button::onClick(int x, int y)
{
	//printf("Button: onClick on x: %d, y: %d\n", x, y);
	this->func();
}

void Button::onMouseLeftDown(int x, int y)
{
	//printf("Button: onMouseLeftDown on x: %d, y: %d\n", x, y);
}

void Button::onMouseLeftUp(int x, int y)
{
	//printf("Button: onMouseLeftUp on x: %d, y: %d\n", x, y);
}

void Button::onMouseRightDown(int x, int y)
{
	//printf("Button: onMouseRightDown on x: %d, y: %d\n", x, y);
}

void Button::onMouseRightUp(int x, int y)
{
	//printf("Button: onMouseRightUp on x: %d, y: %d\n", x, y);
}