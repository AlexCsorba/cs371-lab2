#include "pch.h"
#include "cppFunctions.h"

namespace cs371Lab2Lib
{
	void sumOfPreviousElementsCpp(int* array, int length)
	{
		int sum = 0;
		for (int i = 0; i < length; i++)
		{
			int temp = array[i];
			array[i] = sum;
			sum += temp;
		}
	}
}