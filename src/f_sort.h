

#include <iostream>
#include <vector>

template <typename IteratorType>
void merge(	   IteratorType first,
			   IteratorType last,
			   IteratorType firstZ,
			   IteratorType middleZ,
			   IteratorType lastZ);

template <typename IteratorType>
void print(	   IteratorType first,
				  IteratorType last			   );


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

	}



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

