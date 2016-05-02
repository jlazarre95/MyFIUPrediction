#pragma once
#include "classifier.h"

class AdaBoost : public Classifier
{
public:
	AdaBoost();
	~AdaBoost();

	int setRelation(RelationObj _training_data);
	std::string predict(TableRow record);
	void push_back(Classifier* new_classifier);
	//void pop_back();


private:
	std::vector<Classifier*> all_base_classifiers; // list of base classifier
	RelationObj training_data;
	std::vector<float> all_record_weights; // weights for each record to classify
	static const float weight_increase_factor;
	std::vector<TableColumn> all_predicted_class_labels_list; // a list of predicted values from each base classifier
	std::vector<std::string> boosted_predicted_values; // result predicted values from boosting

	void buildModel();
	int sampleRecords();


};

