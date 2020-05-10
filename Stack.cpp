#include "Stack.h"

Stack* Stack::instance = nullptr;

Stack* Stack::getInstance()
{
	if (!instance)
		instance = new Stack();

	return instance;
}

void Stack::add(Button* data)
{
	if (this->pTop != nullptr)
	{
		Node* temp = this->pTop;
		while (temp->pLow != nullptr)
			temp = temp->pLow;
		temp->pLow = new Node{ nullptr, data };
	}
	else
	{
		this->pTop = new Node{ nullptr, data };
	}
}

void Stack::pop()
{
	if (this->pTop != nullptr)
	{
		Node* temp = this->pTop;
		while (temp->pLow->pLow != nullptr)
			temp = temp->pLow;
		delete temp->pLow;
		temp->pLow = nullptr;
	}
}

void Stack::draw()
{
	Node* temp = this->pTop;
	while (temp != nullptr)
	{
		temp->data->draw();
		temp = temp->pLow;
	}
}

bool Stack::isFocused(int x, int y, void (View::* func)(int, int))
{
	bool bl = false;
	Node* temp = this->pTop;
	while (temp)
	{
		if(!bl)
			bl = temp->data->isFocused(x, y, func);
		else
			temp->data->isFocused(x, y, func);
		temp = temp->pLow;
	}
	return bl;
}