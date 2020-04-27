#include <iostream>
using namespace std;

#include "App.h"

void btnAutoCities();
void btnSetCities();
void btnFindPath();

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Rus");

	Control ctrl[] = {
		{15, 15, 120, 30, "Auto cities", btnAutoCities},
		{15, 60, 120, 30, "Set cities", btnSetCities},
		{15, 105, 120, 30, "Find path", btnFindPath}
	};

	App::getInstance(&argc, argv, ctrl, sizeof(ctrl)/(sizeof Control))->start();
	return 0;
}

void btnAutoCities()
{
	int count = 4;

	Node** cities = new Node*[4];

	int* counts = new int[4];

	int** paths = new int* [4];
	paths[0] = new int[3];
	paths[1] = new int[3];
	paths[2] = new int[3];
	paths[3] = new int[3];

	Node*** ptrs = new Node * *[4];
	ptrs[0] = new Node * [3];
	ptrs[1] = new Node * [3];
	ptrs[2] = new Node * [3];
	ptrs[3] = new Node * [3];

	counts[0] = counts[1] = counts[2] = counts[3] = 3;

	paths[0][0] = paths[0][1] = paths[0][2] =
		paths[1][0] = paths[1][1] = paths[1][2] = 
		paths[2][0] = paths[2][1] = paths[2][2] = 
		paths[3][0] = paths[3][1] = paths[3][2] = 101;

	cities[0] = new Node("Perm", counts[0], paths[0], ptrs[0]);
	cities[1] = new Node("Tashckent", counts[1], paths[1], ptrs[1]);
	cities[2] = new Node("SaintPetersburg", counts[2], paths[2], ptrs[2]);
	cities[3] = new Node("Vladicaucasus", counts[3], paths[3], ptrs[3]);

	ptrs[0][0] = cities[1];
	ptrs[0][1] = cities[2];
	ptrs[0][2] = cities[3];
	ptrs[1][0] = cities[0];
	ptrs[1][1] = cities[2];
	ptrs[1][2] = cities[3];
	ptrs[2][0] = cities[1];
	ptrs[2][1] = cities[0];
	ptrs[2][2] = cities[3];
	ptrs[3][0] = cities[1];
	ptrs[3][1] = cities[2];
	ptrs[3][2] = cities[0];

	App::getInstance()->setCities(cities, count);
}

void btnSetCities()
{
	char buffer[20];

	int count;
	Node** cities;

	char** names;
	int* counts;
	int** paths;
	Node*** ptrs;


	cout << "Введите число городов: ";
	cin >> count;

	cities = new Node * [count];
	names = new char* [count];
	counts = new int[count];
	paths = new int* [count];
	ptrs = new Node * *[count];

	for (int i = 0; i < count; i++)
	{
		cities[i] = new Node();
		cout << "Введите название города " << char('A' + i) << ": ";
		cin >> buffer;
		names[i] = new char[strlen(buffer) + 1];
		for (unsigned j = 0; j < strlen(buffer); j++)
			names[i][j] = buffer[j];
		names[i][strlen(buffer)] = '\0';
	}

	for (int i = 0; i < count; i++)
	{
		cout << "Введите число путей из города " << char('A' + i) << "-" << names[i] << ": ";
		cin >> counts[i];
		counts[i] = ((counts[i] > 0) && (counts[i] < count)) ? counts[i] : (count - 1);
		ptrs[i] = new Node * [counts[i]];
		paths[i] = new int[counts[i]];
		for (int j = 0, k = 0; (j < count) && (k < counts[i]); j++)
		{
			if (i == j)
				continue;
			int temp;
			cout << "Растояние от " << char('A' + i) << "-" << names[i] << " до " << char('A' + j) << "-" << names[j] << " (0 - дороги не существует): ";
			cin >> temp;
			if (temp)
			{
				paths[i][k] = temp;
				ptrs[i][k] = cities[j];
				k++;
			}
		}
	}

	for (int i = 0; i < count; i++)
		cities[i]->setNode(names[i], counts[i], paths[i], ptrs[i]);

	App::getInstance()->setCities(cities, count);
}

void btnFindPath()
{
	
}