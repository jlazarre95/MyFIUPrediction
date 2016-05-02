#include "../include/ada_boost.h"
#include <cmath>
#include <ctime>
//#include <random>

using namespace std;

const float AdaBoost::weight_increase_factor = 1.00;

AdaBoost::AdaBoost()
{
}


AdaBoost::~AdaBoost()
{
	for (Classifier* base_classifier : all_base_classifiers)
	{
		delete base_classifier;
	}
}

int AdaBoost::setRelation(RelationObj _training_data)
{
	Classifier::setRelation(_training_data);
	int num_of_records = _training_data.getNumOfRecords();
	
	float initial_record_weight = 1 / (float)num_of_records; // each record has an initial weight of 1/N; N is the total number of records

	for (int i = 0; i < num_of_records; i++)
	{
		all_record_weights.push_back(initial_record_weight);
	}

	buildModel();

	return 0;
}

void AdaBoost::push_back(Classifier* new_classifier)
{
	all_base_classifiers.push_back(new_classifier);

	return;
}

void AdaBoost::buildModel()
{
	RelationHeader adaboost_header = training_data.getHeader(); // header for all base classifiers
	RelationTable adaboost_table = training_data.getTable(); 
	string relation_name = training_data.getName();
	TableColumn training_data_class_labels = adaboost_table.getColumn(class_label_index);

	int num_of_records = adaboost_table.getNumOfRows();

	for (Classifier* base_classifier : all_base_classifiers)
	{
		RelationTable base_classifier_table; // training data for one base classifier
		for (int i = 0; i < num_of_records; i++)
		{
			int index_of_selected_record = sampleRecords();
			TableRow selected_record = adaboost_table.getRow(index_of_selected_record);
			base_classifier_table.push_back(selected_record);
		}

		RelationObj base_classifier_training_data = RelationObj(relation_name, adaboost_header, base_classifier_table);

		base_classifier->setRelation(base_classifier_training_data);
		base_classifier->setClassLabel(class_label);

		TableColumn predicted_class_labels = base_classifier->predictAll(adaboost_table);
		all_predicted_class_labels_list.push_back(predicted_class_labels);
		vector<int> indexes_of_misclassified_records = training_data_class_labels.compareValues(predicted_class_labels);

		/* If misclassification error of classifier is ever > 50%, reduce all weights to 1/N and start buildModel() again */
		if (indexes_of_misclassified_records.size() > ceil(num_of_records / (float) 2))
		{
			cout << "Misclassification error over 50%, resetting weights...\n";
			int num_of_records = training_data.getNumOfRecords();
			float initial_record_weight = 1 / (float) num_of_records; // each record has an initial weight of 1/N; N is the total number of records

			for (int i = 0; i < num_of_records; i++)
			{
				all_record_weights.push_back(initial_record_weight);
			}

			cout << "Rebuilding model...\n";
			buildModel();
			return;
		}

		/* Change weights of records */
		for (int index_of_misclassified_record : indexes_of_misclassified_records)
		{
			all_record_weights[index_of_misclassified_record] += weight_increase_factor;
		}

	}

	cout << "Successfully built AdaBoost Model!\n";

	return;
}

std::string AdaBoost::predict(TableRow record)
{
	TableSlice all_predicted_class_labels;

	for (Classifier* base_classifier : all_base_classifiers)
	{
		string predicted_class_label = base_classifier->predict(record);
		all_predicted_class_labels.push_back(predicted_class_label);
	}

	string majority_class_label = all_predicted_class_labels.getMajorityValue();

	return majority_class_label;
}


int AdaBoost::sampleRecords()
{
	float sum_of_weights = 0.0;

	for (int i = 0; i < all_record_weights.size(); i++)
	{
		sum_of_weights += all_record_weights[i];
	}

	int num_of_decimal_places;
	int max_random_weight = parseFloatAsInt(sum_of_weights, &num_of_decimal_places); // e.g. 1.0000 -> 1 or .315 -> 315

	srand(time(NULL)); // seed the random number generator
	float random_weight = rand() % max_random_weight; // implicitly converts result from int to float

	for (int j = 0; j < num_of_decimal_places; j++)
		random_weight / 10.0; // move decimal place to be used with weights

	for (int k = 0; k < all_record_weights.size(); k++)
	{
		if (all_record_weights[k] >= random_weight) 
			return k; // return index of selected record
		
		random_weight -= all_record_weights[k];

	}

	return -1;
}

/* Private function */
int parseFloatAsInt(float _x, int* num_of_decimal_places = NULL) 
{
	float x = _x;

	if(num_of_decimal_places != NULL)
		*num_of_decimal_places = 0;

	int int_result; // if x == 721.429 -> 721429
	float float_result; 

	float frac_part; // buffer; if x == 721.429 ->  .429
	
	frac_part = modf(x, &float_result); // get whole and fraction parts from x

	while (true)
	{
		if (frac_part == 0.0)
		{
			int_result = floor(float_result);
			return int_result;
		}
		
		x * 10.0;
		if (num_of_decimal_places != NULL)
			(*num_of_decimal_places)++;

		frac_part = modf(x, &float_result); // get whole and fraction parts from x
	}

	return INT_MIN;
}



