#include "AboutView.h"

#include "Text.h"
#include "AppFunc.h"

AboutView* AboutView::instance = nullptr;

AboutView* AboutView::getInstance()
{
	if (!instance)
		instance = new AboutView();
	return instance;
}

void AboutView::set(char** r, int rs, char isC)
{
	this->clear();

	this->row = const_cast<const char**>(r);
	this->rows = rs;

	this->isConst = isC;
}

void AboutView::set(const char** r, int rs, char isC)
{
	this->clear();

	this->row = r;
	this->rows = rs;

	this->isConst = isC;
}

void AboutView::clear()
{
	if (this->isConst == 1)
	{
		delete[] this->row;
	}
	else if(this->isConst == -1)
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
			Text(this->row[i], nullptr, 15, APP_ABOUT + i * 18, 8).draw();
}