#include "App.h"
#include "Window.h"

#include <glut.h>
#include <iostream>
using namespace std;

App* App::instance = nullptr;
bool App::isMenu = false;

int xDown, yDown;

void displayFunc();
void reshapeFunc(int, int);
void passiveMotionFunc(int, int);
void motionFunc(int, int);
void mouseFunc(int, int, int, int);

App* App::getInstance(int* argc, char** argv, Button** ctrl, int size)
{
	if (!instance)
		instance = new App(argc, argv, ctrl, size);

	return instance;
}

App::App(int* argc, char** argv, Button** ctrl, int size)
{
	this->isStarted = false;
	this->graph = Graph::getInstance();
	this->stack = Stack::getInstance();
	this->aboutView = AboutView::getInstance();

	this->addStack(ctrl, size);

	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	int app_width = glutGet(GLUT_SCREEN_WIDTH);
	int app_height = glutGet(GLUT_SCREEN_HEIGHT);
	cout << "Screen: width = " << app_width << ", height = " << app_height << endl;

	glutInitWindowSize(APP_WIDTH, APP_HEIGHT);
	glutInitWindowPosition((app_width - APP_WIDTH) / 2, int(app_height - APP_HEIGHT * 1.3) / 2);
	glutCreateWindow("Graph with OpenGL");
}

void App::start()
{
	if (!this->isStarted)
	{
		glutDisplayFunc(displayFunc);
		glutReshapeFunc(reshapeFunc);
		glutPassiveMotionFunc(passiveMotionFunc);
		glutMotionFunc(motionFunc);
		glutMouseFunc(mouseFunc);
		glutMainLoop();
		this->isStarted = true;
	}
}

int App::getCountGraph()
{
	return this->graph->getCount();
}

const char* App::getNameNode(int num)
{
	return this->graph->getNameNode(num);
}

Node* App::getPtrNode(int num)
{
	return this->graph->getPtrNode(num);
}

void App::addStack(Button** ctrl, int size)
{
	for (int i = 0; i < size; i++)
		this->stack->add(ctrl[i]);
}

void App::addGraph(Node* node)
{
	this->graph->addNode(node);
	glutPostRedisplay();
}

void App::popStack(int count)
{
	for(int i = 0; i < count; i++)
		this->stack->pop();
}

void App::setCities(Node** cities, int count)
{
	this->graph->setCities(cities, count);
	this->graph->setCoords();
	glutPostRedisplay();
}

void App::setCoords()
{
	this->graph->setCoords();
	glutPostRedisplay();
}

void App::delOtherBtn()
{
	if (Window::countBtn)
	{
		this->popStack(Window::countBtn);
		Window::countBtn = 0;
	}

	if (Node::countBtn)
	{
		this->popStack(Node::countBtn);
		Node::countBtn = 0;
	}

	if (Path::countBtn)
	{
		this->popStack(Path::countBtn);
		Path::countBtn = 0;
	}
}

void App::getMatrix(int***& mat, int& n, int**& cost, int*& path)
{
	this->graph->getMatrix(mat, n, cost, path);
}

void App::outPath(int* path)
{
	this->graph->outPath(path);
}

void App::draw()
{
	this->graph->draw();
	this->stack->draw();
	this->aboutView->draw();
}

void displayFunc()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	App::getInstance()->draw();

	glBegin(GL_LINES);
	double c[] = { 0.75, 0.75, 0.75 };
	glColor3dv(c);
	glVertex2d(150.0, 0);
	glVertex2d(150.0, APP_HEIGHT);
	glVertex2d(0, 0);
	glVertex2d(APP_WIDTH, 0);
	glEnd();

	glutSwapBuffers();
	glFlush();
}

void reshapeFunc(int width, int height)
{
	glutReshapeWindow(width, height);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, height, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void motionFunc(int x, int y)
{
	App::getInstance()->graph->moveNode(x, y);
	glutPostRedisplay();
}

void passiveMotionFunc(int x, int y)
{
	bool temp = App::getInstance()->stack->isFocused(x, y);
	if(!temp)
		temp = App::getInstance()->graph->isFocused(x, y);
	if (!temp)
		Window().isFocused(x, y);
	glutPostRedisplay();
}

void mouseFunc(int button, int state, int x, int y)
{
	bool temp = false;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		xDown = x;
		yDown = y;
		temp = App::getInstance()->stack->isFocused(x, y, &View::onMouseLeftDown);
		if(!temp)
			temp = App::getInstance()->graph->isFocused(x, y, &View::onMouseLeftDown);
		if(!temp)
			Window().onMouseLeftDown(x, y);
	}

	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		xDown = x;
		yDown = y;
		temp = App::getInstance()->stack->isFocused(x, y, &View::onMouseRightDown);
		if (!temp)
			temp = App::getInstance()->graph->isFocused(x, y, &View::onMouseRightDown);
		if (!temp)
			Window().onMouseRightDown(x, y);
	}

	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		temp = App::getInstance()->stack->isFocused(x, y, &View::onMouseLeftUp);
		if (!temp)
			temp = App::getInstance()->graph->isFocused(x, y, &View::onMouseLeftUp);
		if(!temp)
			Window().onMouseRightDown(x, y);
		if (pow(x - xDown, 2) + pow(y - yDown, 2) <= 100)
		{
			temp = App::getInstance()->stack->isFocused(x, y, &View::onMouseLeftClick);
			if (!temp)
				temp = App::getInstance()->graph->isFocused(x, y, &View::onMouseLeftClick);
			if (!temp)
				Window().onMouseLeftClick(x, y);
		}
	}

	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		temp = App::getInstance()->stack->isFocused(x, y, &View::onMouseRightUp);
		if (!temp)
			temp = App::getInstance()->graph->isFocused(x, y, &View::onMouseRightUp);
		if (!temp)
			Window().onMouseRightUp(x, y);
		if (pow(x - xDown, 2) + pow(y - yDown, 2) <= 100)
		{
			temp = App::getInstance()->stack->isFocused(x, y, &View::onMouseRightClick);
			if (!temp)
				temp = App::getInstance()->graph->isFocused(x, y, &View::onMouseRightClick);
			if (!temp)
				Window().onMouseRightClick(x, y);
		}
	}

	glutPostRedisplay();
}