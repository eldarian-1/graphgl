#pragma once

#include "View.h"
#include "Node.h"

class Graph: public View
{
private:

	Node** nodes;
	int count;
	bool isNullptr;

public:
	Graph() :nodes(nullptr), count(0), isNullptr(true) {}
	Graph(Node** c, int i) :nodes(c), count(i), isNullptr(true) { setCoords(); }

	void setCoords();
	void setCities(Node**, int);
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

