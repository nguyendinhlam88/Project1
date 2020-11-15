#include <iostream>
#include <algorithm>
#include "bwt.h"

using namespace std;

struct rotation {
	int index;
	char* suffix;
};

bool cmp(rotation rot1, rotation rot2) {
	return strcmp(rot1.suffix, rot2.suffix) < 0;
}

int* build_suffix_array(char* arr, int n, int &k) {
	int* suffix_array = new int[n];
	rotation rot[n];

	for(int i = 0; i < n; i++) {
		rot[i].index = i;
		rot[i].suffix = arr + i;
	} 
	// Sort rot array by item's suffix. Le
	sort(rot, rot + n, cmp);

	for(int i = 0; i < n; i++) {
		suffix_array[i] = rot[i].index;
		if(suffix_array[i] == 0) k = i;
	}

	return  suffix_array;
}

char* get_last_column(char* arr, int* suffix_array, int n) {
	char* bwt = new char[n];

	for(int i = 0; i < n; i++) {
		bwt[i] = arr[(suffix_array[i] - 1 + n)%n];
	}
	bwt[n] = '\0';
	return bwt;
}

char* bwte(char* arr, int n, int &k) {
	int* suffix_array = build_suffix_array(arr, n, k);
	char* bwte = get_last_column(arr, suffix_array, n);
	delete []suffix_array;
	return bwte;
}

