//
// Created by Kamil Zych on 17.03.2019.
//

#ifndef SORTING_SORTALG_H
#define SORTING_SORTALG_H

#include <iostream>


class SortAlg
{
protected:
	int* table;
	int length;

public:
	SortAlg(const int[] , int length_i);
	virtual ~SortAlg();

	virtual void sort()=0;
	bool isEqualTo(const int[]);

	friend std::ostream &operator<<(std::ostream &output, const SortAlg &B);
};



#endif //SORTING_SORTALG_H
