#include "sorting.h"

#include <iostream>

namespace sorting {

	//************
	// QuickSort *
	//************      

	int partition(vector<int>& arr, int left, int right) {
		int x = arr[right];
		int i = left - 1;
		for (int j = left; j <= right - 1; j++) {
			if (arr[j] <= x) {
				i++;
				swap(arr[i], arr[j]);
			}
		}
		swap(arr[i + 1], arr[right]);
		return i + 1;
	}

	void QuickSort(vector<int>& arr, int left, int right) {

		if (left < right) {
			int mid = partition(arr, left, right);
			QuickSort(arr, left, mid - 1);
			QuickSort(arr, mid + 1, right);
		}

	}
	//************
	// MergeSort *
	//************

	//***************************
	// implement mergesort here *
	//***************************

	void Merge(vector<int>& a, vector<int>& b, int leftPos, int rightPos, int rightEnd) {
		int leftEnd = rightPos - 1;
		int tmpPos = leftPos;
		int n = rightEnd - leftPos + 1;

		while (leftPos <= leftEnd && rightPos <= rightEnd) {
			if (a[leftPos] <= a[rightPos]) {
				b[tmpPos] = a[leftPos];
				leftPos++;
			}
			else {
				b[tmpPos] = a[rightPos];
				rightPos++;
			}
			tmpPos++;
		}

		while (leftPos <= leftEnd) {
			b[tmpPos++] = a[leftPos++];
		}
		while (rightPos <= rightEnd) {
			b[tmpPos++] = a[rightPos++];
		}
		int i = 0;
		while (i < n) {
			a[rightEnd] = b[rightEnd];
			rightEnd--;
			i++;
		}
	}

	void MergeSort(vector<int>& a, vector<int>& b, int low, int high) {
		if (low < high) {
			int q = (low + high) / 2;
			MergeSort(a, b, low, q);
			MergeSort(a, b, q + 1, high);
			Merge(a, b, low, q + 1, high);
		}
	}


	
	//************
	// Heapsort  *
	//************
	int leftChild(int i) {
		return 2 * i + 1;
	}


	void percDown(vector<int>& a, int p, int n) {
		int child = p;
		int tmp = a[p];
		int j = p;
		while (leftChild(j) < n) {
			child = leftChild(j);
			if ((child != n - 1) && a[child] < a[child + 1]) 
				child = child + 1;
			if (tmp < a[child]) 
				swap(a[j], a[child]);
			else 
				break;
			j = child;
		} 
		a[j] = tmp;
	}

	void HeapSort(vector<int>& a, int n) {

		//***************************
		// implement heapsort here *
		//***************************

		int i = n / 2;
		while (i >= 0) {
			percDown(a, i, n);
			i--;
		}
		int j = n - 1;
		while (j > 0) {
			swap(a[0], a[j]);
			percDown(a, 0, j);
			j--;
		}
	}




	//************
	// Shellsort *
	//************
	void hibbard(vector<int>& h, int length) {
		h.push_back(-1);
		for (int i = 1; i <= 5 * length; i = 2 * i + 1) // ausgangskriterien ? 
			h.push_back(i); 
	}


	void ShellSort(vector<int>& a, int n)
	{
		vector<int> hib;
		hibbard(hib, n);
		int hib_start = 0;

		while (hib.at(hib_start) < n) hib_start++;

		while (hib.at(hib_start) != -1) {
			int gap = hib.at(hib_start);
			for (int i = gap; i < n; i++) {
				int tmp = a[i];
				int j = i;
				for (; j >= gap && tmp < a[j - gap]; j -= gap) {
					a[j] = a[j - gap];
				}
				a[j] = tmp;
			}
			hib_start--;
		}
	}

	void randomizeVector(vector<int>& array, int n) {
		array.resize(n);

		for (unsigned int i = 0; i < array.size(); i++)
			array[i] = rand() % 1000000;
	}
}





