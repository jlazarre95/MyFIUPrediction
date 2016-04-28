#pragma once
#include <iostream>
#include "classifier.h"
#include "impurity_measure.h"
#include "j48_node.h"

/*
TODO: deal with decision trees that don't cover all rules
*/

	class J48DecisionTree : public Classifier
	{
	public:
		J48DecisionTree();
		/*J48DecisionTree(std::string _class_label);
		J48DecisionTree(ImpurityMeasure* _impurity_measure, std::string _class_label);*/
		J48DecisionTree(RelationObj _relation_obj, std::string _class_label);
		J48DecisionTree(RelationObj _relation_obj, ImpurityMeasure* _impurity_measure, std::string _class_label);
		~J48DecisionTree();

		void setImpurityMeasure(ImpurityMeasure* _impurity_measure);
		void buildDecisionTree();
		virtual std::string predict(TableRow record);

		template <class InputIterator>
		std::string predictIgnore(TableRow record, InputIterator first, InputIterator last)
		{
			std::vector<int> ignored_attribute_indexes;

			for (InputIterator it = first; it != last; it++)
			{
				std::string ignored_attribute_name = *it;
				int ignored_attribute_index = relation_obj.getIndexOfAttribute(ignored_attribute_name);
				ignored_attribute_indexes.push_back(ignored_attribute_index);
			}
			
			impurity_measure->setIgnoredAttributes(ignored_attribute_indexes.begin(), ignored_attribute_indexes.end());

			if(is_tree_built == false)
				buildDecisionTree();

			std::string predicted_class_label = recPredict(record, root);

			return predicted_class_label;
		}

		template <class InputIterator>
		TableColumn predictAllIgnore(RelationTable table, InputIterator first, InputIterator last)
		{
			TableColumn all_predicted_values;

			for (TableRow record : table)
			{
				string predicted_value = predictIgnore(record, first, last);
				all_predicted_values.push_back(predicted_value);
			}

			return all_predicted_values;
		}

		void setDefaultClassLabel(std::string _default_class_label_value) { default_class_label_value = _default_class_label_value; }
		//float getClassLabelImpurity();

		void operator<<(int i) { return; }
		friend std::ostream& operator<<(std::ostream& os, const J48DecisionTree& jdt);

	protected:
		J48Node* root;
		//int fanout;
		ImpurityMeasure* impurity_measure;
		std::string default_class_label_value;
		bool is_tree_built;

		void recBuildSubtrees(J48Node* node, RelationTable table);
		/* virtual? */ std::string recPredict(TableRow record, J48Node* curr_node);

		//static void operatorHelper(RelationObj& _rel_obj, J48Node* node, int num_of_spaces);

		std::string class_label;

	};
