#pragma once

#include "View.h"
#include "Node.h"

class Graph
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

	Node** getNodes();

	void getMatrix(int***& mat, int& n, int**& cost, int*& path);
	void outPath(int* path);

	bool isFocused(int, int, void (View::*)(int, int) = nullptr);

	friend void btnRebuild();
};