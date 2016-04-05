// matrix_menu.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "matrix.h"
#include "iostream"
#include "conio.h"

using namespace std;

bool menu(matrix&);
void print_menu();
bool switcher(matrix&, char);
void print(matrix&);
void add(matrix&);
void _remove(matrix&);
void clear(matrix&);
void find(matrix&);

int main()
{
	matrix matrix;
	do {} 
	while (menu(matrix));
    return 0;
}

bool menu(matrix& matrix)
{
	print_menu();
	char ch = _getch();
	if(!switcher(matrix, ch))
		return false;
	return true;
}

void print_menu() 
{
	cout << "Press:" << endl
		<< "1. to add a path" << endl
		<< "2. to remove a path" << endl
		<< "3. to find a path" << endl
		<< "4. to print all" << endl
		<< "5. to clear path list" << endl
		<< "6. to clear screen" << endl
		<< "ESC to exit" << endl;
}

bool switcher(matrix& matrix, char ch)
{
	switch (ch)
	{
	case'1': add(matrix); break;
	case'2': _remove(matrix); break; //remove в си существует, удаляет файл по имени
	case'3': find(matrix); break;
	case'4': print(matrix); break;
	case'5': clear(matrix); break;
	case'6': system("cls"); break;
	case 27: return false; break;
	}
	return true;
}

void print(matrix& matrix)
{
	if (matrix.is_empty())
	{
		cout << "empty" << endl;
		return;
	}
	matrix::iterator i(matrix);
	cout << "Paths:" << endl;
	while (!i.is_NULL())
	{
		cout << "from " << i.get_sourse() << " to " << i.get_destination()
			<< " with distance " << i.get_distance() << endl;
		++i;
	}
}

void add(matrix& matrix)
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
			cout << "path added" << endl;
		}
		catch (char* exc)
		{
			if (exc == "существующий маршрут")
				cout << "path is already exist" << endl;
			else throw exc;
		}
		cout << "add more? (y/n)" << endl;
		do
			ch = _getch();
		while (ch != 'n' && ch != 'y');
	} while (ch != 'n');
}

void _remove(matrix& matrix)
{
	if (matrix.is_empty())
	{
		cout << "empty" << endl;
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
			cout << "path removed" << endl;
		}
		catch (char* exc)
		{
			if (exc == "несуществующий маршрут")
				cout << "this path does not exist" << endl;
			else if (exc == "пустой список")
				/*уже предусмотрено*/;
			else throw exc;
		}

		cout << "remove more? (y/n)" << endl;
		do
			ch = _getch();
		while (ch != 'n' && ch != 'y');
	} while (ch != 'n');
}

void find(matrix& matrix)
{
	char ch;
	int srs, dest;
	do
	{
		cout << "source-city (int number): ";
		cin >> srs;
		cout << "destination-sity (int number): ";
		cin >> dest;

		int result = matrix.find(srs, dest);
		if (result != -1)
			cout << "\npath from " << srs << "to" << dest << ":  " << result;
		else
			cout << "\this npath does not exist";

		cout << "\nfind more? (y/n)";
		do
			ch = _getch();
		while (ch != 'n' || ch != 'y');
	} while (ch != 'n');
}

void  clear(matrix& matrix)
{
	char ch;
	cout << "\nare you sure? (y/n)";

	do
		ch = _getch();
	while (ch != 'n' || ch != 'y');

	if(ch == 'y')
		matrix.clear();
	else 
		return;
}
