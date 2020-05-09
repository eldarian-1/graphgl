#pragma once

class AboutView
{
private:
	static AboutView* instance;

	AboutView() : row(nullptr), rows(0), isConst(true) {};
	~AboutView() {};

	char** row;
	int rows;
	bool isConst;

public:
	static AboutView* getInstance();

	void set(char** r = nullptr, int rs = 0);
	void set(const char* r = nullptr);
	void clear();
	void draw();

};