#include "../include/j48_node.h"

using namespace std;

J48Node::J48Node()
{
}

J48Node::~J48Node()
{
	for (struct J48Branch* branch : branches)
		delete branch;
}

J48Node::J48Node(int _attribute_index, attribute attr, float _impurity)
{


	attribute_index = _attribute_index;
	impurity = _impurity;
	is_leaf = false;
	//node_fanout = attr.getNumOfValues();
	//branches = J48Node_branch[node_fanout];

	for (std::string attr_value_name : attr)
	{
		J48Branch* new_branch = new J48Branch;
		new_branch->attribute_value_name = attr_value_name;
		branches.push_back(new_branch);
	}

}

void J48Node::setAsLeafNode(string _class_label_value)
{
	is_leaf = true;
	class_label_value = _class_label_value;

	//std::vector<J48Node_branch*>::iterator b = &branches.begin();

}
