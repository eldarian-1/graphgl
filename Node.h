#pragma once

#include "View.h"
#include "Ellip.h"
#include "Text.h"

class Node : public View
{
private:
	friend class Graph;

	Text text;
	Ellip* figure;

	int paths;
	int* path;
	Node** ptr;
	bool isFocus;

public:
	Node(const char* n = nullptr, int ps = 0, int* p = nullptr, Node** pr = nullptr)
		: text(n), figure(nullptr), paths(ps), path(p), ptr(pr), isFocus(false) {};

	~Node(){}

	int length() { return text.length(); }

	void setCoords(double x, double y, double r);
	void setCoords(double x, double y, double a, double b);
	void draw();

	void setNode(const char* n, int ps, int* p, Node** pr);

	void isFocused(int, int, void (View::*)(int, int) = nullptr);
	void onFocused();
	void onUnfocused();
	void onClick(int, int);
	void onMouseLeftDown(int, int);
	void onMouseLeftUp(int, int);
	void onMouseRightDown(int, int);
	void onMouseRightUp(int, int);
};