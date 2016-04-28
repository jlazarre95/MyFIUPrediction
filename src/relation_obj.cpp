#include "../include/relation_obj.h"

using namespace std;

RelationObj::RelationObj()
{
}

RelationObj::~RelationObj()
{
}

RelationObj::RelationObj(std::string _name, RelationHeader _header, RelationTable _table)
{
	header = _header;
	header.name = _name;
	table = _table;
}

int RelationObj::getIndexOfAttribute(string attribute_name)
{
	return header.getIndexOfAttribute(attribute_name);
}

AttributeList RelationObj::getAllAttributes()
{
	return header.all_attributes;
}

int RelationObj::getNumOfAttributes()
{
	return header.getNumOfColumns();
}

int RelationObj::getNumOfRecords()
{
	return table.getNumOfRows();
}

void RelationObj::setTable(RelationTable _table)
{
	table = _table;
}

RelationTable RelationObj::getTable()
{
	return table;
}

RelationTable RelationObj::selectAll(int attribute_index, std::string attribute_value_name)
{
	return table.selectAll(attribute_index, attribute_value_name);
}

//const RelationHeader& relation::getHeader()
//{
//	return header;
//}
//
//const relationData& relation::getData()
//{
//	return data;
//}
