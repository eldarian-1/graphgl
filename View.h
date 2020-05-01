#pragma once

class View
{
public:
	virtual bool isFocused(int, int, void (View::*)(int, int)) = 0;
	virtual void onFocused() = 0;
	virtual void onUnfocused() = 0;
	virtual void onMouseLeftClick(int, int) = 0;
	virtual void onMouseRightClick(int, int) = 0;
	virtual void onMouseLeftDown(int, int) = 0;
	virtual void onMouseLeftUp(int, int) = 0;
	virtual void onMouseRightDown(int, int) = 0;
	virtual void onMouseRightUp(int, int) = 0;
};