#include <iostream>
#include <algorithm>
#include "bwt.h"

using namespace std;

struct Rotation {
	 int index;
	wchar_t* suffix;
};

inline int cmp(wchar_t* suffix1, wchar_t* suffix2) {
	return wcscmp(suffix1, suffix2);
}

void merge(Rotation* rot,  int beg,  int mid,  int end) {
	 int n1, n2, idx = 0, l = 0, r = 0, k = beg;
	 int chkCMP;

	n1 = mid - beg + 1;
	n2 = end - mid;
	Rotation* lRot = new Rotation[n1];
	Rotation* rRot = new Rotation[n2];

	for( int i = beg; i <= mid; i++) {
		lRot[idx].index = rot[i].index;
		lRot[idx].suffix = rot[i].suffix;
		idx++;
	}

	idx = 0;
	for( int i = mid+1; i <= end; i++) {
		rRot[idx].index = rot[i].index;
		rRot[idx].suffix = rot[i].suffix;
		idx++;
	}

	while(l < n1 && r < n2) {
		chkCMP = cmp(lRot[l].suffix, rRot[r].suffix);
		if(chkCMP < 0) {
			rot[k].index = lRot[l].index;
			rot[k].suffix = lRot[l].suffix;;
			l++;
			k++;
		} else if(chkCMP > 0) {
			rot[k].index = rRot[r].index;
			rot[k].suffix = rRot[r].suffix;
			r++;
			k++;
		} else {
			rot[k].index = lRot[l].index;
			rot[k].suffix = lRot[l].suffix;
			l++;
			k++;
			rot[k].index = rRot[r].index;
			rot[k].suffix = rRot[r].suffix;
			r++;
			k++;
		}
	}

	while(l < n1) {
		rot[k].index = lRot[l].index;
		rot[k].suffix = lRot[l].suffix;
		l++;
		k++;
	}

	while(r < n2) {
		rot[k].index = rRot[r].index;
		rot[k].suffix = rRot[r].suffix;
		r++;
		k++;
	}

	delete []lRot;
	delete []rRot;
}

void mergeSort(Rotation* rot,  int beg,  int end) {
	 int mid;

	if(beg == end) return;
	else if(beg < end){
		mid = (beg + end)/2;
		mergeSort(rot, beg, mid);
		mergeSort(rot, mid+1, end);
		merge(rot, beg, mid, end);
	}
}

// sArray : mảng hậu tố lưu giữ vị trí của các Rotation sau khi sắp xếp.
 int* buildSuffixArray(wchar_t* arr,  int n, unsigned int &k) {
	 int* sArray = new  int[n];
	Rotation* rot = new Rotation[n];

	for( int i = 0; i < n; i++) {
		rot[i].index = i;
		rot[i].suffix = arr + i;
	} 

	mergeSort(rot, 0, n-1);

	for( int i = 0; i < n; i++) {
		sArray[i] = rot[i].index;
		if(sArray[i] == 0) k = i;
	}

	delete []rot;
	return  sArray;
}

wchar_t* getLastColumn(wchar_t* arr,  int* sArray,  int n) {
	wchar_t* bWTEncoder = new wchar_t[n];

	for( int i = 0; i < n; i++) {
		bWTEncoder[i] = arr[(sArray[i] - 1 + n)%n]; // Lấy ra vị trí cuối của Rotation tương ứng.
	}
	bWTEncoder[n] = '\0';

	return bWTEncoder;
}

/* arr : mảng ký tự ban đầu trước khi mã hoá.
 * bwte : mảng sau khi mã hoá theo burror wheeler transform.
 * k : vị trí của chuỗi ban đầu sau khi buildSuffixArray(), thuận tiện cho việc decode.
 */
wchar_t* bWTEncoder(wchar_t* arr,  int n, unsigned int &k) {
	 int* sArray;
	wchar_t* bWTEncoder;

	sArray = buildSuffixArray(arr, n, k);
	bWTEncoder = getLastColumn(arr, sArray, n);
	delete []sArray;
	delete []arr;
	
	return bWTEncoder;
}

