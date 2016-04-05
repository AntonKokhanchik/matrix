#include "stdafx.h"
#include "matrix.h"

matrix::matrix()
{
	first = NULL;
}

matrix::~matrix()
{
	clear();
}

// ��������� �� �������
bool matrix::is_empty()
{
	if (first == NULL)
		return true;
	return false;
}

//������� ������ ���������
void matrix::clear()
{
	while (first)
	{
		mark* deleting_row = first;
		while (deleting_row->first_col)
		{
			node* deleting_node = deleting_row->first_col;
			deleting_row->first_col = deleting_node->next_col;
			delete deleting_node;
		}
		first = deleting_row->next_row;
		delete deleting_row;
	}
}

// ��������� ����� ������� ����� ��������
// ����������� ���������� ��� ������������ ��������
void matrix::add(int ts, int td, int dist)
{
	if (is_empty())
	{
		mark* m = new mark();
		m->next_row = NULL;
		m->row = ts;

		node* n = new node();
		n->col = td;
		n->dist = dist;
		n->next_col = NULL;
		m->first_col = n;

		first = m;
		return;
	}

	mark* r = r_find(ts);
	mark* m = new mark;
	m->row = ts;

	if (r)
	{
		if (r->row == ts)
		{
			delete m;
			m = r;
			node* c = c_find(td, m);
			if (c)
			{
				if (c->col == td)
					throw "������������ �������";
			}
		}
		else
		{
			m->next_row = r->next_row;
			r->next_row = m;
			m->first_col = NULL;
		}
	}
	else
	{
		m->next_row = first;
		first = m;
		m->first_col = NULL;
	}

	node* tmp = new node();
	tmp->col = td;
	tmp->dist = dist;

	node* c = c_find(td, m);
	if (!c)
	{
		tmp->next_col = m->first_col;
		m->first_col = tmp;
	}
	else
	{
		tmp->next_col = c->next_col;
		c->next_col = tmp;
	}
}

// ���������� ��������� �� ������� ��� ���������� �����-�������� 
//(NULL ��� ��������)
matrix::mark* matrix::r_find(int i)
{
	if (is_empty())
		return NULL;
	mark* tmp = first;
	if (tmp->row > i)
		return NULL;
	while (tmp->next_row != NULL && tmp->next_row->row <= i)
		tmp = tmp->next_row;
	return tmp;								//�����. ��������� �� �������� < ��� = i ��� NULL
}

//���������� ��������� �� ������� ��� ���������� �����-����������
//� ������� ��������� (NULL ��� ��������)
matrix::node* matrix::c_find(int i, mark* m)
{
	if (!m || !m->first_col)
		return NULL;
	node* tmp = m->first_col;
	if (tmp->col > i)
		return NULL;
	while (tmp->next_col != NULL && tmp->next_col->col <= i)
		tmp = tmp->next_col;
	return tmp;
}

// ������� ������� �� ������� ��������� � ����������
// ���������, ���� ������ �������� ���
// ����� ������� �����, ���� �� ��������� �� �������
// ���������� ���� ������ ���� ��� ������� �� ���������
void matrix::remove(int ts, int td)
{
	if (is_empty())
		throw "������ ������";
	mark* r = r_find(ts);
	node* c = c_find(td, r);

	if (!r || !c || r->row != ts || c->col != td)
		throw "�������������� �������";
	else
	{
		node* tmp2 = r->first_col;
		if (c != tmp2)
		{
			while (tmp2->next_col->col < c->col)
				tmp2 = tmp2->next_col;
			tmp2->next_col = c->next_col;
		}
		else
			r->first_col = c->next_col;
		delete c;

		if (r->first_col != NULL)
			return;

		mark* tmp1 = first;
		if (r != tmp1)
		{
			while (tmp1->next_row->row < r->row)
				tmp1 = tmp1->next_row;
			tmp1->next_row = r->next_row;
		}
		else
			first = r->next_row;
		delete r;
	}
}

// ���������� ����� �������� �� ������� ��������� � ����������
// -1 ���� �������� ���
int matrix::find(int s, int d)
{
	mark* row = r_find(s);
	if (!row || row->row != s)
		return -1;
	node* col= c_find(d, row);
	if (!col || col->col != d)
		return -1;
	return col->dist;
}

// ������ ��������, ����������� �� ������ ������� �������
// (������ �������� ������, ������ �������� �������)
matrix::iterator::iterator(matrix& matrix)
{
	row = matrix.first;
	column = row->first_col;
}

// ���������� ����� ������-��������� (����� ������ �������)
int matrix::iterator::get_sourse()
{
	if(row)
		return row->row;
	throw "��������� � NULL";
}

// ���������� ����� ������-���������� (����� ������� �������)
int matrix::iterator::get_destination()
{
	if(column)
		return column->col;
	throw "��������� � NULL";
}

// ���������� ���������� ����� ��������
int matrix::iterator::get_distance()
{
	if (column)
		return column->dist;
	throw "��������� � NULL";
}

// ���������� true, ���� ��������� �� NULL 
// (����� �� ����� �������)
bool matrix::iterator::is_NULL()
{
	if (row == NULL)
		return true;
	return false;
}

// ���������� ��������� ������� �������
// (������� ��� ���������� ������, ����� ������������� �� ��������� ������)
const matrix::iterator operator++(matrix::iterator& i)
{
	if (i.is_NULL())
		return i;
	if (i.column->next_col)
	{
		i.column = i.column->next_col;
		return i;
	}
	else
		if (i.row->next_row)
		{
			i.row = i.row->next_row;
			i.column = i.row->first_col;
			return i;
		}
		else
		{
			i.row = NULL;
			i.column = NULL;
		}
}