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

	const char** desc;
	int sizeD;

public:
	Button(int x, int y, int width, int height, const char* text, void (*fnc)(), const char** d = nullptr, int sD = 0)
		: rect(x, y, width, height), text(text, &rect), func(fnc), isFocus(false), desc(d), sizeD(sD) {}

	void draw();

	bool isFocused(int, int, void (View::*)(int, int) = nullptr);
	void onFocused();
	void onUnfocused();
	void onMouseLeftClick(int, int);
	void onMouseRightClick(int, int);
	void onMouseLeftDown(int, int);
	void onMouseLeftUp(int, int);
	void onMouseRightDown(int, int);
	void onMouseRightUp(int, int);

};