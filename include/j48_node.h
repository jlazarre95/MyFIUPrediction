#pragma once

#include <string>
#include <vector>
#include "attribute.h"
#include "j48_node_branch.h"

//struct or class? struct: members public by default, class: members private by default

typedef struct j48_node {

	j48_node();
	j48_node(int _attribute_index, attribute attr, float _impurity);
	~j48_node();

	void setAsLeafNode(std::string _class_label_value);

	int attribute_index; //position of attribute in dataset_header 
	float impurity; //necessary?
	bool is_leaf;
	std::string class_label_value;
	std::vector<struct j48_node_branch*> branches;

	auto begin() -> decltype (branches.begin()) { return branches.begin(); }
	auto end() -> decltype (branches.end()) { return branches.end(); }


} j48_node;


