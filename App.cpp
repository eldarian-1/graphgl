#include "App.h"

#include <glut.h>
#include <iostream>
using namespace std;

App* App::instance = nullptr;

int xDown, yDown;

void displayFunc();
void reshapeFunc(int, int);
void passiveMotionFunc(int, int);
void mouseFunc(int, int, int, int);

App* App::getInstance(int* argc, char** argv, Control* ctrl, int size)
{
	if (instance == 0)
		instance = new App(argc, argv, ctrl, size);
	return instance;
}

App::App(int* argc, char** argv, Control* ctrl, int size)
{
	this->isStarted = false;

	for(int i = 0; i < size; i++)
		this->stack.add(new Button(ctrl[i]));

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
		glutMouseFunc(mouseFunc);
		glutMainLoop();
		this->isStarted = true;
	}
}

void App::setCities(Node** cities, int count)
{
	this->graph.setCities(cities, count);
	this->graph.setCoords();
	glutPostRedisplay();
}

void App::draw()
{
	this->graph.draw();
	this->stack.draw();
}

void displayFunc()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	App::getInstance()->draw();
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

void passiveMotionFunc(int x, int y)
{
	App::getInstance()->stack.isFocused(x, y);
	App::getInstance()->graph.isFocused(x, y);
	glutPostRedisplay();
}

void mouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		xDown = x;
		yDown = y;
		App::getInstance()->stack.isFocused(x, y, &View::onMouseLeftDown);
		App::getInstance()->graph.isFocused(x, y, &View::onMouseLeftDown);
	}

	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (x == xDown && y == yDown)
		{
			App::getInstance()->stack.isFocused(x, y, &View::onClick);
			App::getInstance()->graph.isFocused(x, y, &View::onClick);
		}
		App::getInstance()->stack.isFocused(x, y, &View::onMouseLeftUp);
		App::getInstance()->graph.isFocused(x, y, &View::onMouseLeftUp);
	}

	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		App::getInstance()->stack.isFocused(x, y, &View::onMouseRightDown);
		App::getInstance()->graph.isFocused(x, y, &View::onMouseRightDown);
	}

	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		App::getInstance()->stack.isFocused(x, y, &View::onMouseRightUp);
		App::getInstance()->graph.isFocused(x, y, &View::onMouseRightUp);
	}

	glutPostRedisplay();
}