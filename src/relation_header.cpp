#include "../include/relation_header.h"

using namespace std;

struct RelationHeader;

RelationHeader::RelationHeader()
{
}

RelationHeader::~RelationHeader()
{
}

RelationHeader::RelationHeader(AttributeList _all_attributes)
{
	all_attributes = _all_attributes;
}

int RelationHeader::getIndexOfAttribute(string attribute_name)
{
	return all_attributes.getIndexOfAttribute(attribute_name);
}

int RelationHeader::getNumOfColumns()
{
	return all_attributes.getNumOfAttributes();
}
