//
// Created by Kamil Zych on 18.03.2019.
//

#ifndef SORTING_SELECTSORT_H
#define SORTING_SELECTSORT_H

#include <iostream>
#include "SortAlg.h"

class SelectSort : public SortAlg
{

public:
	SelectSort(const int[] , int length_i);
	~SelectSort() override;

	void sort() override;

};


#endif //SORTING_SELECTSORT_H
