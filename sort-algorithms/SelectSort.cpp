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
		int index_of_smallest, smallest;
		int temp;
														// for every element in unsorted part of the table
		for( int first_index_unsorted=0; first_index_unsorted<length-1; first_index_unsorted++)
		{
			index_of_smallest = first_index_unsorted;
			smallest = table[index_of_smallest];
														// selection of the smallest element
			for (int i = first_index_unsorted+1; i < length; i++)
			{
				if (smallest > table[i])
				{
					smallest = table[i];
					index_of_smallest = i;
				}
			}
														// swapping the smallest with 1st unsorted element
			temp = table[index_of_smallest];
			table[index_of_smallest] = table[first_index_unsorted];
			table[first_index_unsorted] = temp;
		}
	}
}
