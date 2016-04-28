#pragma once

#include <string>
#include <vector>
#include "attribute.h"
#include "j48_branch.h"

//struct or class? struct: members public by default, class: members private by default

typedef struct J48Node {

	J48Node();
	J48Node(int _attribute_index, Attribute attr, float _impurity);
	~J48Node();

	void setAsLeafNode(std::string _class_label_value);

	int attribute_index; //position of attribute in dataset_header 
	float impurity; //necessary?
	bool is_leaf;
	std::string class_label_value;
	std::vector<struct J48Branch*> branches;

	auto begin() -> decltype (branches.begin()) { return branches.begin(); }
	auto end() -> decltype (branches.end()) { return branches.end(); }


} J48Node;


