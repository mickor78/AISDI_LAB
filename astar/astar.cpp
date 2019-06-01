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

int getEntryCost(coord coord_val, const vector<vector<int>>& board){

	int i = coord_val.first;
	int j = coord_val.second;

	if(i < 0 or j < 0)
		return 999999;

	return board[i][j];
}

int getTotalCost(const vector<coord>& history, const vector<vector<int>>& board){

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

bool isAlreadyChecked(coord coord_val, const vector<coord>& checked_vec){

	for(const auto checked : checked_vec)
		if(checked == coord_val)
			return true;

	return false;
}

void pushBackToQueue(vector<stateHistory>& queue, const vector<vector<int>>& board, const vector<coord>& currentStateHistory, coord coord_val){

	int cost = getTotalCost(currentStateHistory, board) + getEntryCost(coord_val, board);
	cost += h(coord_val);

	vector<coord> tempStateHistory = currentStateHistory;
	tempStateHistory.push_back(coord_val);

	queue.push_back( stateHistory(cost, tempStateHistory) );
}

void printSolution() {} // TODO printing solution as required

void astar(){

	// TODO read from a file
	vector<vector<int>> board = {
				{3,3,3,3,2,1,0},
				{3,3,3,1,1,1,2},
				{6,6,5,1,4,9,9},
				{9,9,9,1,1,1,1},
				{7,7,7,8,4,2,1},
				{4,4,5,4,4,2,1},
				{0,1,1,1,1,1,1}
		};


	int i = 0, j = 6;												//start position
	coord start(i,j), currentCoord, right, down, left, up;
	stateHistory cheapestState;
	vector<coord> checked_vec, currentStateHistory, tempStateHistory, solution;
	currentStateHistory.push_back(start);
	vector<stateHistory> queue;

	pushBackToQueue(queue, board, currentStateHistory, start);

	//0 LEFT
	//1 RIGHT
	//2 DOWN
	//3 UP

	while(i!=6||j!=0){

		cheapestState = popCheapest(queue);							// get cheapest stateHistory from queue
		currentCoord = *(cheapestState.second.end() - 1);
		currentStateHistory = cheapestState.second;
		checked_vec.push_back(currentCoord);						// put current state into checked states

		i = currentCoord.first;
		j = currentCoord.second;

		// print << (matrix location) : entryCost <<
		cout << "(" << i << ", " << j << ") : " << getEntryCost(currentCoord, board) << endl;

		if(0<j && j<6){ // check on the left and on the right

			left = coord(i,j-1);
			if(not isAlreadyChecked(left, checked_vec))
				pushBackToQueue(queue, board, currentStateHistory, left);

			right = coord(i,j+1);
			if(not isAlreadyChecked(right, checked_vec))
				pushBackToQueue(queue, board, currentStateHistory, right);

		} else if (j==0) { // check only on the right

			right = coord(i,j+1);
			if(not isAlreadyChecked(right, checked_vec))
				pushBackToQueue(queue, board, currentStateHistory, right);

		} else { // check only on the left

			left = coord(i,j-1);
			if(not isAlreadyChecked(left, checked_vec))
				pushBackToQueue(queue, board, currentStateHistory, left);
		}

		if(i<6&&0<i){ // check up and down

			up = coord(i-1,j);
			if(not isAlreadyChecked(up, checked_vec))
				pushBackToQueue(queue, board, currentStateHistory, up);

			down = coord(i+1,j);
			if(not isAlreadyChecked(down, checked_vec))
				pushBackToQueue(queue, board, currentStateHistory, down);

		} else if (i==0) { // check only down

			down = coord(i+1,j);
			if(not isAlreadyChecked(down, checked_vec))
				pushBackToQueue(queue, board, currentStateHistory, down);

		} else { // check only up

			up = coord(i-1,j);
			if(not isAlreadyChecked(up, checked_vec))
				pushBackToQueue(queue, board, currentStateHistory, up);
		}
	}

	solution = currentStateHistory;

	cout << endl;
	for(const auto coordVal : solution)
		cout << coordVal.first << ", " << coordVal.second << endl;

	printSolution();
}


int main() {

	astar();

/*
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
*/
	return 0;
}
