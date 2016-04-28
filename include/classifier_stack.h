#pragma once
#include "classifier.h"

class ClassifierStack : public Classifier
{
public:
	ClassifierStack();

	template <class InputIterator>
	ClassifierStack(InputIterator first, InputIterator last)
	{
		for (InputIterator it = first; it != last; it++)
			push_back(*it);
	}

	void push_back(Classifier* new_classifier);
	void pop_back();

	std::string predict(TableRow record);
	TableColumn predictAll(RelationTable table);

	~ClassifierStack();

private:
	std::vector<Classifier*> all_classifiers;

};

