//#include "../../stdafx.h"
#include <iostream>
#include "../include/j48_decision_tree.h"
#include "../include/entropy.h" // delete later

using namespace std;

J48DecisionTree::J48DecisionTree()
{
	impurity_measure = new Entropy(); // default impurity_measure to Entropy object
	is_tree_built = false;

	// relation_obj not initialized
	// class_label not initialized

	//buildDecisionTree();
}

//J48DecisionTree::J48DecisionTree(std::string _class_label)
//{
//	impurity_measure = new Entropy(); // default impurity_measure to Entropy object
//	setClassLabel(_class_label);
//	// relation_obj not initialized
//}

//J48DecisionTree::J48DecisionTree(ImpurityMeasure * _impurity_measure, std::string _class_label)
//{
//	impurity_measure = _impurity_measure; // TODO: check if class of ImpurityMeasure object is concrete
//	setClassLabel(_class_label);
//	// relation_obj not initialized
//}

J48DecisionTree::J48DecisionTree(RelationObj _relation_obj, std::string _class_label)
{
	setRelation(_relation_obj);
	impurity_measure = new Entropy(); // default impurity_measure to Entropy object
	setClassLabel(_class_label);
	is_tree_built = false;
}

J48DecisionTree::J48DecisionTree(RelationObj _relation_obj, ImpurityMeasure * _impurity_measure, std::string _class_label)
{
	setRelation(_relation_obj);
	impurity_measure = _impurity_measure; // TODO: check if class of ImpurityMeasure object is concrete
	setClassLabel(_class_label);
	is_tree_built = false;
}


J48DecisionTree::~J48DecisionTree()
{
	delete root; 
	delete impurity_measure;
	//free all nodes!
}

void J48DecisionTree::setImpurityMeasure(ImpurityMeasure* _impurity_measure)
{
	impurity_measure = _impurity_measure;
}

void J48DecisionTree::recBuildSubtrees(J48Node* node, RelationTable table)
{
	//cout << *this << endl << endl;
	/* Build Rest of tree RECURSIVELY */

	int attribute_index = node->attribute_index;

	for (J48Branch* branch : *node)
	{
		string branch_name = branch->attribute_value_name; // name of attribute value
		RelationTable selected_rows = table.selectAll(attribute_index, branch_name); // update table, pass table to recursive call?
		
		//if no selected rows, use default value and continue
		if (selected_rows.getNumOfRows() == 0)
		{
			J48Node* leaf_node = new J48Node();
			leaf_node->setAsLeafNode(default_class_label_value);
			branch->next = leaf_node;
			continue;
		}
		bool is_class_label_shared = true;

		string shared_class_label_value = (*selected_rows.begin())[class_label_index];

		for (TableRow record : selected_rows)
		{
			if (record[class_label_index] != shared_class_label_value)
			{
				is_class_label_shared = false;
				break;
			}
		}

		if (is_class_label_shared == true)
		{/*build leaf node based on majority class... move onto next branch*/
			J48Node* leaf_node = new J48Node();
			leaf_node->setAsLeafNode(shared_class_label_value);
			branch->next = leaf_node;
			continue;
		}
		else
		{/*pick attribute to split (best one) based on branch -- impurity measure's job, pass node and table to recursive call*/
			float best_attribute_impurity;
			int best_attribute_index = impurity_measure->findBestSplitOnBranch(class_label_index, attribute_index, selected_rows, &best_attribute_impurity);
			
			/* If there are no more attributes that can be used to split... */
			if (best_attribute_index < 0)
			{
				TableColumn col = selected_rows.getColumn(class_label_index);
				string majority_attribute_value = col.getMajorityValue();
				J48Node* leaf_node = new J48Node();
				leaf_node->setAsLeafNode(majority_attribute_value);
				branch->next = leaf_node;
				continue;
			}
			
			Attribute best_attribute = relation_obj[best_attribute_index];
			J48Node* intermediate_node = new J48Node(best_attribute_index, best_attribute, best_attribute_impurity);
			branch->next = intermediate_node;
			recBuildSubtrees(intermediate_node, selected_rows);
		}

	}

	return;
}

