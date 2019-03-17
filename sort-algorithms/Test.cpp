//
// Created by Kamil Zych on 17.03.2019.
//

#include "BubbleSort.h"
#include <iostream>

using namespace std;

int main()
{

	int TableToSort[] = {3,2,1};
	int Length = sizeof(TableToSort)/sizeof(int);

	BubbleSort A(TableToSort, Length);
	A.sort();


	return 0;
}