#include "../include/j48_node.h"

using namespace std;

j48_node::j48_node()
{
}

j48_node::~j48_node()
{
	for (struct j48_node_branch* branch : branches)
		delete branch;
}

j48_node::j48_node(int _attribute_index, attribute attr, float _impurity)
{


	attribute_index = _attribute_index;
	impurity = _impurity;
	is_leaf = false;
	//node_fanout = attr.getNumOfValues();
	//branches = j48_node_branch[node_fanout];

	for (std::string attr_value_name : attr)
	{
		j48_node_branch* new_branch = new j48_node_branch;
		new_branch->attribute_value_name = attr_value_name;
		branches.push_back(new_branch);
	}

}

void j48_node::setAsLeafNode(string _class_label_value)
{
	is_leaf = true;
	class_label_value = _class_label_value;

	//std::vector<j48_node_branch*>::iterator b = &branches.begin();

}
