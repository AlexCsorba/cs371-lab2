#include "pch.h"
#include "cppFunctions.h"

namespace cs371Lab2Lib
{
	void countCharsCpp(const char* chars, int* counts, int nChars)
	{
		zeroCpp(counts, N_ASCII_CHARS);
		for (int i = 0; i < nChars; i++)
		{
			++counts[chars[i]];
		}
	}
}