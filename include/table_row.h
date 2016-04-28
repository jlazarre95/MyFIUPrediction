#pragma once
#include "table_slice.h"

struct RelationTable;

typedef struct TableRow : public TableSlice
{
public:
	friend RelationTable;

	TableRow();
	template <class InputIterator>
	TableRow(InputIterator first, InputIterator last) : TableSlice(first, last) {}; // use template
	~TableRow();

} TableRow;

