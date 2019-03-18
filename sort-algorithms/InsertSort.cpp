//
// Created by Kamil Zych on 17.03.2019.
//

#include "InsertSort.h"

InsertSort::InsertSort(const int* input_table, int length_i): 	SortAlg(input_table, length_i)
{
	std::cout << " InsertSort()" << std::endl;
}

InsertSort::~InsertSort()
{
	std::cout << "~InsertSort(): ";
}


void InsertSort::sort()
{
	if( length > 1 )									// check if not sorting 1-element table
	{
		int temp, j;

		for(int i=0; i<length-1; i++)					// for every element
		{
			if( table[i] > table[i+1] )					// if first element from unsorted part of the table is smaller...
			{											// ...than last element from sorted part do
				temp = table[i+1];
				j = i;
				while( j >= 0 & table[j] > temp )		// move sorted part +1 until finding place for new element
				{
					table[j+1] = table [j];
					j--;
				}
				table[j+1] = temp;
			}
		}
	}
}
