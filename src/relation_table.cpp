#include "../include/relation_table.h"

using namespace std;

struct RelationTable;

RelationTable::RelationTable()
{
}

RelationTable::~RelationTable()
{
}

//template <class InputIterator>
//RelationTable::RelationTable(InputIterator first, InputIterator last) // use template
//{
//	setAllRows(first, last);
//}

TableRow RelationTable::getRow(int index)
{
	return all_rows[index];
}

TableColumn RelationTable::getColumn(int index)
{
	TableColumn column;

	for (TableRow row : all_rows)
		column.push_back(row[index]);

	return column;
}

void RelationTable::push_back(TableRow row)
{
	all_rows.push_back(row);
}

RelationTable RelationTable::selectAll(int attribute_index, std::string attribute_value_name)
{
	RelationTable result;
	for (TableRow record : all_rows)
		if (record[attribute_index] == attribute_value_name)
			result.push_back(record);

	return result;
}

int RelationTable::getNumOfRows()
{
	return all_rows.size();
}

//template <class InputIterator>
//void RelationTable::setAllRows(InputIterator first, InputIterator last)
//{
//
//	for (InputIterator table_iterator = first; table_iterator != last; table_iterator++)
//	{
//		TableRow new_row;
//		decltype(*table_iterator) record = *table_iterator;
//
//		for (string value : record) 
//			new_row.push_back(value);
//
//		all_rows.push_back(new_row);
//
//	}
//
//	return;
//}


//int relationData::getSize()
//{
//	return size;
//}
//
//vector<vector<string>> relationData::getRecords()
//{
//	return records;
//}
