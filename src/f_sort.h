/*
 * f_sort.h
 *
 *  Created on: Mar 21, 2019
 *      Author: BittenPear
 */

#include <iostream>
#include <vector>


template <typename IteratorType>
void quicksort(IteratorType first, IteratorType last){

	for (auto var = first; var != last; ++var) {
		std::cout<<*var<<std::endl;
	}

	if (*first > *(last-1)) std::cout<<*first<<"wiekszy niz"<<*(last-1);
	else std::cout<<*first<<"mniejszy niz"<<*(last-1);

}


int foo();
