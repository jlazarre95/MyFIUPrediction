#pragma once
#include "relation_header.h"
#include "relation_table.h"

#include <string>

typedef struct RelationObj {

public:
	RelationObj();
	~RelationObj();
	RelationObj(std::string name, RelationHeader header, RelationTable table);
	int getIndexOfAttribute(std::string attribute_name);
	std::string getName() { return header.name; }
	AttributeList getAllAttributes();
	int getNumOfAttributes();
	int getNumOfRecords();
	void setTable(RelationTable _table);
	RelationHeader getHeader() { return header; }
	RelationTable getTable();
	RelationTable selectAll(int attribute_index, std::string attribute_value_name);

	Attribute operator[](int index) { return getAllAttributes()[index]; }
	std::string getAttributeName(int index) { return getAllAttributes()[index].name; }


private:
	RelationHeader header;
	RelationTable table;

} RelationObj;