#pragma once

#include "AppFunc.h"
#include "Stack.h"
#include "Graph.h"
#include "Node.h"

class App
{
private:
	static App* instance;

	Stack* stack;
	Graph* graph;
	bool isStarted;

	App(int*, char**, Button**, int);

	void draw();

public:
	static App* getInstance(int* = nullptr, char** = nullptr, Button** = nullptr, int = 0);

	static bool isMenu;

	void start();

	int getCountGraph();
	const char* getNameNode(int);
	Node* getPtrNode(int);

	void addStack(Button** ctrl, int size);
	void addGraph(Node*);
	void popStack(int);
	void setCities(Node**, int);
	void setCoords();

	friend void displayFunc();
	friend void reshapeFunc(int, int);
	friend void motionFunc(int, int);
	friend void passiveMotionFunc(int, int);
	friend void mouseFunc(int, int, int, int);
};