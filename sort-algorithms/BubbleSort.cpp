//
// Created by Kamil Zych on 17.03.2019.
//

#include "BubbleSort.h"

BubbleSort::BubbleSort(const int* input_table, int length_i): 	SortAlg(input_table, length_i)
{
	std::cout << " BubbleSort()" << std::endl;
}

BubbleSort::~BubbleSort()
{
	std::cout << "~BubbleSort(): ";
}



void BubbleSort::sort()
{
	if(length > 1)									// check if not sorting 1-element table
	{
		int temp, range = length - 1;
		bool isSorted = true;

		for( int j = 0; j < length - 1; j++)		// looping for multiple bubbles
		{
			for (int i = 0; i < range; i++)			// one bubbles round
			{
				if (table[i] > table[i + 1])
				{
					temp = table[i];
					table[i] = table[i + 1];
					table[i + 1] = temp;
					isSorted = false;
				}
			}

			if( isSorted ) break;					// finish looping if in bubbles round there is no bubble

			range--;
			isSorted = true;
		}
	}
}


