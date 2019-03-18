//
// Created by Kamil Zych on 18.03.2019.
//

#include "SelectSort.h"

SelectSort::SelectSort(const int* input_table, int length_i): 	SortAlg(input_table, length_i)
{
	std::cout << " SelectSort()" << std::endl;
}

SelectSort::~SelectSort()
{
	std::cout << "~SelectSort(): ";
}


void SelectSort::sort()
{
	if( length > 1 )									// check if not sorting 1-element table
	{

	}
}
