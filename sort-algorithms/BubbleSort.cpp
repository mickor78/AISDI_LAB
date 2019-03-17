//
// Created by Kamil Zych on 17.03.2019.
//

#include "BubbleSort.h"
#include <iostream>

BubbleSort::BubbleSort(const int* input_table, int length_i): 	SortAlg(input_table, length_i)
{}


void BubbleSort::sort()
{
	if(length > 1)
	{
		int temp, range = length - 1;

		for( int j = 0; j < length - 1; j++)
		{
			for (int i = 0; i < range; i++)
			{
				if (table[i] > table[i + 1])
				{
					temp = table[i];
					table[i] = table[i + 1];
					table[i + 1] = temp;
				}
			}

			range--;
		}
	}
}


