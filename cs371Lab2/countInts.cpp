#include "pch.h"
#include "cppFunctions.h"

namespace cs371Lab2Lib
{
	void countIntsCpp(int* theInts, int* counts, int nInts)
	{
		for (int i = 0; i < nInts; i++)
		{
			++counts[theInts[i]];
		}
	}
}