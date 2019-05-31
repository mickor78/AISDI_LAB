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

using coord = pair<int,int>;
using stateHistory = pair< int, vector<coord> >;

int h(int i, int j){
	const int horCost = j;
	const int verCost = 6-i;

	return horCost + verCost -1;

}

int h(coord coord_val){
	return h(coord_val.first, coord_val.second);
}

int getEntryCost(coord coord_val, vector<vector<int>> board){

	int i = coord_val.first;
	int j = coord_val.second;

	return board[i][j];
}

int getTotalCost(vector<coord> history, vector<vector<int>> board){

	int totalCost{};

	for(const auto state : history)
		totalCost += getEntryCost(state, board);

	return totalCost;
}

stateHistory popCheapest(vector<stateHistory>& queue){

	if(queue.empty())
		return stateHistory(-1, vector<coord>{coord(-1,-1)});

	int minimalCost = 99999;
	int currentCost;
	vector<stateHistory>::iterator cheapestIt;
	coord cheapest{};

	for(auto iterator = queue.begin(); iterator != queue.end(); ++iterator){

		currentCost = iterator->first;
		if(currentCost < minimalCost){

			cheapestIt = iterator;
			cheapest = *(iterator->second.end() - 1);
			minimalCost = iterator->first;
		}
	}

	stateHistory result = *cheapestIt;
	queue.erase(cheapestIt);
	return result;
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

	//Heap4<int,pair<int,int>> queue;
	Heap4<int,pair<pair<int,int>,pair<int,int>>> tableOfPosibleWays;

	using pairOfPairs = pair<pair<int,int>,pair<int,int>>;



	int i = 0,j = 6;				//start position
	coord start(0,6), currentCoord;
	stateHistory currentHist;
	vector<coord> checked;
	vector<coord> startHistory;
	startHistory.push_back(start);
	vector<stateHistory> queue;

	queue.push_back(stateHistory( h(start), startHistory ));

	//0 LEFT
	//1 RIGHT
	//2 DOWN
	//3 UP

	while(i!=6||j!=0){

		currentHist = popCheapest(queue);							// get cheapest stateHistory from queue
		currentCoord = *(currentHist.second.end() - 1);
		checked.push_back(currentCoord);							// put current state into checked states

		i = currentCoord.first;
		j = currentCoord.second;

		cout<<i<<" "<<j;
/*
		// Left Right 0 1
		if(0<j&&j<6){
			queue.push_back()
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
		j = best.second.second.second;*/
	}

}


int main() {

	//astar();

	coord a(1,1), b(2,2), c(3,3);
	vector<vector<int>> board = {
			{3,3,3,3,2,1,0},
			{3,3,3,1,1,1,2},
			{6,6,5,1,4,9,9},
			{9,9,9,1,1,1,1},
			{7,7,7,8,4,2,1},
			{4,4,5,4,4,2,1},
			{0,1,1,1,1,1,1}
	};


	vector<stateHistory> queue = {
			{3, vector<coord>{a,b,c}},
			{1, vector<coord>{a,c,b}},
			{2, vector<coord>{c,b,a}}
	};

	cout << getTotalCost(vector<coord>{a,b,c}, board) << endl;

	cout << popCheapest(queue).first << endl;
	cout << popCheapest(queue).first << endl;
	cout << popCheapest(queue).first << endl;
	cout << popCheapest(queue).first << endl;

	return 0;
}
