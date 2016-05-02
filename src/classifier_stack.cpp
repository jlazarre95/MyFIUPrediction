#include "../include/classifier_stack.h"

using namespace std;

ClassifierStack::ClassifierStack()
{
}

ClassifierStack::~ClassifierStack()
{
	for (Classifier* classifier : all_classifiers)
	{
		delete classifier;
	}
}


void ClassifierStack::push_back(Classifier* new_classifier)
{
	all_classifiers.push_back(new_classifier);

	return;
}

void ClassifierStack::pop_back()
{
	Classifier* last_classifier = all_classifiers.back();
	all_classifiers.pop_back();
	delete last_classifier;

	return;

}

string ClassifierStack::predict(TableRow record)
{
	TableColumn all_predicted_class_labels;

	for (Classifier* classifier : all_classifiers)
	{
		string predicted_class_label = classifier->predict(record);
		all_predicted_class_labels.push_back(predicted_class_label);

	}

	string majority_class_label = all_predicted_class_labels.getMajorityValue();

	return majority_class_label;

}

TableColumn ClassifierStack::predictAll(RelationTable table)
{
	TableColumn all_predicted_class_labels;

	for (TableRow record : table)
	{
		string predicted_class_label = predict(record);
		all_predicted_class_labels.push_back(predicted_class_label);
	}

	return all_predicted_class_labels;
	
}

