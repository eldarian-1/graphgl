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
void updBtn();

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
	{
		bool temp = false;

		for (int j = 0; j < this->ptrs[i].from->paths && !temp; j++)
			temp = this->ptrs[i].from == this->ptrs[i].from->ptrs[j].to;

		this->ptrs[i].setEllip(temp);
	}
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
		this->ptrs[i].draw();
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

void Node::updNode(const char* text)
{
	this->figure->updEllip(text);
	this->text = Text(text, this->figure);
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

	for(int i = 0; i < p->to->paths; i++)
		if (p->from == p->to->ptrs[i].to)
		{
			p->to->ptrs[i].setEllip(false);
			break;
		}

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

	char** row = new char* [
		(this->paths)?(this->paths + 1):(2)
	];

	const char* f = this->getText();
	int s = strlen(f) + 2;
	char* r = new char[s];
	for (int i = 0; i < s - 2; i++)
		r[i] = f[i];
	r[s - 2] = ':';
	r[s - 1] = '\0';
	row[0] = r;

	if (this->paths)
		for (int i = 0; i < this->paths; i++)
		{
			char buffer[10];
			myitoa(this->ptrs[i].length, buffer, 10);
			const char* f = this->ptrs[i].to->getText();
			int sc = strlen(f);
			int sn = strlen(buffer);
			int s = 6 + sc + sn;
			char* r = new char[s];
			r[0] = 't';
			r[1] = 'o';
			r[2] = ' ';
			for (int j = 0; j < sc; j++)
				r[3 + j] = f[j];
			r[3 + sc] = ':';
			r[4 + sc] = ' ';
			for (int j = 0; j < sn; j++)
				r[5 + sc + j] = buffer[j];
			r[5 + sc + sn] = '\0';
			row[1 + i] = r;
		}
	else
	{
		char t[] = "hasn't paths";
		int st = strlen(t);
		row[1] = new char[st + 1];
		for (int i = 0; i < st; i++)
			row[1][i] = t[i];
		row[1][st] = '\0';
	}

	AboutView::getInstance()->set(row,
		(this->paths) ? (this->paths + 1) : (2)
	);
}

void Node::onUnfocused()
{
	//printf("Город %c: onUnfocused\n", char('A' + this->focused));
}

void Node::onMouseLeftClick(int x, int y)
{
	//printf("Город %c: onMouseLeftClick\n", char('A' + this->focused));
	
	App::getInstance()->delOtherBtn();
}

void Node::onMouseRightClick(int x, int y)
{
	//printf("Город %c: onMouseRightClick\n", char('A' + this->focused));

	actNode = this;

	cXF = x;
	cYF = y;

	App::getInstance()->delOtherBtn();

	Button* ctrl[] = {
		new Button(x, y, 120, 30, "Update node", updBtn, new const char* [2] {"Click here to", "change the name"}, 2),
		new Button(x, y + 29, 120, 30, "Delete node", delBtn, new const char* [2] {"Click here to", "delete the node"}, 2)
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

			if (s <= 0)
				return;

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

void updBtn()
{
	App::getInstance()->popStack(Node::countBtn);
	Node::countBtn = 0;

	char buffer[30];

	cout << "Введите новое название города " << Node::actNode->getText() << ": ";
	cin >> buffer;

	int len = strlen(buffer);
	char* text = new char[len + 1];
	for (int i = 0; i < len; i++)
		text[i] = buffer[i];
	text[len] = '\0';

	Node::actNode->updNode(text);
	Node::actNode = nullptr;
}

void delBtn()
{
	App::getInstance()->popStack(Node::countBtn);
	Node::countBtn = 0;

	Graph::getInstance()->delNode(Node::actNode);
	Node::actNode = nullptr;
}