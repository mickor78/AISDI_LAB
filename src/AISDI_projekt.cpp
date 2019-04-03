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


	vector<int> tableSorted;
	vector<int> tableToSort;
	vector<string> wordToSort;

	string word="";

	ifstream text;
	text.open("pan-tadeusz.txt");

	while(!text.eof()){
		char x = text.get();
		bool isLetter= x != ' ' && x != '\n'&& x != '\t' && x!='.'&& x!=',';
		if (isLetter){
			word+=x;
		} else {
			if (word!="") wordToSort.push_back(word);
			word = "";
		}
	}

	text.close();

	wordToSort.push_back("alfabet");
	wordToSort.push_back("alfred");
	wordToSort.push_back("allegro");
	wordToSort.push_back("betha");

	static const int arr1[] = {3,2,6,9,1,2};
	static const int arr2[] = {1,2,2,3,6,9};
	for (int i = 0; i < sizeof(arr1)/sizeof(arr1[0]); ++i) {
		tableToSort.push_back(arr1[i]);
		tableSorted.push_back(arr2[i]);
	}

	sort(wordToSort.begin(),wordToSort.end());

	quicksort(wordToSort.begin(),wordToSort.end());

	sort(tableToSort.begin(),tableToSort.end());
	//quicksort(tableToSort.begin(),tableToSort.end());

	print(tableToSort.begin(), tableToSort.end());
	//mergeSort(tableToSort.begin(), tableToSort.end(), Z.begin());
	heapSort(tableToSort.begin(), tableToSort.end());
	print(tableToSort.begin(), tableToSort.end());

	return 0;
}
