#include "pch.h"
#include "CppUnitTest.h"
#include <string>
#include <algorithm>
using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "..\cs371Lab2\cppFunctions.h"

// zeroAsm_ - Initialize an integer array to all zeros.
//	int* intsToZero is the address of the first element in the array
//  int nInts is the number of elements in the array.
extern "C" void zeroAsm_(int* intsToZero, int nInts);

// countCharsAsm_ - Count the number of times each character appears in
// the array of characters charsToCount.  
//    char* charsToCount is the address of the array of characters to be counted
//    int* counts is an array of 256 integers (one for each possible character value). 
//    Upon return, counts[i] will contain the number of times the character with ASCII
//    code i appears in charsToCount.
//    int nCharsToCount is the length of the charsToCount array.  Note this array
//    is not null-terminated.  The counts array must be initialized to zeros prior
//    to calling countCharsAsm_.
extern "C" void countCharsAsm_(char* charsToCount, int* counts, int nCharsToCount);

// sumOfPreviousElementsAsm_ replaces each element in theArray with the sum of all the 
// elements that precede it in the array.  For example, if the array were {3, 5, 7, 2},
// the result would be {0, 3, 8, 15}.  The first item is always 0 because nothing precedes it,
// the second item is 3 as that is the only item that precedes it, and the third item is
// 8 because the previous two items are 3 and 5, and the last item 15, because 3 + 5 + 7
// is 15.  Note that this is easy to compute if you keep a running sum that is initially 
// 0.  So in the example, assign the initial sum (zero) to the first element, add 3 to get the second element, add 5 to 
// get the third element, and add 7 to get the fourth element.
// int* theArray is the address of the integer array to modify.
// int nElements is the number of integers in that array.
extern "C" void sumOfPreviousElementsAsm_(int* theArray, int nElements);

// countIntsAsm_ - Count the number of times each integer, which must be in the range (0-255) appears in 
// the array theIntArray. This function works similarly to countCharsAsm_, but counts occurrences of 32-bit integers,
// rather than occurrences of characters.  The integers are guaranteed to be in the range (0-255).
// int* theIntArray contains values to count
// int* counts is the address of a 256-element array that holds the counts.
// Upon return, counts[i] will contain the number of times the integer with value i
// appears in theIntArray.
extern "C" void countIntsAsm_(int* theIntArray, int* counts, int nElementsInIntArray);

// radixSortAsm_ will sort theIntArray given a scratch array of the same size as theIntArray, and 
// a counts array that has been populated with sumOfPreviousElements. The algorithm is as follows:
// 
//   for i = 0 to n-1
//       scratch[counts[theIntArray[i]]] = theIntArray[i]
//       ++counts[theIntArray[i]];
// 
//   Then copy the scratch array back to theIntArray.
//   for i = 0 to n-1
//       theIntArray[i] = scratch[i];

extern "C" void radixSortAsm_(int* theIntArray, int* scratch, int* counts, int nElementsInIntArray);

using namespace cs371Lab2Lib;

