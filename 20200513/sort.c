#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
void Swap(int* array, int l, int r) {
	int tmp = array[l];
	array[l] = array[r];
	array[r] = tmp;
}

int partion(int* array, int begin, int end) {
	int prev = begin;
	int cur = prev + 1;
	int key = array[begin];
	while (cur <= end) {
		while (array[cur] < key && ++prev != cur) {
			Swap(array, prev, cur);
		}
		cur++;
	}
	Swap(array, prev, begin);
	return prev;
}
void quickSort(int* array, int begin, int end) {
	if (begin >= end)
		return;
	int keypos = partion(array, begin, end);
	quickSort(array, begin, keypos - 1);
	quickSort(array, keypos + 1, end);
}

void merge(int* array, int begin, int mid, int end,int* tmp) {
	int begin1 = begin, end1 = mid, begin2 = mid + 1, end2 = end;
	int idx = begin;
	while (begin1 <= end1 && begin2 <= end2) {
		if (array[begin1] > array[begin2])
			tmp[idx++] = array[begin2++];
		else
			tmp[idx++] = array[begin1++];
	}
	if (begin1 <= end1)
		memcpy(tmp + idx, array + begin1, sizeof(int)*(end1 - begin1 + 1));
	if (begin2 <= end2)
		memcpy(tmp + idx, array + begin2, sizeof(int)*(end2 - begin2 + 1));
	memcpy(array + begin, tmp + begin, sizeof(int)*(end - begin + 1));
}

void mergeNor(int* array, int n) {
	int* tmp = (int*)malloc(sizeof(int)*n);
	int k = 1;
	while (k < n) {
		for (int i = 0; i < n; i += 2 * k) {
			int begin = i;
			int mid = i + k - 1;
			if (mid >= n-1)
				continue;
			int end = i + 2 * k - 1;
			if (end > n - 1)
				end = n - 1;
			merge(array, begin, mid, end,tmp);
		}
		k *= 2;
	}
}

void countSort(int* array, int n) {
	int max = array[0], min = array[0];
	for (int i = 1; i < n; i++) {
		if (array[i] > max)
			max = array[i];
		if (array[i] < min)
			min = array[i];
	}
	int range = max - min + 1;
	int* tmp = (int*)malloc(sizeof(int)*range);
	memset(tmp, 0, sizeof(int)*range);
	for (int i = 0; i < n; i++) {
		tmp[array[i] - min]++;
	}
	int idx = 0;
	for (int i = 0; i < range; i++) {
		while (tmp[i]--) {
			array[idx++] = i + min;
		}
	}
	free(tmp);
}