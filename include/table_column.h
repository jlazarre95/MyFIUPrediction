#pragma once
#include "table_slice.h"


struct RelationTable;

typedef struct TableColumn : public TableSlice
{

public:
	friend RelationTable;

	TableColumn();
	template <class InputIterator>
	TableColumn(InputIterator first, InputIterator last) : tableSlice(first, last) {}; // use template
	~TableColumn();

} TableColumn;

