#include "pch.h"
#include "cppFunctions.h"

namespace cs371Lab2Lib
{
	void radixSortCpp(int* dataToSort, int* scratch, int* theCounts, int nElementsToSort)
	{
		for (int i = 0; i < nElementsToSort; i++)
		{
			scratch[theCounts[dataToSort[i]]++] = dataToSort[i];
		}

		for (int i = 0; i < nElementsToSort; i++)
		{
			dataToSort[i] = scratch[i];
		}
	}
}
