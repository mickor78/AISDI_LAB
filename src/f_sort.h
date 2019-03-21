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
		std::cout<<*var;
	}

}


int foo();
