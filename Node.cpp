#include "Node.h"

#include "Arrow.h"
#include "Graph.h"
#include "App.h"

#include <iostream>
#include <glut.h>
using namespace std;

Node* Node::movedNode;
Node* Node::fromNode;
Node* Node::actNode;
int Node::cXF, Node::cYF, Node::countBtn;

void delBtn();

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
	{
		bool isEllip = false;

		for (int j = 0; j < this->ptr[i]->paths && !isEllip; j++)
			isEllip = this == this->ptr[i]->ptr[j];

		Arrow(this->figure, this->ptr[i]->figure, isEllip, 1, M_PI/6, 20, (this->isFocus)?defaultColorArrowFocus : defaultColorArrowMain).draw();
	}
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
	if (fromNode)
	{
		cXF = (int)x;
		cYF = (int)y;
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

	if (fromNode && func != &View::onMouseRightUp)
		fromNode->onMouseRightUp(x, y);

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

	actNode = this;

	cXF = x;
	cYF = y;

	if (countBtn)
	{
		App::getInstance()->popStack(countBtn);
		countBtn = 0;
	}

	Button* ctrl[] = {
		new Button(x, y, 120, 30, "Delete node", delBtn)
	};

	countBtn = (sizeof ctrl) / sizeof(Button*);

	App::getInstance()->addStack(ctrl, countBtn);
}

void Node::onMouseLeftDown(int x, int y)
{
	//printf("Город %s: onMouseLeftDown\n", this->text.getText());

	cXF = (int)this->figure->getCX() - x;
	cYF = (int)this->figure->getCY() - y;

	movedNode = this;

	if (countBtn)
	{
		App::getInstance()->popStack(countBtn);
		countBtn = 0;
	}
}

void Node::onMouseLeftUp(int x, int y)
{
	//printf("Город %s: onMouseLeftUp\n", this->text.getText());

	movedNode = nullptr;
}

void Node::onMouseRightDown(int x, int y)
{
	//printf("Город %c: onMouseRightDown\n", char('A' + this->focused));

	fromNode = this;
}

void Node::onMouseRightUp(int x, int y)
{
	//printf("Город %c: onMouseRightUp\n", char('A' + this->focused));

	if (this != fromNode)
	{
		bool temp = false;
		for (int i = 0; i < fromNode->paths && !temp; i++)
			temp = this == fromNode->ptr[i];
		if (!temp)
		{
			int s;
			cout << "Растояние от " << fromNode->getText() << " до " << this->getText() << " (0 - дороги не существует): ";
			cin >> s;

			int* path = fromNode->path;
			Node** ptr = fromNode->ptr;

			fromNode->path = new int[fromNode->paths + 1];
			fromNode->ptr = new Node*[fromNode->paths + 1];

			for (int i = 0; i < fromNode->paths; i++)
			{
				fromNode->path[i] = path[i];
				fromNode->ptr[i] = ptr[i];
			}

			fromNode->path[fromNode->paths] = s;
			fromNode->ptr[fromNode->paths] = this;
			++fromNode->paths;

			delete path;
			delete[] ptr;
		}
	}

	fromNode = nullptr;
}

void delBtn()
{
	App::getInstance()->popStack(Node::countBtn);
	Node::countBtn = 0;

	Graph::getInstance()->delNode(Node::actNode);
	Node::actNode = nullptr;
}