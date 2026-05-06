#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <string>
#include "../include/algorithms/mergesort.h"
#include "../include/algorithms/quicksort.h"
#include "../include/algorithms/introsort.h"
#include "../include/algorithms/heapsort.h"

using namespace std;



void require(bool cond, const char* msg)
{
	if (!cond)
	{
		cerr << "FAIL: " << msg << "\n";
		exit(1);
	}
}

void print(const std::string& label, const std::vector<int>& v)
{
	cout << label << ": [";
	for (int x : v) cout << x << " ";
	cout << "]\n";
}



int main()
{
	vector<int> input = { 5, -1, 3,3, 8, 16, 0, -4, -1, 2, 9 };
	auto expected = input;

	std::sort(expected.begin(), expected.end());

	cout << "#####################\n";
	cout << "MERGE SORT TEST\n";
	cout << "#####################\n\n";

	{
		auto data = input;

		print("BEFORE", data);

		MergeSort<int> structure;
		structure.sort(data.begin(), data.end());
		print("SORTED", data);
		require(data == expected, "MergeSort");
	}

	cout << "-------------------------------------------------------\n\n";

	cout << "#####################\n";
	cout << "QUICK SORT TEST\n";
	cout << "#####################\n\n";

	{
		auto data = input;
		print("BEFORE", data);
		QuickSort<int> structure;
		structure.sort(data.begin(), data.end());
		print("SORTED", data);
		require(data == expected, "QuickSort");
	}

	cout << "-------------------------------------------------------\n\n";

	cout << "#####################\n";
	cout << "HEAP SORT TEST\n";
	cout << "#####################\n\n";

	{
		auto data = input;
		print("BEFORE", data);
		HeapSort<int> structure;
		structure.sort(data.begin(), data.end());
		print("SORTED", data);
		require(data == expected, "HeapSort");
	}

	cout << "-------------------------------------------------------\n\n";

	cout << "#####################\n";
	cout << "INTRO SORT TEST\n";
	cout << "#####################\n\n";

	{
		auto data = input;
		print("BEFORE", data);
		IntroSort<int> structure;
		structure.sort(data.begin(), data.end());
		print("SORTED", data);
		require(data == expected, "IntroSort");
	}

	cout << "-------------------------------------------------------\n\n";

	cout << "STATUS: OK\n";

	cout << "-------------------------------------------------------\n\n";
	return 0;
}