#include <iostream>
#include <algorithm>
#include "bwt.h"

using namespace std;

struct Rotation {
	int index;
	wchar_t* suffix;
};

bool cmp(Rotation rot1, Rotation rot2) {
	return wcscmp(rot1.suffix, rot2.suffix) < 0;
}

// sArray : mảng hậu tố lưu giữ vị trí của các Rotation sau khi sắp xếp.
int* buildSuffixArray(wchar_t* arr, int n, int &k) {
	int* sArray = new int[n];
	Rotation rot[n];

	for(int i = 0; i < n; i++) {
		rot[i].index = i;
		rot[i].suffix = arr + i;
	} 
	// Sắp xếp mảng rot theo suffix tăng dần.
	sort(rot, rot + n, cmp);

	for(int i = 0; i < n; i++) {
		sArray[i] = rot[i].index;
		if(sArray[i] == 0) k = i;
	}

	return  sArray;
}

wchar_t* getLastColumn(wchar_t* arr, int* sArray, int n) {
	wchar_t* bWTEncoder = new wchar_t[n];

	for(int i = 0; i < n; i++) {
		bWTEncoder[i] = arr[(sArray[i] - 1 + n)%n]; // Lấy ra vị trí cuối của Rotation tương ứng.
	}
	bWTEncoder[n] = '\0';

	return bWTEncoder;
}

// arr : mảng ký tự ban đầu trước khi mã hoá.
// bwte : mảng sau khi mã hoá theo burror wheeler transform.
// k : vị trí của chuỗi ban đầu sau khi buildSuffixArray(), thuận tiện cho việc decode.
wchar_t* bWTEncoder(wchar_t* arr, int n, int &k) {
	int* sArray;
	wchar_t* bWTEncoder;

	sArray = buildSuffixArray(arr, n, k);
	bWTEncoder = getLastColumn(arr, sArray, n);
	delete []sArray;

	return bWTEncoder;
}

