//
// Created by Kamil Zych on 17.03.2019.
//

#include "BubbleSort.h"
#include <iostream>

BubbleSort::BubbleSort(int* input_table, int length_): length(length_)
{
	std::cout<<" BubbleSort(): { ";
	table = new int[length_];
	for(int i=0; i<length_; i++)
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
