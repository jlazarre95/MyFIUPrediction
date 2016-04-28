#include "../include/j48_node_branch.h"

using namespace std;

j48_node_branch::j48_node_branch()
{
	next = NULL; 
}

j48_node_branch::~j48_node_branch()
{
	delete next;
}
