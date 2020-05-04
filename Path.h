#pragma once

#include "Node.h"
#include "Arrow.h"

class Path : public View
{
private:
	friend class Graph;
	friend class Node;

	Node* from;
	Node* to;
	int length;

	bool isFocus;
	bool isFocusEllip;
	bool isEllip;

	Arrow* arrow;
	Ellip* ellip;
	Text* text;

public:
	Path(Node* frN = nullptr, Node* tN = nullptr, int len = 0, bool isF = false, bool isFE = false, bool isE = true, Arrow* ar = nullptr, Ellip* el = nullptr, Text* t = nullptr);

	static Path* actPath;
	static Node* actNode;
	static int countBtn;

	void setLength(int len);

	void setEllip(bool isE);
	void setEllip(double* x = nullptr, double* y = nullptr);
	void setEllipText(double x, double y);
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

	friend void updatePathBtn();
	friend void delPathBtn();
};