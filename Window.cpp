#include "Window.h"

#include "App.h"
#include "AppFunc.h"
#include "AboutView.h"

#include <iostream>
#include <glut.h>
using namespace std;

int Window::countBtn = 0;
int Window::actX = 0;
int Window::actY = 0;

bool Window::isFocused(int x, int y, void (View::*func)(int, int))
{
	actX = x;
	actY = y;

	if (x >= 150 && x <= APP_WIDTH)
	{
		this->onFocused();
		return true;
	}
	
	onUnfocused();
	return false;
}

void Window::onFocused()
{
	//printf("Window: onFocused\n");

	char** row = new char* [2];
	int i;
	char buffer[10];

	myitoa(actX, buffer, 10);
	row[0] = new char[8]{ 'x', ':', ' ' };
	for (i = 0; i < strlen(buffer); i++)
		row[0][3 + i] = buffer[i];
	row[0][3 + i] = '\0';

	myitoa(actY, buffer, 10);
	row[1] = new char[8]{ 'y', ':', ' ' };
	for (i = 0; i < strlen(buffer); i++)
		row[1][3 + i] = buffer[i];
	row[1][3 + i] = '\0';

	AboutView::getInstance()->set(row, 2);
}

void Window::onUnfocused()
{
	//printf("Window: onUnfocused\n");

	AboutView::getInstance()->clear();
}

void Window::onMouseLeftClick(int x, int y)
{
	//printf("Window: onMouseLeftClick\n");
	
	App::getInstance()->delOtherBtn();
}

void Window::onMouseRightClick(int x, int y)
{
	//printf("Window: onMouseRightClick\n");

	actX = x;
	actY = y;

	App::getInstance()->delOtherBtn();

	Button* ctrl[] = {
		new Button(x, y, 120, 30, "Add node", addBtn, new const char* [2] {"Click here to", "create a node"}, 2)
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

	cout << "Введите название города " << char('A' + num) << ": ";
	cin >> buffer;

	int len = strlen(buffer);

	char* name = new char[len + 1];
	for (int i = 0; i < len; i++)
		name[i] = buffer[i];
	name[len] = '\0';

	int paths;
	cout << "Введите число путей из города " << char('A' + num) << "-" << name << ": ";
	cin >> paths;

	paths = ((paths >= 0) && (paths <= num)) ? paths : (num);
	Node** ptr = new Node* [paths];
	int* path = new int[paths];

	for (int i = 0, k = 0; (i < num) && (k < paths); i++)
	{
		int temp;
		cout << "Растояние от " << char('A' + num) << "-" << name << " до " << char('A' + i) << "-" << App::getInstance()->getNameNode(i) << " (0 - дороги не существует): ";
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