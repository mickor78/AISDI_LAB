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


	vector<int> tableSorted = {1,2,2,3,6,9};
	vector<int> tableToSort = {3,2,6,9,1,2};

	mergeSort<vector<int>::iterator>(tableToSort.begin(), tableToSort.end());




	return 0;
}
