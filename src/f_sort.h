

#include <iostream>
#include <vector>
#include <random>

template <typename IteratorType>
void merge(	  IteratorType first,
			  IteratorType last,
			  IteratorType firstZ,
			  IteratorType middleZ,
			  IteratorType lastZ);

template <typename IteratorType>
void print(	  IteratorType first,
			  IteratorType last);

int parentIndex(int child);


template <typename IteratorType>
void mergeSort(IteratorType first, IteratorType last, IteratorType firstZ){

	int N = last - first;


	if( N > 1 )
	{
		auto middle  = first  + N/2;
		auto middleZ = firstZ + N/2;
		auto lastZ 	 = firstZ + N;

		mergeSort(first,middle,firstZ);
		mergeSort(middle,last,middleZ);

		merge(first,last,firstZ,middleZ,lastZ);

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


template <typename IteratorType>
void heapSort(IteratorType first, IteratorType last)
{
	std::vector< typename std::iterator_traits<IteratorType>::value_type > heap;
	int no=0;

	for(auto i = first; i != last; i++)
	{
		heap.push_back(*i);

		if(parentIndex(no) == parentIndex(no - 1) ) //if added rChild
		{
			balanceTree(heap.be , ) // TODO complete balancing lowest sub-tree
		}


		no++;
	}

	std::cout<<"heap: ";
	print(heap.begin(), heap.end());
}


template <typename IteratorType>
void merge(	IteratorType first,
			IteratorType last,
			IteratorType firstZ,
			IteratorType middleZ,
			IteratorType lastZ){


	auto middle_const = middleZ;
	auto last_const = lastZ;
	auto lastZ_const = lastZ;
	auto firstZ_const = firstZ;


	for(auto i = first; i != last; ++i) *firstZ++ = *i;
	firstZ = firstZ_const;


	while( (firstZ != middle_const or middleZ != last_const) )
	{

		if(firstZ == middle_const and middleZ != last_const)
		{
			*first++ = *middleZ++;
		}
		else if(firstZ != middle_const and middleZ == last_const)
		{
			*first++ = *firstZ++;
		}
		else
		{
			if (*firstZ < *middleZ)
				*first++ = *firstZ++;
			else
				*first++ = *middleZ++;

		}
	}



}

template <typename IteratorType>
void print(IteratorType first, IteratorType last)
{
	for(auto i = first; i != last; ++i) std::cout<<*i<<" ";
	std::cout<<std::endl;

}


template <typename IteratorType>
void balanceTree(IteratorType parent, IteratorType lChild)
{
	auto temp = *parent;

	if( *parent < *lChild)
	{
		temp = *parent;
		*parent = *lChild;
		*lChild = temp;
	}
}

template <typename IteratorType>
void balanceTree(IteratorType parent, IteratorType lChild,  IteratorType rChild)
{
	auto temp = *parent;


	if( *lChild <= *rChild )
	{
		if (*parent < *lChild)
		{
			temp = *parent;
			*parent = *lChild;
			*lChild = temp;
		}
	}
	else
	{
		if (*parent < *rChild)
		{
			temp = *parent;
			*parent = *rChild;
			*rChild = temp;
		}

	}
}

int parentIndex(int child)
{
	return (child - 1)/2;
}