namespace cs371Lab2Test
{
	TEST_CLASS(cs371Lab2Test)
	{
	public:

		TEST_METHOD(T000_setArrayToAllZeros)
		{
			const int ARRAY_SIZE = 8;
			int cppArray[ARRAY_SIZE];
			int asmArray[ARRAY_SIZE];
			zeroCpp(cppArray, ARRAY_SIZE);
			zeroAsm_(asmArray, ARRAY_SIZE);

			for (int i = 0; i < ARRAY_SIZE; i++)
			{
				Assert::AreEqual(cppArray[i], asmArray[i]);
			}
		}

		TEST_METHOD(T001_countCharOccurrences)
		{
			const int ARRAY_SIZE = 256;
			int cppArray[ARRAY_SIZE];
			int asmArray[ARRAY_SIZE];
			string alphabet("abcdefghijklmnopqrstuvwxyz");
			alphabet = alphabet + alphabet;

			zeroCpp(cppArray, ARRAY_SIZE);
			countCharsCpp(alphabet.c_str(), cppArray, (int) alphabet.length());

			zeroAsm_(asmArray, ARRAY_SIZE);
			countCharsAsm_((char*)alphabet.c_str(), asmArray, (int) alphabet.length());

			for (int i = 0; i < ARRAY_SIZE; i++)
			{
				Assert::AreEqual(cppArray[i], asmArray[i]);
			}
			Assert::AreEqual(2, cppArray['a']);
			Assert::AreEqual(2, cppArray['z']);
		}

		TEST_METHOD(T002_countIntOccurrences)
		{
			const int RADIX = 256;
			int cppCount[RADIX];
			int asmCount[RADIX];

			const int DATA_SIZE = 1024;
			int asmNumbersLessThan256[DATA_SIZE];
			int cppNumbersLessThan256[DATA_SIZE];

			srand(234135);
			for (int i = 0; i < DATA_SIZE; i++)
			{
				asmNumbersLessThan256[i] = rand() % RADIX;
				cppNumbersLessThan256[i] = asmNumbersLessThan256[i];
			}

			zeroCpp(cppCount, RADIX);
			countIntsCpp(cppNumbersLessThan256, cppCount, DATA_SIZE);

			zeroAsm_(asmCount, RADIX);
			countIntsAsm_(asmNumbersLessThan256, asmCount, DATA_SIZE);

			for (int i = 0; i < RADIX; i++)
			{
				Assert::AreEqual(cppCount[i], asmCount[i]);
			}
		}

		TEST_METHOD(T003_sumOfPreviousElements)
		{
			const int ARRAY_SIZE = 32;
			int cppArray[ARRAY_SIZE + 1];
			int asmArray[ARRAY_SIZE + 1];
			int baseArray[ARRAY_SIZE + 1];

			for (int i = 0; i < ARRAY_SIZE; i++)
			{
				cppArray[i] = i;
				asmArray[i] = i;
				baseArray[i] = i;
			}

			// Replace the ith element of the array with the sum of all previous
			// elements in the array
			sumOfPreviousElementsCpp(cppArray, ARRAY_SIZE + 1);
			sumOfPreviousElementsAsm_(asmArray, ARRAY_SIZE + 1);

			for (int i = 0; i < ARRAY_SIZE + 1; i++)
			{
				Assert::AreEqual(cppArray[i], asmArray[i]);
			}
		}

		TEST_METHOD(T004_radixSort)
		{
			const int RADIX = 256;
			const int ARRAY_SIZE = 128;
			int cppData[ARRAY_SIZE];
			int asmData[ARRAY_SIZE];
			int baseData[ARRAY_SIZE];
			int cppScratchData[ARRAY_SIZE];
			int asmScratchData[ARRAY_SIZE];

			srand(234231);
			for (int i = 0; i < ARRAY_SIZE; i++)
			{
				cppData[i] = rand() % RADIX;
				asmData[i] = cppData[i];
				baseData[i] = cppData[i];
			}

			int cppCount[RADIX+1];
			int asmCount[RADIX+1];

			zeroCpp(cppCount, RADIX);
			countIntsCpp(cppData, cppCount, ARRAY_SIZE);

			zeroAsm_(asmCount, RADIX);
			countIntsAsm_(asmData, asmCount, ARRAY_SIZE);

			// Replace the ith element of the array with the sum of all previous
			// elements in the array
			sumOfPreviousElementsCpp(cppCount, RADIX + 1);
			sumOfPreviousElementsAsm_(asmCount, RADIX + 1);

			radixSortCpp(cppData, cppScratchData, cppCount, ARRAY_SIZE);
			radixSortAsm_(asmData, asmScratchData, asmCount, ARRAY_SIZE);
			for (int i = 1; i < ARRAY_SIZE; i++)
			{
				Assert::IsTrue(cppData[i] >= cppData[i - 1]);
				Assert::IsTrue(asmData[i] >= asmData[i - 1]);
			}
		}

	 //   TEST_METHOD(T005_timedRadixSort)
		//{
		//	const int RADIX = 256;
		//	const int ARRAY_SIZE = 128*1024*1024;
		//	int* dataToSort = new int[ARRAY_SIZE];
		//	int* scratchArray = new int[ARRAY_SIZE];

		//	srand(234231);
		//	for (int i = 0; i < ARRAY_SIZE; i++)
		//	{
		//		dataToSort[i] = rand() % RADIX;
		//	}

		//	int asmCount[RADIX + 1];

		//	zeroAsm_(asmCount, RADIX);
		//	countIntsAsm_(dataToSort, asmCount, ARRAY_SIZE);

		//	// Replace the ith element of the array with the sum of all previous
		//	// elements in the array
		//	sumOfPreviousElementsAsm_(asmCount, RADIX + 1);
		//	radixSortAsm_(dataToSort, scratchArray, asmCount, ARRAY_SIZE);

		//	for (int i = 1; i < ARRAY_SIZE; i++)
		//	{
		//		Assert::IsTrue(dataToSort[i] >= dataToSort[i - 1]);
		//	}
		//}
		//		
	 //   TEST_METHOD(T006_timedLibSort)
		//{
		//	const int RADIX = 256;
		//	const int ARRAY_SIZE = 128 * 1024 * 1024;
		//	int* dataToSort = new int[ARRAY_SIZE];
		//	int* scratchArray = new int[ARRAY_SIZE];

		//	srand(234231);
		//	for (int i = 0; i < ARRAY_SIZE; i++)
		//	{
		//		dataToSort[i] = rand() % RADIX;
		//	}

		//	std::sort(dataToSort, dataToSort + ARRAY_SIZE);

		//	for (int i = 1; i < ARRAY_SIZE; i++)
		//	{
		//		Assert::IsTrue(dataToSort[i] >= dataToSort[i - 1]);
		//	}
		//}
	};
}
