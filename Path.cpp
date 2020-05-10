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
			{
				Arrow* temp = this->arrow;
				this->arrow = new Arrow(this->from->figure, this->to->figure, this->arrow->getFocus(), true);
				delete temp;
			}
			else
				this->arrow = new Arrow(this->from->figure, this->to->figure, false, true);

			this->isEllip = true;
			this->arrow->setXYforEllip(x, y, this->length);

			return;
		}

	if (this->arrow)
	{
		Arrow* temp = this->arrow;
		this->arrow = new Arrow(this->from->figure, this->to->figure, this->arrow->getFocus(), false);
		this->isEllip = false;
		delete temp;
	}
	else
		this->arrow = new Arrow(this->from->figure, this->to->figure);

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

	if (this->ellip)
		this->ellip->set(x, y, text, 3.0, 0, defaultColorMain, nullptr, defaultColorFocus);
	else
		this->ellip = new Ellip(x, y, text, 3.0, 0, defaultColorMain, nullptr, defaultColorFocus);

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

	char** row = new char* [3];

	const char* f = this->from->getText();
	int sf = strlen(f) + 6;
	row[0] = new char[sf];
	row[0][0] = 'f';
	row[0][1] = 'r';
	row[0][2] = 'o';
	row[0][3] = 'm';
	row[0][4] = ' ';
	for (int i = 0; i < sf - 6; i++)
		row[0][5 + i] = f[i];
	row[0][sf - 1] = '\0';

	const char* t = this->to->getText();
	int st = strlen(t) + 4;
	row[1] = new char[st];
	row[1][0] = 't';
	row[1][1] = 'o';
	row[1][2] = ' ';
	for (int i = 0; i < st - 4; i++)
		row[1][3 + i] = t[i];
	row[1][st - 1] = '\0';

	char buffer[10];
	myitoa(this->length, buffer, 10);
	int sd = strlen(buffer) + 7;
	row[2] = new char[sd];
	row[2][0] = 'p';
	row[2][1] = 'a';
	row[2][2] = 't';
	row[2][3] = 'h';
	row[2][4] = ':';
	row[2][5] = ' ';
	for (int i = 0; i < sd - 7; i++)
		row[2][6 + i] = buffer[i];
	row[2][sd - 1] = '\0';

	AboutView::getInstance()->set(row, 3);
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
			new Button(x, y, 120, 30, "Update path", updatePathBtn, new const char* [3] {"Click here to", "change the", "distance"}, 3),
			new Button(x, y + 29, 120, 30, "Delete path", delPathBtn, new const char* [2] {"Click here to", "delete the path"}, 2),
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