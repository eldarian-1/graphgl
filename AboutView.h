#pragma once

class AboutView
{
private:
	static AboutView* instance;

	AboutView() : row(nullptr), rows(0), isConst(true) {};
	~AboutView() {};

	const char** row;
	int rows;
	char isConst;

public:
	static AboutView* getInstance();

	void set(char** r = nullptr, int rs = 0, char isC = -1);
	void set(const char** r = nullptr, int rs = 0, char isC = 1);

	void clear();
	void draw();

};