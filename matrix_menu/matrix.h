#pragma once
#include <string>

using namespace std;

class matrix
{
	struct node
	{
		int col;
		int dist;
		node* next_col;
	};

	struct mark
	{
		int row;
		mark* next_row;
		node* first_col;
	};

	mark* first;

	mark* r_find(int);
	node* c_find(int, mark*);


public:
	matrix();
	~matrix();

	bool is_empty();
	void clear();
	void add(int, int, int);
	void remove(int, int);
	int find(int, int);
};

