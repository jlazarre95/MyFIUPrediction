#include "stdafx.h"

/*
 
 THINGS TO DO:
	-Use namespaces!
 
 */

/* 
Schema for student transcript

@ATTRIBUTE transcript_id NUMERIC
@ATTRIBUTE course_num STRING
@ATTRIBUTE semester_taken STRING
@ATTRIBUTE grade_received{ A,A - ,B + ,B,B - ,C + ,C,C - ,D + ,D,D - ,F,P,INC,I }
@ATTRIBUTE passed{ t,f }
@ATTRIBUTE course_name STRING
@ATTRIBUTE category STRING
*/

/* Debug function */
static void printVec(std::vector<std::string> string_vector)
{
  int i = 0;

  for (std::string str : string_vector)
    std::cout << "[" << str << "] ";
  std::cout << std::endl;
  return;

}

int main(int argc, char* argv[])
{
	using namespace std;

	
	DataFileParser* parser = new ArffParser();
	parser->openFile("dat/student_transcript.arff");
	parser->parseFile();
	relationObj relation_obj = parser->getRelationObj();

	string class_label = "grade";
	//cout << "Initializing Decision Tree...\n";
	J48DecisionTree* classifier = new J48DecisionTree(relation_obj, class_label); 
	string def = classifier->relation_obj.getTable().getColumn(relation_obj.getIndexOfAttribute(class_label)).getMajorityValue();
	classifier->setDefaultClassLabel(def);

	vector<string> ignored_attributes = { "transcript_id"/*, "course_name", "tc_credits" /*"semester_taken",*/ /*"course_num"*/};
	
	 /* Predict "grade_received" class label for record */
	vector<string> record_values = 
	 { "8", "COP 5725", "Fall 2016", "?" , "?" , "Principles of Database Management Systems", "Computer Programming" };

	tableRow record = tableRow(record_values.begin(), record_values.end());
	string predicted_class_label = classifier->predict(record);

	/* Print record */
	cout << "\nPredicted class label of record (" << record << "): " << predicted_class_label;

	delete classifier;


	return 0;
}

