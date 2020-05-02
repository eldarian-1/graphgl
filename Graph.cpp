#include "Graph.h"

#include <math.h>

#include "AppFunc.h"
#include "Arrow.h"

extern const int APP_WIDTH;
extern const int APP_HEIGHT;
extern const int APP_SHIFT;
extern const double M_PI;

Graph* Graph::instance = nullptr;

Graph* Graph::getInstance(Node** c, int i)
{
	if (instance == nullptr)
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

void Graph::setCities(Node** cities, int count)
{
	if (this->nodes != nullptr)
		delete[] this->nodes;

	this->nodes = cities;
	this->count = count;
}

void Graph::draw()
{
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
			isIs = this->nodes[i]->ptr[j] == node;

		if (isIs)
		{
			int j;
			int* path = this->nodes[i]->path;
			Node** ptr = this->nodes[i]->ptr;

			this->nodes[i]->path = new int[this->nodes[i]->paths - 1];
			this->nodes[i]->ptr = new Node*[this->nodes[i]->paths - 1];

			for (j = 0; ptr[j] != node; j++)
			{
				this->nodes[i]->path[j] = path[j];
				this->nodes[i]->ptr[j] = ptr[j];
			}

			for (++j; j < this->nodes[i]->paths; j++)
			{
				this->nodes[i]->path[j - 1] = path[j];
				this->nodes[i]->ptr[j - 1] = ptr[j];
			}

			--this->nodes[i]->paths;
			delete[] path;
			delete[] ptr;
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

bool Graph::isFocused(int x, int y, void (View::* func)(int, int))
{
	bool temp = false;
	for (int i = 0; i < this->count && !temp; i++)
		temp = this->nodes[i]->isFocused(x, y, func);
	return temp;
}

void Graph::onFocused()
{
	//printf("Город %c: onFocused\n", char('A' + this->focused));
}

void Graph::onUnfocused()
{
	//printf("Город %c: onUnfocused\n", char('A' + this->focused));
}

void Graph::onMouseLeftClick(int x, int y)
{
	//printf("Город %c: onMouseLeftClick\n", char('A' + this->focused));
}

void Graph::onMouseRightClick(int x, int y)
{
	//printf("Город %c: onMouseRightClick\n", char('A' + this->focused));
}

void Graph::onMouseLeftDown(int x, int y)
{
	//printf("Город %c: onMouseLeftDown\n", char('A' + this->focused));
}

void Graph::onMouseLeftUp(int x, int y)
{
	//printf("Город %c: onMouseLeftUp\n", char('A' + this->focused));
}

void Graph::onMouseRightDown(int x, int y)
{
	//printf("Город %c: onMouseRightDown\n", char('A' + this->focused));
}

void Graph::onMouseRightUp(int x, int y)
{
	//printf("Город %c: onMouseRightUp\n", char('A' + this->focused));
}