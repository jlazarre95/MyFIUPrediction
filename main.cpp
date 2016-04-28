/*
 
THINGS TO DO:
-Use namespaces!
 
 */

/* 
Schema for student transcript

@ATTRIBUTE transcript_id NUMERIC
@ATTRIBUTE course_num STRING
@ATTRIBUTE semester_taken STRING
@ATTRIBUTE grade_received{ A,A-,B+,B,B-,C+,C,C-,D+,D,D-,F,P,INC,I }
@ATTRIBUTE passed{ t,f }
@ATTRIBUTE course_name STRING
@ATTRIBUTE category STRING
*/

#include "main_dependencies.h"

#define CLASS_LBL "grade_received"
#define IGNORED_ATTRS std::vector<std::string>({ "transcript_id", "course_name"/*, "tc_credits" /*"semester_taken",*/ /*"course_num"*/ })

std::vector<std::string> record_values;

/* Debug function */
static void printVec(std::vector<std::string> string_vector)
{
  int i = 0;

  for (std::string str : string_vector)
    std::cout << "[" << str << "] ";
  std::cout << std::endl;
  return;

}

/* Function to create a record of tableRow type using a vector of strings */
TableRow createRecord(std::vector<std::string> record_values)
{
	TableRow record = TableRow(record_values.begin(), record_values.end());

	return record;
}

int main(int argc, char* argv[])
{
	using namespace std;

	string class_label = CLASS_LBL;
	vector<string> ignored_attributes = IGNORED_ATTRS;

	/* Parse file and get relationObj */
	cout << "Initializing parser object...\n";
	DataFileParser* parser = new ArffParser();
	cout << "Opening file...\n";
	parser->openFile("dat/student_transcript.arff");
	
	cout << "Parsing file...\n";
	parser->parseFile();
	cout << "Done parsing file...\n";
	
	RelationObj relation_obj = parser->getRelationObj();
	parser->closeFile();
	cout << "File successfully closed...\n";

	/* Initialize classifier */
	cout << "Initializing Decision Tree...\n";
	J48DecisionTree* classifier = new J48DecisionTree(relation_obj, class_label); 

	/* Set up default value based on class label (picks majority value from class label column) */
	cout << "Setting default value...\n";
	int class_label_index = relation_obj.getIndexOfAttribute(class_label); // get index of class label
	RelationTable table = classifier->relation_obj.getTable(); // retrieve table

	TableColumn class_label_column = table.getColumn(class_label_index); // get column of class label
	string default_class_label = class_label_column.getMajorityValue(); // get majority value of class label (e.g. "C+")

	classifier->setDefaultClassLabel(default_class_label);
	cout << "Default value set to " << default_class_label << "...\n";

	 /* Predict class label for each record */
	TableRow record = createRecord(vector<string>({ "8", "COP 5725", "Fall 2016", "?" , "?" , "DBMS", "Computer Programming" }));
	string predicted_class_label = classifier->predictIgnore(record, ignored_attributes.begin(), ignored_attributes.end());
	cout << "Class label for record successfully predicted...\n";

	cout << endl;

	/* Print decision tree */
	cout << "Printing decision tree...\n";
	cout << endl;
	cout << *classifier << endl;
	cout << "Done printing decision tree...\n";
	cout << endl;

	/* Print records and their predicted class labels */
	cout << "Printing records and their predicted class labels...\n";
	cout << "(" << record << ") : " << predicted_class_label << endl;

	cout << endl;

	/* Deallocate memory for dynamic objects, arrays, etc. */
	cout << "Finished classification procedure...\n";
	cout << "Exiting...\n";
	cout << "Removing decision tree from heap...\n";
	delete classifier;

	cout << "Done!\n";



	return 0;
}

