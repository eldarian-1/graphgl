#include "Node.h"

#include "Arrow.h"

#include <stdio.h>

Node* Node::movedNode;
int Node::cXF, Node::cYF;

const char* Node::getText()
{
	return this->text.getText();
}

void Node::setCoords(double x, double y)
{
	this->figure->setCoords(x, y);
	this->text = Text(this->text.getText(), this->figure);
}

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

void Node::moveNode(double x, double y)
{
	if (movedNode)
	{
		movedNode->figure->setCoords(x + cXF, y + cYF);
		movedNode->text = Text(movedNode->text.getText(), movedNode->figure);
	}
}

bool Node::isFocused(int x, int y, void (View::* func)(int, int))
{
	if (this->figure->isFocused(x, y))
	{
		this->isFocus = true;
		if (func != nullptr)
			(this->*((void (Node::*)(int, int))func))(x, y);
		else
			this->onFocused();
		return true;
	}
	else if (this->isFocus)
	{
		this->isFocus = false;
		this->onUnfocused();
	}
	return false;
}

void Node::onFocused()
{
	//printf("Город %c: onFocused\n", char('A' + this->focused));
}

void Node::onUnfocused()
{
	//printf("Город %c: onUnfocused\n", char('A' + this->focused));
}

void Node::onMouseLeftClick(int x, int y)
{
	//printf("Город %c: onMouseLeftClick\n", char('A' + this->focused));
}

void Node::onMouseRightClick(int x, int y)
{
	//printf("Город %c: onMouseRightClick\n", char('A' + this->focused));
}

void Node::onMouseLeftDown(int x, int y)
{
	//printf("Город %s: onMouseLeftDown\n", this->text.getText());
	cXF = this->figure->getCX() - x;
	cYF = this->figure->getCY() - y;
	movedNode = this;
}

void Node::onMouseLeftUp(int x, int y)
{
	//printf("Город %s: onMouseLeftUp\n", this->text.getText());

	movedNode = nullptr;
}

void Node::onMouseRightDown(int x, int y)
{
	//printf("Город %c: onMouseRightDown\n", char('A' + this->focused));
}

void Node::onMouseRightUp(int x, int y)
{
	//printf("Город %c: onMouseRightUp\n", char('A' + this->focused));
}