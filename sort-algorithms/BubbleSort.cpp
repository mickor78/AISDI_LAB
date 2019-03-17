//
// Created by Kamil Zych on 17.03.2019.
//

#include "BubbleSort.h"
#include <iostream>

BubbleSort::BubbleSort(const int* input_table, int length_i): length(length_i)
{
	std::cout<<" BubbleSort(): { ";
	table = new int[length_i];
	for(int i=0; i<length_i; i++)
	{
		table[i] = input_table[i];
		std::cout<<table[i]<<" ";
	}
	std::cout<<"}"<<std::endl;
}

BubbleSort::~BubbleSort()
{
	std::cout<<"~BubbleSort(): "<<*this<<std::endl;

	delete[] table;
}

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

std::ostream &operator<<( std::ostream &output, const BubbleSort &B )
{
	output <<"{ ";
	for(int i=0; i<B.length; i++)
	{
		output<<B.table[i]<<" ";
	}
	output<<"}";

	return output;
}

bool BubbleSort::isEqualTo(const int *table_i)
{
	bool isEqual = true;
	int i=0;

	while( isEqual & i<length)
	{
		if( table[i] != *(table_i) )
			isEqual = false;

		table_i++;
		i++;
	}

	return isEqual;
}
