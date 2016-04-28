#pragma once
#include "j48_node.h"

typedef struct j48_node_branch {

	j48_node_branch();
	~j48_node_branch();

	std::string attribute_value_name;
	float attribute_value_impurity;
	struct j48_node* next; // maximum of one node

} j48_node_branch;
