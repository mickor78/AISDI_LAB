//============================================================================
// Name        : AISDI_projekt.cpp
// Author      : mickor78@gmail.com
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <iostream>
#include <vector>
#include "f_sort.h"
#include <algorithm>


using namespace std;

int main()
{


	vector<int> tableSorted;
	vector<int> tableToSort;
	static const int arr1[] = {3,2,6,9,1,2};
	static const int arr2[] = {1,2,2,3,6,9};
	for (int i = 0; i < sizeof(arr1)/sizeof(arr1[0]); ++i) {
		tableToSort.push_back(arr1[i]);
		tableSorted.push_back(arr2[i]);
	}
	int Length = tableSorted.size();





	sort(tableSorted.begin(),tableSorted.end());
	quicksort(tableSorted.begin(),tableSorted.end());


	return 0;
}
