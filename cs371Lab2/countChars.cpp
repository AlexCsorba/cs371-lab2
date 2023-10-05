#include "pch.h"
#include "cppFunctions.h"

namespace cs371Lab2Lib
{
	void countCharsCpp(const char* chars, int* counts, int nChars)
	{
		for (int i = 0; i < nChars; i++)
		{
			++counts[chars[i]];
		}
	}
}