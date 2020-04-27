#pragma once

#include "View.h"
#include "Rect.h"
#include "Text.h"
#include "AppFunc.h"

class Button : public View
{
private:
	Rect rect;
	Text text;
	void (*func)();
	bool isFocus;

public:
	Button(Control btn)
		: rect(btn.sX, btn.sY, btn.fX, btn.fY), text(btn.text, &rect), func(btn.func), isFocus(false) {}

	void draw();

	void isFocused(int, int, void (View::*)(int, int) = nullptr);
	void onFocused();
	void onUnfocused();
	void onClick(int, int);
	void onMouseLeftDown(int, int);
	void onMouseLeftUp(int, int);
	void onMouseRightDown(int, int);
	void onMouseRightUp(int, int);

};