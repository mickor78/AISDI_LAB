//
// Created by Kamil Zych on 17.03.2019.
//

#ifndef SORTING_INSERTSORT_H
#define SORTING_INSERTSORT_H

#include <iostream>
#include "SortAlg.h"

class InsertSort : public SortAlg
{

public:
	InsertSort(const int[] , int length_i);
	~InsertSort() override;

	void sort() override;

};


#endif //SORTING_INSERTSORT_H
