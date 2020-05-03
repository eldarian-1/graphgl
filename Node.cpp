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

Node::Node(const char* n, int ps, int* p, Node** pr)
	: text(n), figure(nullptr), paths(ps), tempPath(p), tempPtrs(pr), isFocus(false), isTemp(true), ptrs(nullptr)
{
	/*this->ptrs = new Path[ps];
	for (int i = 0; i < ps; i++)
		this->ptrs[i] = Path(this, pr[i], p[i]);*/
}

Node::Node(int x, int y, const char* n, int ps, int* p, Node** pr)
	: text(n), figure(new Ellip(x, y, n)), paths(ps), tempPath(p), tempPtrs(pr), isFocus(false), isTemp(true), ptrs(nullptr)
{
	/*this->ptrs = new Path[ps];
	for (int i = 0; i < ps; i++)
		this->ptrs[i] = Path(this, pr[i], p[i]);
	this->text = Text(n, this->figure);*/
};

void delBtn();

const char* Node::getText()
{
	return this->text.getText();
}

void Node::setPaths()
{
	if (this->isTemp)
	{
		this->isTemp = false;

		this->ptrs = new Path[this->paths];

		for (int i = 0; i < this->paths; i++)
			this->ptrs[i] = Path(this, this->tempPtrs[i], this->tempPath[i]);

		this->text = Text(this->getText(), this->figure);

		delete[] this->tempPath;
		delete[] this->tempPtrs;
		this->tempPath = nullptr;
		this->tempPtrs = nullptr;
	}
}

void Node::setEllip()
{
	for (int i = 0; i < this->paths; i++)
		this->ptrs[i].setEllip();
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
	this->setPaths();

	this->figure->draw();
	this->text.draw();
	for (int i = 0; i < this->paths; i++)
	{
		//this->ptrs[i].setEllip();
		this->ptrs[i].draw();
	}
	/*
	for (int i = 0; i < this->paths; i++)
	{
		bool isEllip = false;

		for (int j = 0; j < this->ptrs[i]-> && !isEllip; j++)
			isEllip = this == this->ptr[i]->ptr[j];

		Arrow(this->figure, this->ptr[i]->figure, isEllip, 1, M_PI/6, 20, (this->isFocus)?defaultColorArrowFocus : defaultColorArrowMain).draw();
	}
	*/
}

void Node::setNode(const char* n, int ps, int* p, Node** pr)
{
	this->text = Text(n);
	this->paths = ps;

	delete[] this->ptrs;
	this->ptrs = nullptr;

	this->tempPath = p;
	this->tempPtrs = pr;
	this->isTemp = true;
}

void Node::delPath(Path* p)
{
	int i;
	Path* temp = this->ptrs;
	this->ptrs = new Path[this->paths - 1];

	for (i = 0; &temp[i] != p; i++)
		this->ptrs[i] = temp[i];

	for (++i; i < this->paths; i++)
		this->ptrs[i - 1] = temp[i];

	--this->paths;
	delete[] temp;
}

void Node::moveNode(double x, double y)
{
	if (movedNode)
	{
		movedNode->figure->setCoords(
			(x + cXF + movedNode->figure->getRA() < APP_WIDTH) ? ((x + cXF - movedNode->figure->getRA() > 150) ? (x + cXF) : (150 + movedNode->figure->getRA())) : (APP_WIDTH - movedNode->figure->getRA()),
			(y + cYF + movedNode->figure->getRB() < APP_HEIGHT) ? ((y + cYF - movedNode->figure->getRB() > 0) ? (y + cYF) : (movedNode->figure->getRB())) : (APP_HEIGHT - movedNode->figure->getRB())
		);

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
	else if (this->paths)
	{
		bool arrowIsFocus = false;

		for (int i = 0; i < this->paths && !arrowIsFocus; i++)
			arrowIsFocus = this->ptrs[i].isFocused(x, y, func);

		if (arrowIsFocus)
			return true;
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

	if (fromNode)
		this->onMouseRightUp(x, y);
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
			temp = this == fromNode->ptrs[i].to;
		if (!temp)
		{
			int s;
			cout << "Растояние от " << fromNode->getText() << " до " << this->getText() << " (0 - дороги не существует): ";
			cin >> s;

			Path* ptrs = fromNode->ptrs;

			fromNode->ptrs = new Path[fromNode->paths + 1];

			for (int i = 0; i < fromNode->paths; i++)
				fromNode->ptrs[i] = ptrs[i];

			fromNode->ptrs[fromNode->paths] = Path(fromNode, this, s);
			++fromNode->paths;

			delete[] ptrs;
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