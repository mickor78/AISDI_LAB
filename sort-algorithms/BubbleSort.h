//
// Created by Kamil Zych on 17.03.2019.
//

#ifndef AISDI_LAB_BUBBLESORT_H
#define AISDI_LAB_BUBBLESORT_H

#include <iostream>
#include "SortAlg.h"

class BubbleSort : public SortAlg
{

public:
	BubbleSort(const int[] , int length_i);
	~BubbleSort() override = default;

	void sort() override;

};

#endif //AISDI_LAB_BUBBLESORT_H
