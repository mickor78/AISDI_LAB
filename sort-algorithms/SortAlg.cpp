//
// Created by Kamil Zych on 17.03.2019.
//

#include "SortAlg.h"

SortAlg::SortAlg(const int* input_table, int length_i): length(length_i)
{
	std::cout<<" SortAlg(): { ";
	table = new int[length_i];
	for(int i=0; i<length_i; i++)
	{
		table[i] = input_table[i];
		std::cout<<table[i]<<" ";
	}
	std::cout<<"}"<<std::endl;
}

SortAlg::~SortAlg()
{
	std::cout<<"~SortAlg(): "<<*this<<std::endl;

	delete[] table;
}


std::ostream &operator<<( std::ostream &output, const SortAlg &B )
{
	output <<"{ ";
	for(int i=0; i<B.length; i++)
	{
		output<<B.table[i]<<" ";
	}
	output<<"}";

	return output;
}

bool SortAlg::isEqualTo(const int *table_i)
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
