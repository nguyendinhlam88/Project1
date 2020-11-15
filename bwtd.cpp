#include <iostream>
#include <map>
#include "bwt.h"

using namespace std;

/* Hàm trả về 1 mảng có tính chất : row[i] = vị 
trí suffix tiếp theo khi xoay 1 ký tự sang trái trong ma trận xoay đã sắp xếp: 'abc' -> 'bca' */
int* compute_next(char* arr, int n) {
	char sorted_arr[n];
	strcpy(sorted_arr, arr);
	sort(sorted_arr, sorted_arr + n);
	int* next = new int[n];
	map<char, int> count; // Số ký tự (a) đã xuất hiện trước ký tự đang xét (a).

	for(int i = 0; i < n; i++) {
		int k = count[sorted_arr[i]];
		char* loc = strchr(arr, sorted_arr[i]);

		if(k == 0) {
			next[i] = loc - arr;
		} else {
			for(int j = 1; j <= k; j++){ 
				loc = strchr(loc + 1, sorted_arr[i]);
			}
			next[i] = loc - arr;
		}

		count[sorted_arr[i]] += 1;
	}

	return next;
}

char* bwtd(char* arr, int n, int k) {
	char* bwtd = new char[n];
	int* next = compute_next(arr, n);

	for(int i = 0; i < n; i++) {
		k = next[k];
		bwtd[i] = arr[k];
	}
	bwtd[n] = '\0';
	delete []next;

	return bwtd;
}