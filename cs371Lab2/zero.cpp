#include "pch.h"
namespace cs371Lab2Lib
{
	void zeroCpp(int* intsToZero, int nInts)
	{
		for (int i = 0; i < nInts; i++) intsToZero[i] = 0;
	}
}