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

// проверяет на пустоту
bool matrix::is_empty()
{
	if (first == NULL)
		return true;
	return false;
}

//очищает список маршрутов
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

// добавляет новый маршрут между городами
// выбрасывает искоючение при существующем маршруте
void matrix::add(int ts, int td, int dist)
{
	if (is_empty())
	{
		mark* m_tmp = new mark();
		m_tmp->next_row = NULL;
		m_tmp->row = ts;

		node* n_tmp = new node();
		n_tmp->col = td;
		n_tmp->dist = dist;
		n_tmp->next_col = NULL;
		m_tmp->first_col = n_tmp;

		first = m_tmp;
		return;
	}
	mark* r = r_find(ts);
	mark* m;

	if (r)
	{
		if (r->row == ts)
		{
			m = r;
			node* c = c_find(td, m);
			if (c)
			{
				if (c->col == td)
					throw "существующий маршрут";
			}
		}
		else
		{
			m = new mark();
			m->next_row = r->next_row;
			r->next_row = m;
		}
	}
	else
	{
		m->next_row = first;
		first = m;
	}

	node* tmp = new node();
	tmp->col = ts;
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

// возвращает указатель на искомый или предыдущий город-источник 
//(NULL для меньшего)
matrix::mark* matrix::r_find(int i)
{
	if (is_empty())
		return NULL;
	mark* tmp = first;
	if (tmp->row >= i)
		return NULL;
	while (tmp->next_row != NULL && tmp->next_row->row <= i)
		tmp = tmp->next_row;
	return tmp;								//возвр. указатнль на значение < или = i или NULL
}

//возвращает указатель на искомый или предыдущий город-назначение
//у данного источника (NULL для меньшего)
matrix::node* matrix::c_find(int i, mark* m)
{
	if (!m || !m->first_col)
		return NULL;
	node* tmp = m->first_col;
	if (tmp->col >= i)
		return NULL;
	while (tmp->next_col != NULL && tmp->next_col->col <= i)
		tmp = tmp->next_col;
	return tmp;
}

// удаляет маршрут по входным источнику и назначению
// исключеие, если такого маршрута нет
//также удаляет метку, если та указывает на пустоту
// исключение если список пуст или элемент не уществует
void matrix::remove(int ts, int td)
{
	if (is_empty())
		throw "пустой список";
	mark* r = r_find(ts);
	node* c = c_find(td, r);

	if (!r || !c || r->row != ts || c->col != td)
		throw "несуществующий маршрут";
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

// возвращает длину маршрута по входным источнику и назначению
// -1 если маршрута нет
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