void J48DecisionTree::buildDecisionTree()
{
	//if (impurity_measure != NULL)
	//	cout << "not null\n";
	//else cout << "null\n";

	impurity_measure->setRelationHeader(relation_obj.getHeader());

	/* Find first attribute to split on */
	float attribute_impurity;
	int best_initial_attribute_index = impurity_measure->findBestInitalSplit(class_label_index, relation_obj.getTable(), &attribute_impurity);
	Attribute best_initial_attribute = relation_obj[best_initial_attribute_index];

	root = new J48Node(best_initial_attribute_index, best_initial_attribute, attribute_impurity);

	//cout << "Entropy of Best Attribute Split (" << relation_obj.getAttributeName(best_initial_attribute_index) << "): " << root->impurity << endl;

	recBuildSubtrees(root, relation_obj.getTable());
	is_tree_built = true;

	return;

}

string J48DecisionTree::predict(TableRow record)
{
	if(is_tree_built == false)
		buildDecisionTree();

	string predicted_class_label = recPredict(record, root);
	return predicted_class_label;
}

//template <class InputIterator>
//string J48DecisionTree::predictIgnore(TableRow record, InputIterator first, InputIterator last)
//{
//	impurity_measure->setIgnoredAttributes(first, last);
//
//	buildDecisionTree();
//
//	J48Node* curr_node = root;
//	string predicted_class_label = recPredict(record, root);
//
//	return predicted_class_label;
//}

std::string J48DecisionTree::recPredict(TableRow record, J48Node* curr_node)
{

	if (curr_node->is_leaf == true)
		return curr_node->class_label_value;

	int curr_node_attribute_index = curr_node->attribute_index;

	string record_attribute_value = record[curr_node_attribute_index];

	J48Branch* next_branch = NULL;

	for (J48Branch* branch : *curr_node)
	{
		if (branch->attribute_value_name == record_attribute_value)
		{
			next_branch = branch;
			break;
		}
	}

	if (next_branch == NULL)
	{
		next_branch = curr_node->branches[(curr_node->branches.size())/2]; // return default value, or pick middle branch?
	}

	J48Node* next_node = next_branch->next;

	string predicted_class_label = recPredict(record, next_node);

	return predicted_class_label;

}



static void operatorHelper(RelationObj & _rel_obj, J48Node * node, int num_of_spaces)
{

	if (node == NULL)
	{
		cout << "NULL\n";
		return;
	}

	if (node->is_leaf == true)
	{
		cout << "" << node->class_label_value << "" << endl;
		return;
	}

	int attr_index = node->attribute_index;
	const string& attr_name = _rel_obj.getAttributeName(attr_index);

	cout << "" << attr_name << ":\n";

	//for (int i = 0; i < num_of_spaces; i++)
	//	cout << " ";

	int branch_count = 0;

	for (J48Branch* branch : *node)
	{
		for (int i = 0; i < num_of_spaces; i++)
			cout << " ";

		cout << "[" << branch_count << "]" << "----" << branch->attribute_value_name << "----> ";

		if (branch->next == NULL)
		{
			cout << endl;
			return;
		}
		J48Node* next_node = branch->next;
		branch_count++;

		operatorHelper(_rel_obj, next_node, num_of_spaces + 5); // indentation space after each attribute name

	}

	return;

}

ostream& operator<<(ostream& os, const J48DecisionTree& jdt) {

	RelationObj rel_obj = jdt.relation_obj;
	J48Node* root = jdt.root;

	if (root == NULL)
		std::cout << "NULL\n";
	else
	{
		cout << "ROOT: ";
		operatorHelper(rel_obj, root, 3);
	}

	return os;

}

//float J48DecisionTree::getClassLabelImpurity()
//{
//	return impurity_measure->getClassLabelImpurity();
//}
