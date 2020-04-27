#pragma once

#include "Button.h"
#include "View.h"

class Stack
{
private:
	struct Node {
		Node* pLow = nullptr;
		Button* data = nullptr;
	}* pTop;

public:
	Stack() : pTop(nullptr){}

	void add(Button*);
	void draw();
	void isFocused(int, int, void (View::*)(int, int) = nullptr);
};