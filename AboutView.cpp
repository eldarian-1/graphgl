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

	this->row = r;
	this->rows = rs;

	this->isConst = false;
}

void AboutView::set(const char* r)
{
	this->clear();

	int len = strlen(r);
	this->rows = len / 12 + 1;
	this->row = new char* [this->rows];
	for (int i = 0; i < this->rows; i++)
	{
		this->row[i] = new char[13];
		for (int j = 0; j < 12; j++)
			this->row[i][j] = r[i * 12 + j];
		this->row[i][12] = '\0';
	}

	this->isConst = true;
}

void AboutView::clear()
{
	if (!this->isConst)
	{
		for (int i = 0; i < this->rows; i++)
			delete[] this->row[i];
		delete[] this->row;
	}

	this->row = nullptr;

	this->isConst = true;
}

void AboutView::draw()
{
	if(this->row)
		for (int i = 0; i < this->rows; i++)
			Text(this->row[i], nullptr, 15, 200 + i * 30).draw();
}