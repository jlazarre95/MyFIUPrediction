#pragma once
#include <vector>
#include "attribute.h"


typedef struct AttributeList
{
public:
	std::vector<Attribute> all_attributes;

	AttributeList();
	~AttributeList();
	template <class InputIterator>
	AttributeList(InputIterator first, InputIterator last) { setAllAttributes(first, last); }
	void addAttribute(Attribute new_attribute);
	Attribute getAttribute(int index);
	Attribute getAttribute(std::string attribute_name);
	int getIndexOfAttribute(std::string attribute_name);
	int getNumOfAttributes();
	Attribute operator[](int index) { return getAttribute(index); }

	auto begin() -> decltype(all_attributes.begin()) { return all_attributes.begin(); }
	auto end() -> decltype(all_attributes.end()) { return all_attributes.end(); }

	template <class InputIterator>
	void setAllAttributes(InputIterator first, InputIterator last)
	{
		for (InputIterator all_attributes_iterator = first; all_attributes_iterator != last; all_attributes_iterator++)
		{
			Attribute new_attribute = *all_attributes_iterator;
			all_attributes.push_back(new_attribute);
		}
	}


} AttributeList;
