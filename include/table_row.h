#pragma once
#include "table_slice.h"

struct RelationTable;

typedef struct TableRow : public TableSlice
{
public:
	TableRow();
	template <class InputIterator>
	TableRow(InputIterator first, InputIterator last) : TableSlice(first, last) {}; // use template
	~TableRow();
	friend RelationTable;
} TableRow;

