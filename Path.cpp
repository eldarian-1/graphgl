#include "Path.h"

#include "App.h"

#include <stdio.h>
#include <math.h>

#include <iostream>
using namespace std;

Path* Path::actPath = nullptr;
Node* Path::actNode = nullptr;
int Path::countBtn = 0;

void updatePathBtn();
void delPathBtn();

Path::Path(Node* frN, Node* tN, int l, bool isF, bool isFE, bool isE, Arrow* ar, Ellip* el, Text* t)
	: from(frN), to(tN), length(l), isFocus(isF), isFocusEllip(isFE), isEllip(isE), arrow(ar), ellip(el), text(t) {}

void Path::setLength(int len)
{
	this->length = len;
}

void Path::setEllip(bool isE)
{
	if (this->arrow)
		this->arrow->setEllip(isE);
	else
		this->arrow = new Arrow(this->from->figure, this->to->figure, isE);
}

void Path::setEllip(double* x, double* y)
{
	for (int i = 0; i < this->to->paths; i++)
		if (this->from == this->to->ptrs[i].to)
		{
			if (this->arrow)
				delete this->arrow;

			this->isEllip = true;
			this->arrow = new Arrow(this->from->figure, this->to->figure, true);

			this->arrow->setXYforEllip(x, y, this->length);

			return;
		}

	if (this->arrow)
		delete this->arrow;

	this->isEllip = false;
	this->arrow = new Arrow(this->from->figure, this->to->figure, false);

	this->arrow->setXYforEllip(x, y, this->length);
}

void Path::setEllipText(double x, double y)
{
	char buffer[20];
	myitoa(this->length, buffer, 10);

	int str = strlen(buffer);
	char* text = new char[str + 1];
	for (int i = 0; i < str; i++)
		text[i] = buffer[i];
	text[str] = '\0';

	double* cM = new double[3]{ 0.95, 0.95, 0.95 };
	double* cF = new double[3]{ 0.95, 1.0, 1.0 };

	if (this->ellip)
		this->ellip->set(x, y, text, 3.0, 0, cM, nullptr, cF);
	else
		this->ellip = new Ellip(x, y, text, 3.0, 0, cM, nullptr, cF);

	if(this->text)
		this->text->set(text, this->ellip);
	else
		this->text = new Text(text, this->ellip);
}

void Path::draw()
{
	double x, y;
	this->setEllip(&x, &y);
	this->setEllipText(x, y);

	this->arrow->draw();
	this->ellip->draw();
	this->text->draw();
}

bool Path::isFocused(int x, int y, void (View::* func)(int, int))
{
	if (this->arrow->isFocused(x, y))
	{
		this->isFocus = true;
		this->isFocusEllip = false;
		this->arrow->setFocus(true);
		if (func != nullptr)
			(this->*((void (Path::*)(int, int))func))(x, y);
		else
			this->onFocused();
		return true;
	}
	else if (this->ellip->isFocused(x, y))
	{
		this->isFocus = true;
		this->isFocusEllip = true;
		this->arrow->setFocus(true);
		if (func != nullptr)
			(this->*((void (Path::*)(int, int))func))(x, y);
		else
			this->onFocused();
		return true;
	}
	else if (this->isFocus)
	{
		this->isFocus = false;
		this->arrow->setFocus(false);
		this->onUnfocused();
	}
	return false;
}

void Path::onFocused()
{
	//printf("Path: onFocused from %s to %s\n", this->from->getText(), this->to->getText());
}

void Path::onUnfocused()
{
	//printf("Path: onUnfocused\n");
}

void Path::onMouseLeftClick(int x, int y)
{
	//printf("Button: onMouseLeftClick on x: %d, y: %d\n", x, y);
	
	App::getInstance()->delOtherBtn();
}

void Path::onMouseRightClick(int x, int y)
{
	//printf("Button: onMouseRightClick on x: %d, y: %d\n", x, y);

	App::getInstance()->delOtherBtn();

	if (isFocusEllip && isFocus)
	{
		actNode = this->from;
		actPath = this;

		Button* ctrl[] = {
			new Button(x, y, 120, 30, "Update path", updatePathBtn),
			new Button(x, y + 30, 120, 30, "Delete path", delPathBtn),
		};

		countBtn = (sizeof ctrl) / sizeof(Button*);

		App::getInstance()->addStack(ctrl, countBtn);
	}
}

void Path::onMouseLeftDown(int x, int y)
{
	//printf("Button: onMouseLeftDown on x: %d, y: %d\n", x, y);
}

void Path::onMouseLeftUp(int x, int y)
{
	//printf("Button: onMouseLeftUp on x: %d, y: %d\n", x, y);
}

void Path::onMouseRightDown(int x, int y)
{
	//printf("Button: onMouseRightDown on x: %d, y: %d\n", x, y);

	if (!isFocusEllip && isFocus)
	{
		Node::fromNode = this->from;
		this->from->delPath(this);
	}
}

void Path::onMouseRightUp(int x, int y)
{
	//printf("Button: onMouseRightUp on x: %d, y: %d\n", x, y);
}

void updatePathBtn()
{
	App::getInstance()->popStack(Path::countBtn);
	Path::countBtn = 0;

	int s;
	cout << "Растояние от " << Path::actPath->from->getText() << " до " << Path::actPath->to->getText() << " (0 - дороги не существует): ";
	cin >> s;

	if (s > 0)
		Path::actPath->setLength(s);
	else
		Path::actNode->delPath(Path::actPath);

	Path::actNode = nullptr;
	Path::actPath = nullptr;
}

void delPathBtn()
{
	App::getInstance()->popStack(Path::countBtn);
	Path::countBtn = 0;

	Path::actNode->delPath(Path::actPath);
	Path::actNode = nullptr;
	Path::actPath = nullptr;
}