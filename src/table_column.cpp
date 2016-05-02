#include "../include/table_column.h"

using namespace std;

TableColumn::TableColumn()
{
}

TableColumn::~TableColumn()
{
}

vector<int> TableColumn::compareValues(TableColumn other)
{
	vector<int> indexes_of_diff_values;
	int this_col_size = size();
	int other_col_size = other.size();

	if (this_col_size != other_col_size)
		exit(-1); // throw exception; change later

	for (int i = 0; i < this_col_size; i++)
	{
		if ((*this)[i] != other[i])
			indexes_of_diff_values.push_back(i);
	}

	return indexes_of_diff_values;
}

