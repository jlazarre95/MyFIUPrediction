#pragma once
#include "../include/impurity_measure.h"

class Entropy: public ImpurityMeasure
{

public:

	Entropy();
	~Entropy();
	float calculateImpurity(int attribute_index, RelationTable table);
	int findBestInitalSplit(int class_label_index, RelationTable table, float* attribute_impurity = NULL);
	int findBestSplitOnBranch(int class_label_index, int attribute_index_of_value, RelationTable table, float* attribute_impurity = NULL);

private: 
	float calculateEntropy(int attribute_index, RelationTable table);
	float calculateConditionalEntropy(int of_attribute_index, int on_attribute_index, RelationTable table);
	inline float informationGain(float entropy1, float entropy2) { return entropy1 - entropy2; }


};