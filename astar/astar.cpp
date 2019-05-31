//============================================================================
// Name        : djisc.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

/*
 * queue.cpp
 *
 *  Created on: May 31, 2019
 *      Author: mkorzeni
 */


template<typename KeyType, typename ValueType>
class Heap4 {
public:
	using KeyValueType = std::pair< KeyType, ValueType>;

	bool isEmpty() const {
		return heap.size() == 0;
	}

	void insert(KeyType const& key, ValueType const & value) {
		auto newElement = KeyValueType(key, value);

		heap.push_back(newElement);

		if (heap.size() == 1)
			return;
		else {
			int tempIndex = heap.size() - 1;
			int indexOfParent = (tempIndex - 1) / 4;

			while (tempIndex != 0) {
				if (heap[tempIndex].first < heap[indexOfParent].first) {
					auto temp = heap[tempIndex];
					heap[tempIndex] = heap[indexOfParent];
					heap[indexOfParent] = temp;
				}
				tempIndex = indexOfParent;
				indexOfParent = (tempIndex - 1) / 4;
			}
		}

	}
	void insert(KeyValueType const & key_value) {
		insert(key_value.first, key_value.second);
	}
	KeyValueType const& peek() const {
		if (!isEmpty())
			return heap[0];
		else
			throw -1;
	}
	KeyValueType pop() {
		KeyValueType head = *heap.begin();

		*heap.begin() = *(--heap.end());
		heap.pop_back();

		int tempIndex = 0;
		int iter = 1;
		int indexOfChild = tempIndex*4+iter;

		while (indexOfChild <= heap.size()-1) {
		    //find min child
		    auto tempFirst = heap[indexOfChild].first;
		    int indexOfminChild = indexOfChild;
            for (int i = 1; i < 4; ++i) {
                if (indexOfminChild+i > heap.size()-1) break;
                if(heap[indexOfChild+i].first < tempFirst){
                    tempFirst=heap[indexOfChild+i].first;
                    indexOfminChild = indexOfChild+i;
                }
            }

            //replace parent if min child is smaller than
			if (heap[tempIndex].first > heap[indexOfminChild].first) {
				auto temp = heap[tempIndex];
				heap[tempIndex] = heap[indexOfminChild];
				heap[indexOfminChild] = temp;
			}

			tempIndex = indexOfminChild;
			indexOfChild = tempIndex*4+1;
		}

		return head;
	}
	size_t size() const {
		return heap.size();
	}
	void print(ostream& stream) const {
		print(stream, 0, 0);
	}

private:
	vector<KeyValueType> heap;

};

int h(int i, int j){
	const int horCost = j;
	const int verCost = 6-i;

	return horCost + verCost -1;

}

void astar(){
	vector<vector<int>>Board = {
				{3,3,3,3,2,1,0},
				{3,3,3,1,1,1,2},
				{6,6,5,1,4,9,9},
				{9,9,9,1,1,1,1},
				{7,7,7,8,4,2,1},
				{4,4,5,4,4,2,1},
				{0,1,1,1,1,1,1}
		};

	Heap4<int,pair<int,int>> queue;
	Heap4<int,pair<pair<int,int>,pair<int,int>>> tableOfPosibleWays;

	using pairOfPairs = pair<pair<int,int>,pair<int,int>>;



	int i = 0,j = 6;
	//0 LEFT
	//1 RIGHT
	//2 DOWN
	//3 UP

	while(i!=6||j!=0){



		cout<<i<<" "<<j;

		pair<int,int>pairOf;
		pairOf.first = i;
		pairOf.second = j;

		// Left Right 0 1
		if(0<j&&j<6){
			tableOfPosibleWays.insert(Board[i][j-1]+h(i,j-1),pairOfPairs(pairOf, pair<int,int>(i,j-1)));
			tableOfPosibleWays.insert(Board[i][j+1]+h(i,j+1),pairOfPairs(pairOf, pair<int,int>(i,j+1)));
		} else if (j==0) {
			tableOfPosibleWays.insert(9999,pairOfPairs(pairOf, pair<int,int>(i,j-1)));
			tableOfPosibleWays.insert(Board[i][j+1]+h(i,j+1),pairOfPairs(pairOf, pair<int,int>(i,j+1)));
		} else {
			tableOfPosibleWays.insert(Board[i][j-1]+h(i,j-1),pairOfPairs(pairOf, pair<int,int>(i,j-1)));
			tableOfPosibleWays.insert(9999,pairOfPairs(pairOf, pair<int,int>(i,j+1)));
		}

		if(i<6&&0<i){
			//UP Down
			tableOfPosibleWays.insert(Board[i-1][j]+h(i-1,j),pairOfPairs(pairOf, pair<int,int>(i-1,j)));
			tableOfPosibleWays.insert(Board[i+1][j]+h(i+1,j),pairOfPairs(pairOf, pair<int,int>(i+1,j)));
		} else if (i==0) {
			tableOfPosibleWays.insert(Board[i+1][j]+h(i+1,j),pairOfPairs(pairOf, pair<int,int>(i+1,j)));
			tableOfPosibleWays.insert(9999,pairOfPairs(pairOf, pair<int,int>(i-1,j)));
		} else {
			tableOfPosibleWays.insert(9999,pairOfPairs(pairOf, pair<int,int>(i+1,j)));
			tableOfPosibleWays.insert(Board[i-1][j]+h(i-1,j),pairOfPairs(pairOf, pair<int,int>(i-1,j)));
		}


		auto best = tableOfPosibleWays.pop();



		cout<<" "<<best.first<<endl;

		i = best.second.second.first;
		j = best.second.second.second;
	}

}


int main() {

	astar();



	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
