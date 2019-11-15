// SORTING_STEP1.C [161113]
// Supplied for use with ELEC278 Lab 6
//
// History:
// 161113	Hesham Farahat	First Release
// 171111	DA				Minor tweaking

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "maxheap.h"


void print(int *a,int *b, int n)
// Print contents of array
{
	int i;
	for (i = 0; i < n; i++)	printf("%d ", a[b[i]]);
	printf("\n");
}//print()


void swap (int *a, int *b)
// Swap two integers.  Parameters are pointers to integers, so integers
// can be anywhere.
{
	int t = *a;    *a = *b;    *b = t;
}//swap()


//*******************Insertion Sort**************************
long insertionSort(int *array, int n) {
	int i, j;
	int ctr = 0;
	for (i = 1; i < n; i++) {
		for (j = i; j > 0 && (array[j - 1] < array[j]); j--) {
			swap(&array[j], &array[j - 1]);
			ctr++;
		}
	}
	return ctr;
}


long insertionSortQ(int *array,int *b, int left, int right) {
	int i, j;
	int ctr = 0;
	for (i = left + 1; i < right + 1; i++) {
		for (j = i; j > 0 && (array[b[j - 1]] < array[b[j]]); j--) {
			
			swap(&b[j], &b[j-1]);
			printf("After insertionSortQ swap 1 :\t\t");
			print(array,b, 7);
			ctr++;
		}
	}
	return ctr;
}


//*******************Bubble Sort**************************
long bubbleSort(int* array, int n) {
	int i, j, swapped;
	long ctr = 0;

	for (i = 0; i < n; ++i) {
		swapped = 0;
		for (j = n - 1; j > i; --j) {
			if (array[j] > array[j - 1]) {
				swapped = 1;
				swap(&array[j], &array[j - 1]);
				ctr++;
			}
		}
		if (swapped == 0) break;
	}
	return ctr;
}


//*******************Quick Sort**************************

int partition(int* a, int* b, int left, int right, long* swaps) {
	int i = left;
	int j = right - 1;
	int pivot_index = left + (right - left) / 2;
	int pivot = a[b[pivot_index]];
	swap(&b[right], &b[pivot_index]);
	printf("After partition swap 1 :\t\t");
	print(a,b, 7);
	(*swaps)++;
	while (i < j) {
		while (a[b[i]] > pivot) i++;
		while (a[b[j]] < pivot) j--;
		if (i <= j) {
			swap(&b[i], &b[j]);
			printf("After partition swap 2 :\t\t");
			print(a,b, 7);
			(*swaps)++;
			i++;
			j--;
		}
	}
	int placeholder = b[right];
	printf("before partition swap 3 :\t\t");
	print(a,b, 7);
	printf("[ %d , %d, %d, %d, %d,%d,%d] \n",b[0],b[1],b[2],b[3],b[4],b[5],b[6]);
	printf("b i %d \n",b[i] );
	printf("b right %d \n",b[right] );
	printf("pivot_index %d \n",pivot_index );
	
	b[right] = b[i];
	printf("in middle of partition swap 3 :\t\t");
	print(a,b, 7);
	b[i] = placeholder;
	printf("After partition swap 3 :\t\t");
	print(a,b, 7);
	(*swaps)++;
	return i;
}


long quickSort(int* a, int* b, int left, int right) {
	long swaps = 0;
	if (right - left > 2) {
		int pivot = partition(a,b, left, right, &swaps);
		swaps += quickSort(a, b, left, pivot - 1);
		swaps += quickSort(a, b, pivot + 1, right);
	} else {
		 swaps +=insertionSortQ(a,b, left, right);
	}
	return swaps;
}

//*******************Heap Sort**************************

long heapSort(int* a, int n)
{
	long swaps = 0;
	Heap* h = heapify2(a, n, &swaps);
	
	int i;
	for (i = n - 1; i > 0; i--) {
		swap(&h->a[0], &h->a[i]);
		swaps++;
		h->last--;
		swaps += reheapDown(h, 0);
		}
	return swaps;
}

//*******************Merge Sort**************************

long merge(int*a, int start, int middle, int end, int*b) {
	int i;
	long swaps = 0;
	int j = start;
	int k = middle + 1;
	for (i = start; j <= middle && k <= end; i++) {
		if (a[j] > a[k]) {
			
			b[i] = a[j];
			j++;
		} else {
			
			b[i] = a[k];
			k++;
		}
		swaps++;
	}
	while (j <= middle){
		swaps++;
		b[i++] = a[j++];
	}
	while (k <= end){
		swaps++;
		b[i++] = a[k++];
	}
	for (i = start; i <= end; i++){
		a[i] = b[i];
	}
	return swaps;
}

//*******************Merge Sort**************************

long mergeSortR(int* a, int start, int end, int* b) {
	int		middle;
	long swaps = 0;
	if (start >= end) return 0;

	middle = start + (end - start) / 2;
	swaps += mergeSortR(a, start, middle, b);
	swaps += mergeSortR(a, middle + 1, end, b);
	swaps += merge(a, start, middle, end, b);
	return swaps;
}

long mergeSort(int* a, int n) {
	int* b = malloc(sizeof(int) * n);
	int i;
	long swaps;
	for (i = 0; i < n; i++) {
		b[i] = a[i];
	}
	swaps = mergeSortR(a, 0, n - 1, b);
	return swaps;
}
//*******************Bucket Sort**************************

void bucketSort(int *a, int n, int b) {
	int* buckets = malloc(sizeof(int) * b);
	int i, j, k;
	for (i = 0; i < b; i++) // initialize buckets array
		buckets[i] = 0;
	for (i = 0; i < n; i++) // count number of repeated data in each bucket
		buckets[a[i]]++;
	i = 0;
	for (j = 0; j < b; j++) { // loop for every bucket
		for (k = 0; k < buckets[j]; k++) {
			a[i] = j;
			i++;
			}
		}
}

//*******************Radix Sort**************************

long radixSort(int *a, int n, int p) {
	int i, j, k;
	for (k = 0; k < p; k++) {
		int count[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		int* tmp = malloc(sizeof(int) * n);
		int* offset = malloc(sizeof(int) * 10);
		for (i = 0; i < n; i++)
			count[9-((a[i] / (int) pow(10, k)) % 10)]++;//9-reverses order
		offset[0] = 0;
		for (i = 1; i < 10; i++) {
			offset[i] = 0;
			for (j = 0; j < i; j++) {
				offset[i] += count[j];
			}
		}

		for (i = 0; i < n; i++) {
			tmp[(offset[9-((a[i] / (int) pow(10, k)) % 10)]++)] = a[i]; //9- reverses order
		}
		for (i = 0; i < n; i++) {
			a[i] = tmp[i];
			}
		}
	return 0;
}


void initArray(int* a) {
	a[0] = 10;
	a[1] = 24;
	a[2] = 5;
	a[3] = 32;
	a[4] = 1;
	a[5] = 84;
	a[6] = 19;
}


int main() {
	int a[] = { 10, 24, 5, 32, 1, 84, 19 };
	int b[] = {0, 1, 2, 3, 4, 5, 6};
	int n = 7;
	long	swaps = 0;
	printf("Before   Sorting:\t\t");
	print(a,b, n);
	printf("*****\n");

	

	initArray(a);
	swaps = quickSort(a, b, 0, n - 1);
	printf("After Quick Sort:\t\t");
	print(a,b, n);
	printf("Number of swaps: %ld\n*****\n",swaps);


	

	return 0;
}