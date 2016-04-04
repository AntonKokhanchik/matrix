// matrix_menu.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "matrix.h"
#include "iostream"
#include "conio.h"


using namespace std;


int main()
{
	matrix matrix;
	do {} 
	while (menu(matrix));
    return 0;
}

bool menu(matrix matrix)
{
	print_menu();
	char ch = _getch();
	if(!switcher(matrix, ch))
		return false;
	return true;
}

void print_menu()
{
	cout << "Press:"
		<< "1. to add a path"
		<< "2. to remove a path"
		<< "3. to find a path"
		<< "4. to print all"
		<< "5. to clear path list"
		<< "6. to clear screen"
		<< "ESC to exit";
}

bool switcher(matrix matrix, char ch)
{
	switch (ch)
	{
	case'1': add(matrix); break;
	case'2': _remove(matrix); break; //remove в си существует, удаляет файдпо имени
	case'3': find(matrix); break;
	case'4': print(matrix); break;
	case'5': clear(matrix); break;
	case'6': system("cls"); break;
	case 27: return false; break;
	}
	return true;
}

void add(matrix matrix)
{
	char ch;
	int srs, dest, dist;
	do
	{
		cout << "source-city (int number): ";
		cin >> srs;
		cout << "destination-sity (int number): ";
		cin >> dest;
		cout << "distance: ";
		cin >> dist;
		try 
		{
			matrix.add(srs, dest, dist);
			cout << "\npath added";
		}
		catch (char* exc)
		{
			if (strcmp(exc, "существующий маршрут"))
				cout << "path is already exist";
			else throw exc;
		}
		cout << "add more? (y/n)";
		do
			ch = _getch();
		while (ch != 'n' || ch != 'y');
	} while (ch != 'n');
}

void _remove(matrix matrix)
{
	if (matrix.is_empty())
	{
		cout << "empty";
		return;
	}
	char ch;
	int srs, dst;

	do 
	{
		cout << "source-city(int number): ";
		cin >> srs;
		cout << "destination city(int number): ";
		cin >> dst;

		try
		{
			matrix.remove(srs, dst);
			cout << "\npath removed";
		}
		catch (char* exc)
		{
			if (strcmp(exc, "несуществующий маршрут"))
				cout << "this path does not exist";
			else if (strcmp(exc, "пустой список"))
				/*уже предусмотрено*/;
			else throw exc;
		}

		cout << "remove more? (y/n)";
		do
			ch = _getch();
		while (ch != 'n' || ch != 'y');
	} while (ch != 'n');
}

