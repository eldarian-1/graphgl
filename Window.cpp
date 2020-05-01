#include "Window.h"

#include "App.h"
#include "AppFunc.h"

#include <iostream>
using namespace std;

int Window::countBtn = 0;
int Window::actX = 0;
int Window::actY = 0;

bool Window::isFocused(int x, int y, void (View::*func)(int, int))
{
	return false;
}

void Window::onFocused()
{
	//printf("Window: onFocused\n");
}

void Window::onUnfocused()
{
	//printf("Window: onUnfocused\n");
}

void Window::onMouseLeftClick(int x, int y)
{
	//printf("Window: onMouseLeftClick\n");

	if (countBtn)
	{
		App::getInstance()->popStack(countBtn);
		countBtn = 0;
	}
}

void Window::onMouseRightClick(int x, int y)
{
	//printf("Window: onMouseRightClick\n");

	actX = x;
	actY = y;

	if (countBtn)
	{
		App::getInstance()->popStack(countBtn);
		countBtn = 0;
	}

	Button* ctrl[] = {
		new Button(x, y, 120, 30, "Add node", addBtn)
	};

	countBtn = (sizeof ctrl) / sizeof(Button*);

	App::getInstance()->addStack(ctrl, countBtn);
}

void Window::onMouseLeftDown(int x, int y)
{
	//printf("Window: onMouseLeftDown\n");
}

void Window::onMouseLeftUp(int x, int y)
{
	//printf("Window: onMouseLeftUp\n");
}

void Window::onMouseRightDown(int x, int y)
{
	//printf("Window: onMouseRightDown\n");
}

void Window::onMouseRightUp(int x, int y)
{
	//printf("Window: onMouseRightUp\n");
}

void addBtn()
{
	App::getInstance()->popStack(Window::countBtn);
	Window::countBtn = 0;

	char buffer[100];

	int num = App::getInstance()->getCountGraph();

	cout << "������� �������� ������ " << char('A' + num) << ": ";
	cin >> buffer;

	int len = strlen(buffer);

	char* name = new char[len + 1];
	for (int i = 0; i < len; i++)
		name[i] = buffer[i];
	name[len] = '\0';

	int paths;
	cout << "������� ����� ����� �� ������ " << char('A' + num) << "-" << name << ": ";
	cin >> paths;

	paths = ((paths >= 0) && (paths <= num)) ? paths : (num);
	Node** ptr = new Node* [paths];
	int* path = new int[paths];

	for (int i = 0, k = 0; (i < num) && (k < paths); i++)
	{
		int temp;
		cout << "��������� �� " << char('A' + num) << "-" << name << " �� " << char('A' + i) << "-" << App::getInstance()->getNameNode(i) << " (0 - ������ �� ����������): ";
		cin >> temp;
		if (temp)
		{
			path[k] = temp;
			ptr[k] = App::getInstance()->getPtrNode(i);
			k++;
		}
	}

	Node* node = new Node(Window::actX, Window::actY, name, paths, path, ptr);

	App::getInstance()->addGraph(node);
}