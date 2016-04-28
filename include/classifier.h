#pragma once
#include "relation_obj.h"
#include <string>

#define RECORD_SIZE_ERROR -1;
#define  ATTRIBUTE_TYPE_MISMATCH_ERROR -2;

	class Classifier
	{
	public:
		int class_label_index;
		RelationObj relation_obj;
		/*	int num_of_records;
		int num_of_attributes;*/

		Classifier();
		Classifier(std::string _class_label) { setClassLabel(_class_label); }
		~Classifier();
		//TODO: create constructor to init relation and class label

		int setRelation(RelationObj _relation_obj);
		void setClassLabel(std::string _class_label);
		virtual std::string predict(TableRow record) = 0;
		//TODO: create function validaterelation() that checks for valid attribute names, repeated attribute names, etc.

		//template <class InputIterator>
		//virtual std::predictIgnore(TableRow record, InputIterator first, InputIterator last) = 0;

	protected:
		std::string class_label;
		int validateRecord(TableRow record);
		//std::vector<int> ignored_attribute_indexes;


	};
