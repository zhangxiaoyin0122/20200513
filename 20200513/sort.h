#pragma once
void Swap(int* array, int l, int r);

int partion(int* array, int begin, int end);

void quickSort(int* array, int begin, int end);

void merge(int* array, int begin, int mid, int end,int* tmp);

void mergeNor(int* array, int n);

void countSort(int* array, int n);
