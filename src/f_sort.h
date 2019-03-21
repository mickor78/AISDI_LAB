/*
 * f_sort.h
 *
 *  Created on: Mar 21, 2019
 *      Author: BittenPear
 */

#include <iostream>
#include <vector>
#include <random>


template <typename IteratorType>
void quicksort(IteratorType first, IteratorType last){

	if (last-first==1){}
	else{

		IteratorType pivot = last-1;
	for (IteratorType var = first; var != last; ++var) {
			if (*var>=*pivot && var<pivot){
				auto elm = *var;
				*pivot = elm;

			}

		}


	if (*first > *(last-1)) std::cout<<*first<<"wiekszy niz"<<*(last-1);
	else std::cout<<*first<<"mniejszy niz"<<*(last-1);
	}

}


int foo();
