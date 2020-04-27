#include "Graph.h"

#include <math.h>

#include "AppFunc.h"

extern const int APP_WIDTH;
extern const int APP_HEIGHT;
extern const int APP_SHIFT;
extern const double M_PI;

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
		double x0 = cX + R * cosf(t0);
		double y0 = cY + R * sinf(t0);
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
}

void Graph::isFocused(int x, int y, void (View::* func)(int, int))
{
	for (int i = 0; i < this->count; i++)
		this->nodes[i]->isFocused(x, y, func);
}

void Graph::onFocused()
{
	//printf("Город %c: onFocused\n", char('A' + this->focused));
}

void Graph::onUnfocused()
{
	//printf("Город %c: onUnfocused\n", char('A' + this->focused));
}

void Graph::onClick(int x, int y)
{
	//printf("Город %c: onClick\n", char('A' + this->focused));
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