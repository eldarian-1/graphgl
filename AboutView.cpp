#include "AboutView.h"

#include "Text.h"

AboutView* AboutView::instance = nullptr;

AboutView* AboutView::getInstance()
{
	if (!instance)
		instance = new AboutView();
	return instance;
}

void AboutView::set(char** r, int rs)
{
	this->clear();

	this->row = const_cast<const char**>(r);
	this->rows = rs;

	this->isConst = false;
}

void AboutView::set(const char** r, int rs)
{
	this->clear();

	this->row = r;
	this->rows = rs;

	this->isConst = true;
}

void AboutView::clear()
{
	if (this->isConst)
	{
		delete[] this->row;
	}
	else
	{
		for (int i = 0; i < this->rows; i++)
			delete[] this->row[i];
		delete[] this->row;
	}

	this->row = nullptr;
	this->rows = 0;
	this->isConst = true;
}

void AboutView::draw()
{
	if(this->row)
		for (int i = 0; i < this->rows; i++)
			Text(this->row[i], nullptr, 15, 200 + i * 18, 8).draw();
}