#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cstdlib>

using namespace std;

/*----------------------------------------------------------------BINARY SEARCH ALGORITHM-----------------------------------------------------------------*/
int binarySearch(int* array, int first, int last, int searchValue) // binary search in array
{
	int middle = (first + last) / 2;
	int counterOfIteration = 1;
	while (first <= last)
	{
		std::cout << "Iteration " << counterOfIteration << " , f,l,m (" << first << " " << last << " " << middle << ")" << std::endl;

		if (array[middle] > searchValue)
		{
			last = middle - 1;
		}
		else if (array[middle] < searchValue)
		{
			first = middle + 1;
		}
		else
		{
			return middle;
		}

		middle = (first + last) / 2;
		++counterOfIteration;
	}
	return -1; // occurs when didn't find number
}

int binarySearch(vector<int>::iterator iteratorToFirst, vector<int>::iterator iteratorToLast, int searchValue) // binary search in vector
{
	auto beginIter = iteratorToFirst;
	auto Middle = distance(iteratorToFirst, iteratorToLast) / 2;
	int counterOfIteration = 1;

	while (iteratorToFirst < iteratorToLast)
	{
		std::cout << "Iteration " << counterOfIteration << " , f,l,m (" << *iteratorToFirst << " " << *(iteratorToLast - 1) << " " << *(iteratorToFirst + Middle) << ")" << std::endl;
		int value = *(iteratorToFirst + Middle);
		
		if (value > searchValue)
		{
			iteratorToLast = iteratorToFirst + Middle;
		}
		else if (value < searchValue)
		{
			iteratorToFirst = iteratorToFirst + Middle + 1;
		}
		else
		{
			return distance(beginIter, iteratorToFirst + Middle);
		}

		Middle = distance(iteratorToFirst, iteratorToLast) / 2;
		++counterOfIteration;
	}

	return -1; // occurs when didn't find number
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------------*/

int main()
{
	vector<int> intVector;
	const size_t dim = 8;
	intVector.reserve(dim);

	for (size_t i = 1; i <= dim; i++)
		intVector.push_back(i);

	for (auto i = intVector.begin(); i != intVector.end(); i++)
		cout << *i << " ";

	if (!is_sorted(intVector.begin(), intVector.end()))
		sort(intVector.begin(), intVector.end());

	cout << endl;

	for (auto i = intVector.begin(); i != intVector.end(); i++)
		cout << *i << " ";

	int arr[dim];
	for (size_t i = 0; i < dim; i++)
		arr[i] = intVector[i];

	std::cout << endl;
	
	for (int i = 0; i <= 9; i++)  // example of binary search in array
	{
		std::cout << "Result solution : searchValue = " << i << " , index = " << binarySearch(arr, 0, dim-1, i) << std::endl;
	}

	for (int i = 0; i <= 9; i++)  // example of binary search in vector
	{
		std::cout << "Result solution based on iterators : searchValue = " << i << " , index = " << binarySearch(intVector.begin(), intVector.end(), i) << std::endl;
	}

	return EXIT_SUCCESS;
}