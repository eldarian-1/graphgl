#include "Button.h"

#include "AboutView.h"

void Button::draw()
{
	rect.draw();
	text.draw();
}

bool Button::isFocused(int x, int y, void (View::* func)(int, int))
{
	if (this->rect.isFocused(x, y))
	{
		this->isFocus = true;
		if (func != nullptr)
			(this->*((void (Button::*)(int, int))func))(x, y);
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

void Button::onFocused()
{
	//printf("Button: onFocused on x: %d, y: %d\n", x, y);

	AboutView::getInstance()->set("Click here and something will happen");
}

void Button::onUnfocused()
{
	//printf("Button: onFocused on x: %d, y: %d\n", x, y);
}

void Button::onMouseLeftClick(int x, int y)
{
	//printf("Button: onMouseLeftClick on x: %d, y: %d\n", x, y);
	this->func();
}

void Button::onMouseRightClick(int x, int y)
{
	//printf("Button: onMouseRightClick on x: %d, y: %d\n", x, y);
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