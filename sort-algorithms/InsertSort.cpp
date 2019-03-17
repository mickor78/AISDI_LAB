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

}
