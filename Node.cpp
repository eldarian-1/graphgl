#include "Node.h"

#include "Arrow.h"

void Node::setCoords(double x, double y, double r)
{
	if (this->figure == nullptr)
		this->figure = new Ellip();
	this->figure->setCoords(x, y, r, 20);

	this->text = Text(this->text.getText(), this->figure);
}

void Node::setCoords(double x, double y, double a, double b)
{
	if (this->figure == nullptr)
		this->figure = new Ellip();
	this->figure->setCoords(x, y, a, b);
}

void Node::draw()
{
	figure->draw();
	text.draw();

	for (int i = 0; i < this->paths; i++)
		Arrow(this->figure, this->ptr[i]->figure).draw();
}

void Node::setNode(const char* n, int ps, int* p, Node** pr)
{
	this->text = Text(n);
	this->paths = ps;
	this->path = p;
	this->ptr = pr;
}

void Node::isFocused(int x, int y, void (View::* func)(int, int))
{
	if (figure->isFocused(x, y))
	{
		this->isFocus = true;
		if (func != nullptr)
			(this->*((void (Node::*)(int, int))func))(x, y);
		else
			this->onFocused();
	}
	else if (this->isFocus)
	{
		this->isFocus = false;
		this->onUnfocused();
	}
}

void Node::onFocused()
{
	//printf("Город %c: onFocused\n", char('A' + this->focused));
}

void Node::onUnfocused()
{
	//printf("Город %c: onUnfocused\n", char('A' + this->focused));
}

void Node::onClick(int x, int y)
{
	//printf("Город %c: onClick\n", char('A' + this->focused));
}

void Node::onMouseLeftDown(int x, int y)
{
	//printf("Город %c: onMouseLeftDown\n", char('A' + this->focused));
}

void Node::onMouseLeftUp(int x, int y)
{
	//printf("Город %c: onMouseLeftUp\n", char('A' + this->focused));
}

void Node::onMouseRightDown(int x, int y)
{
	//printf("Город %c: onMouseRightDown\n", char('A' + this->focused));
}

void Node::onMouseRightUp(int x, int y)
{
	//printf("Город %c: onMouseRightUp\n", char('A' + this->focused));
}