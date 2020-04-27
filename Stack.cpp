#include "Stack.h"

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

void Stack::draw()
{
	Node* temp = this->pTop;
	while (temp != nullptr)
	{
		temp->data->draw();
		temp = temp->pLow;
	}
}

void Stack::isFocused(int x, int y, void (View::* func)(int, int))
{
	Node* temp = this->pTop;
	while (temp != nullptr)
	{
		temp->data->isFocused(x, y, func);
		temp = temp->pLow;
	}
}