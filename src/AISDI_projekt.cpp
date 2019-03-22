//============================================================================
// Name        : AISDI_projekt.cpp
// Author      : mickor78@gmail.com
// Version     :
// Copyright   :
// Description :
//============================================================================


#include <iostream>
#include <vector>
#include "f_sort.h"
#include <algorithm>
#include <fstream>

using namespace std;

int main()
{


	vector<int> tableToSort = {3,2,6,9,1,2};
	vector<int> Z = tableToSort;

	print(tableToSort.begin(), tableToSort.end());
	//mergeSort(tableToSort.begin(), tableToSort.end(), Z.begin());
	heapSort(tableToSort.begin(), tableToSort.end());
	print(tableToSort.begin(), tableToSort.end());

	return 0;
}
