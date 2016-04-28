#pragma once
#include "attribute_list.h"
#include <vector>

struct RelationObj;

typedef struct RelationHeader{

public:
	RelationHeader();
	~RelationHeader();
	RelationHeader(AttributeList _all_attributes);
	friend RelationObj;

	AttributeList all_attributes;
	int getIndexOfAttribute(std::string attribute_name);
	int getNumOfColumns();

private:
	std::string name;

} RelationHeader;