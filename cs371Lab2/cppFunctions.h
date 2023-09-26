namespace cs371Lab2Lib
{
	const int N_ASCII_CHARS = 128;
	void zeroCpp(int* intsToZero, int nInts);
	void countCharsCpp(const char* theString, int* counts, int nChars);
	void sumOfPreviousElementsCpp(int* array, int length);
	void countIntsCpp(int* theInts, int* counts, int nInts);
	void radixSortCpp(int* dataToSort, int* memoryAsLargeAsDataToSort, int* theCounts, int nElementsToSort);
}