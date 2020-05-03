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

	static Stack* instance;

	Stack() : pTop(nullptr) {}

public:

	static Stack* getInstance();

	void add(Button*);
	void pop();
	void draw();
	bool isFocused(int, int, void (View::*)(int, int) = nullptr);
};