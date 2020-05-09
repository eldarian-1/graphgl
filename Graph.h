#pragma once

#include "View.h"
#include "Node.h"

class Graph: public View
{
private:
	static Graph* instance;

	Graph(Node** c = nullptr, int i = 0) :nodes(c), count(i), isNullptr(true) { setCoords(); }

	Node** nodes;
	int count;
	bool isNullptr;

public:
	static Graph* getInstance(Node** c = nullptr, int i = 0);

	int getCount();
	const char* getNameNode(int);
	Node* getPtrNode(int);

	void addNode(Node*);
	void setCoords();
	void setPaths();
	void setCities(Node**, int);
	void draw();

	void moveNode(int, int);
	void delNode(Node*);

	void getMatrix(int***& mat, int& n, int**& cost, int*& path);
	void outPath(int* path);

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