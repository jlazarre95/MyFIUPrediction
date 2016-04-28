#pragma once
#include "j48_node.h"

typedef struct J48Branch {

	std::string attribute_value_name;
	float attribute_value_impurity;
	struct J48Node* next; // maximum of one node

	J48Branch();
	~J48Branch();

} J48Branch;
