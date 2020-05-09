#pragma once

#include "View.h"
#include "Ellip.h"
#include "Text.h"
#include "Path.h"

class Node : public View
{
private:
	friend class Graph;
	friend class Path;

	Text text;
	Ellip* figure;
	int paths;
	Path* ptrs;
	bool isFocus;

	int* tempPath;
	Node** tempPtrs;
	bool isTemp;

public:
	Node(const char* n = nullptr, int ps = 0, int* p = nullptr, Node** pr = nullptr)
		: text(n), figure(nullptr), paths(ps), tempPath(p), tempPtrs(pr), isFocus(false), isTemp(true), ptrs(nullptr) {}

	Node(int x, int y, const char* n, int ps, int* p, Node** pr)
		: text(n), figure(new Ellip(x, y, n)), paths(ps), tempPath(p), tempPtrs(pr), isFocus(false), isTemp(true), ptrs(nullptr) {}

	~Node(){}


	static Node* movedNode, * fromNode, *actNode;
	static void moveNode(double x, double y);
	static int cXF, cYF, countBtn;

	const char* getText();

	void setPaths();
	void setEllip();

	int length() { return text.length(); }
	void setCoords(double x, double y);
	void setCoords(double x, double y, double r);
	void setCoords(double x, double y, double a, double b);
	
	void draw();

	void setNode(const char* n, int ps, int* p, Node** pr);
	void updNode(const char*);

	void delPath(Path* p);

	bool isFocused(int, int, void (View::*)(int, int) = nullptr);
	void onFocused();
	void onUnfocused();
	void onMouseLeftClick(int, int);
	void onMouseRightClick(int, int);
	void onMouseLeftDown(int, int);
	void onMouseLeftUp(int, int);
	void onMouseRightDown(int, int);
	void onMouseRightUp(int, int);

	friend void updBtn();
	friend void delBtn();
};
