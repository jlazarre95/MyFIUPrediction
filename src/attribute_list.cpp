#include "../include/attribute_list.h"
#include <stdexcept>

using namespace std;
AttributeList::AttributeList()
{
}


AttributeList::~AttributeList()
{
}


//template<class InputIterator>
//AttributeList::AttributeList(InputIterator first, InputIterator last)
//{
//	setAllValues(first, last);
//}


void AttributeList::addAttribute(Attribute new_attribute)
{
	all_attributes.push_back(new_attribute);
}

//template<class InputIterator>
//void AttributeList::setAllAttributes(InputIterator first, InputIterator last)
//{
//	for (InputIterator all_attributes_iterator = first; all_attributes_iterator != last; all_attributes_iterator++)
//	{
//		attribute new_attribute = *all_attributes_iterator;
//		all_attributes.push_back(new_attribute);
//	}
//	
//}


Attribute AttributeList::getAttribute(int index)
{
	return all_attributes[index];
}

Attribute AttributeList::getAttribute(std::string attribute_name)
{
	Attribute attr;

	for (auto all_attributes_iterator = all_attributes.begin(); all_attributes_iterator != all_attributes.end(); all_attributes_iterator++)
	{
		attr = *all_attributes_iterator;

		if (attr.name == attribute_name)
			return attr;
	}

	throw invalid_argument("Attribute " + attribute_name + " does not exist!");
}

int AttributeList::getIndexOfAttribute(std::string attribute_name)
{
	int index_of_attribute = 0;

	for (Attribute relation_attribute : all_attributes)
	{
		if (relation_attribute.name == attribute_name)
			return index_of_attribute;
		index_of_attribute++;
	}

	return -1;
}

int AttributeList::getNumOfAttributes()
{
	return all_attributes.size();
}


