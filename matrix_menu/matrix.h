#pragma once

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


	class iterator
	{
		mark* row;
		node* column;
	public:
		iterator(matrix&);
		friend const iterator operator++(iterator&);
		int get_sourse();
		int get_destination();
		int get_distance();
		bool is_NULL();
	};	
};

