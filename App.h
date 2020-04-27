#pragma once

#include "AppFunc.h"
#include "Stack.h"
#include "Graph.h"
#include "Node.h"

class App
{
private:
	static App* instance;

	Stack stack;
	Graph graph;
	bool isStarted;

	App(int*, char**, Control*, int);

	void draw();

public:
	static App* getInstance(int* = nullptr, char** = nullptr, Control* = nullptr, int = 0);

	void start();

	void setCities(Node**, int);

	friend void displayFunc();
	friend void reshapeFunc(int, int);
	friend void passiveMotionFunc(int, int);
	friend void mouseFunc(int, int, int, int);
};