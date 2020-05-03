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
	bool isEllip;
	Arrow* arrow;

public:
	Path(Node* frN = nullptr, Node* tN = nullptr, int len =  0, bool isF = false, bool isE = true, Arrow* ar = nullptr)
		: from(frN), to(tN), length(len), isFocus(isF), isEllip(isE), arrow(ar) {}

	static Path* actPath;
	static Node* actNode;
	static int countBtn;

	void setEllip();
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

	friend void delPathBtn();
};