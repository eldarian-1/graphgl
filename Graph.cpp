#pragma once

#include "Graph.h"

#include <iostream>
#include <cmath>
using namespace std;

#include "AppFunc.h"
#include "Arrow.h"
#include "App.h"

extern const int APP_WIDTH;
extern const int APP_HEIGHT;
extern const int APP_SHIFT;
extern const double M_PI;

Graph* Graph::instance = nullptr;

void btnRebuild();

Graph* Graph::getInstance(Node** c, int i)
{
	if (!instance)
		instance = new Graph(c, i);

	return instance;
}

int Graph::getCount()
{
	return this->count;
}

const char* Graph::getNameNode(int num)
{
	return this->nodes[num]->getText();
}

Node* Graph::getPtrNode(int num)
{
	return this->nodes[num];
}

void Graph::addNode(Node* node)
{
	Node** temp = this->nodes;
	this->nodes = new Node * [this->count + 1];
	for (int i = 0; i < this->count; i++)
		this->nodes[i] = temp[i];
	this->nodes[this->count++] = node;
}

void Graph::setCoords()
{
	this->isNullptr = false;

	double cX = APP_WIDTH / 2;
	double cY = APP_HEIGHT / 2;
	double R = APP_HEIGHT / 2.5;

	double step = 2.0 * M_PI / double(this->count);

	for (int i = 0, k = 1; i < this->count; i++)
	{
		double t0 = -M_PI / 2 + step * i;
		double x0 = cX + R * cos(t0);
		double y0 = cY + R * sin(t0);
		double r0 = this->nodes[i]->length() * 5.0 + 10.0;

		Node* temp = nodes[i];
		nodes[i]->setCoords(x0, y0, r0);
	}
}

void Graph::setPaths()
{
	for (int i = 0; i < this->count; i++)
		this->nodes[i]->setPaths();

	for (int i = 0; i < this->count; i++)
		this->nodes[i]->setEllip();
}

void Graph::setCities(Node** cities, int count)
{
	if (this->nodes != nullptr)
		delete[] this->nodes;

	this->nodes = cities;
	this->count = count;
}

void Graph::draw()
{
	this->setPaths();

	if (App::getInstance()->isFind())
		Text("Start", defaultColorArrowFocus, this->nodes[0]->figure->getCX() - 25, this->nodes[0]->figure->getCY() - 25).draw();

	for (int i = 0; i < this->count; i++)
		this->nodes[i]->draw();

	if (Node::fromNode)
		Arrow(Node::fromNode->figure, Node::cXF, Node::cYF).draw();
}

void Graph::moveNode(int x, int y)
{
	Node::moveNode(x, y);
}

void Graph::delNode(Node* node)
{
	for (int i = 0; i < this->count; i++)
	{
		bool isIs = false;

		if (this->nodes[i] == node)
			continue;

		for (int j = 0; j < this->nodes[i]->paths && !isIs; j++)
			isIs = this->nodes[i]->ptrs[j].to == node;

		if (isIs)
		{
			int j;
			Path* ptrs = this->nodes[i]->ptrs;

			this->nodes[i]->ptrs = new Path[this->nodes[i]->paths - 1];

			for (j = 0; ptrs[j].to != node; j++)
				this->nodes[i]->ptrs[j] = ptrs[j];

			for (++j; j < this->nodes[i]->paths; j++)
				this->nodes[i]->ptrs[j - 1] = ptrs[j];

			--this->nodes[i]->paths;
			delete[] ptrs;
		}
	}

	Node** temp = this->nodes;
	this->nodes = new Node * [this->count - 1];
	int i;

	for (i = 0; temp[i] != node; i++)
		this->nodes[i] = temp[i];

	for (++i; i < this->count; i++)
		this->nodes[i - 1] = temp[i];

	--this->count;
	delete[] temp;
}

Node** Graph::getNodes()
{
	return this->nodes;
}

void Graph::getMatrix(int***& mat, int& n, int**& cost, int*& path)
{
	n = this->count;

	cost = new int* [n];
	for (int i = 0; i < n; i++)
		cost[i] = new int[n];

	path = new int[n];
	for (int i = 0; i < n; i++)
		path[i] = -1;

	mat = new int** [n];
	for (int i = 0; i < n; i++)
	{
		mat[i] = new int* [n];
		for (int j = 0; j < n; j++)
			mat[i][j] = nullptr;
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < this->nodes[i]->paths; j++)
		{
			bool f = false;
			for (int k = 0; k < n && !f; k++)
			{
				f = this->nodes[k] == this->nodes[i]->ptrs[j].to;
				if (f)
					mat[i][k] = new int(this->nodes[i]->ptrs[j].length);
			}
		}
}

void Graph::outPath(int* path)
{
	int sum = 0;

	for (int i = 0, j = 0; i < this->count; i++)
	{
		cout << this->nodes[j]->getText() << " - ";

		bool f = false;

		for (int k = 0; k < this->count && !f; k++)
		{
			f = this->nodes[j]->ptrs[k].to == this->nodes[path[j]];
			if (f)
				sum += this->nodes[j]->ptrs[k].length;
		}

		j = path[j];
	}
	cout << this->nodes[0]->getText() << endl;
	cout << "Path: " << sum << endl;

	App::getInstance()->toFinded();
	App::getInstance()->setPath(path);

	Stack::getInstance()->add(new Button(APP_MENU + 14, 15, 150, 30, "Rebuild graph", btnRebuild, new const char* [3]{ "Click here to", "rebuild", "the graph" }, 3));
}

bool Graph::isFocused(int x, int y, void (View::* func)(int, int))
{
	bool temp = false;
	for (int i = 0; i < this->count && !temp; i++)
		temp = this->nodes[i]->isFocused(x, y, func);
	return temp;
}

void btnRebuild()
{
	App* app = App::getInstance();
	Stack* stack = Stack::getInstance();
	Graph* graph = Graph::getInstance();
	Node** temp = new Node * [graph->count];
	int* path = app->getPath();

	for (int i = 0, j = 0; i < graph->count; i++)
	{
		temp[i] = graph->nodes[i];
		graph->nodes[i] = (i < j) ? (graph->nodes[j]) : (temp[j]);
		j = path[j];
	}

	delete[] temp;

	app->setPath(nullptr);
	app->toFinded();
	stack->pop();
	graph->setCoords();
}