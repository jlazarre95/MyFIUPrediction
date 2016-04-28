#include "../include/j48_branch.h"

using namespace std;

J48Branch::J48Branch()
{
	next = NULL; 
}

J48Branch::~J48Branch()
{
	delete next;
}
