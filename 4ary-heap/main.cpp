//============================================================================
// Name        : Zadanie4.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

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

	void print(std::ostream& stream, int i, int tabNO) const {

		if(i < heap.size()){

			string t = "";
			for(int i = 0; i < tabNO; i++)
				t += "\t";

			stream << t << heap[i].first << endl;

			print(stream, 4*i + 1, tabNO+1);
			print(stream, 4*i + 2, tabNO+1);
			print(stream, 4*i + 3, tabNO+1);
			print(stream, 4*i + 4, tabNO+1);
		}
	}

};

void unit_test() {
	Heap4<int, int> testHeap;

	assert(testHeap.isEmpty() == true);
	assert(testHeap.size() == 0);

	testHeap.insert(1, 1);

	assert(testHeap.isEmpty() == false);
	assert(testHeap.size() == 1);

	for (int var = 0; var < 50; ++var) {
		testHeap.insert(var, 1);
	}


	//testHeap.insert("a",1);

	testHeap.print(std::cout);
	std::cout<<endl;

	std::cout<<"--------------------"<<endl;

	for (int i = 0; i < 10; ++i) {
		testHeap.pop();
	}

	testHeap.print(std::cout);

}

int main() {
	std::cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	unit_test();

	return 0;
}
