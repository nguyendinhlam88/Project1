#include <iostream>
#include <map>
#include "bwt.h"

using namespace std;

 int findCharLoc(wchar_t* arr, wchar_t ch,  int n,  int start) {
	for( int i = start; i < n; i++) {
		if(arr[i] == ch) return i;
	}

	return -1;
}

void merge(wchar_t* arr,  int beg,  int mid,  int end) {
	 int n1, n2, idx = 0, l = 0, r = 0, k = beg;

	n1 = mid - beg + 1;
	n2 = end - mid;
	wchar_t* lCharArray = new wchar_t[n1];
	wchar_t* rCharArray = new wchar_t[n2];

	for( int i = beg; i <= mid; i++) {
		lCharArray[idx] = arr[i];
		idx++;
	}

	idx = 0;
	for( int i = mid+1; i <= end; i++) {
		rCharArray[idx] = arr[i];
		idx++;
	}

	while(l < n1 && r < n2) {
		if(lCharArray[l] < rCharArray[r]) {
			arr[k] = lCharArray[l];
			l++;
			k++;
		} else if(lCharArray[l] > rCharArray[r]) {
			arr[k] = rCharArray[r];
			r++;
			k++;
		} else {
			arr[k] = lCharArray[l];
			l++;
			k++;
			arr[k] = rCharArray[r];
			r++;
			k++;
		}
	}

	while(l < n1) {
		arr[k] = lCharArray[l];
		l++;
		k++;
	}

	while(r < n2) {
		arr[k] = rCharArray[r];
		r++;
		k++;
	}

	delete []lCharArray;
	delete []rCharArray;
}

void mergeSort(wchar_t* arr,  int beg,  int end) {
	 int mid;

	if(beg == end) return;
	else if(beg < end){
		mid = (beg + end)/2;
		mergeSort(arr, beg, mid);
		mergeSort(arr, mid+1, end);
		merge(arr, beg, mid, end);
	}
}

/* next[i] với i là vị trí của ví dụ 'abc', 
next[i] : 'bca' : chuỗi chuyển sang trái 1 ký tự */
 int* computeNext(wchar_t* arr,  int n) {
	wchar_t firstChar;
	wchar_t* sortArray = new wchar_t[n];
	 int* next; // Vị trí sau khi quay 1 
	map<wchar_t,  int> begLoc; // Lưu lại vị trí đầu của các ký tự.
	 int loc;

	for( int i = 0; i < n; i++) sortArray[i] = arr[i];
	
	mergeSort(sortArray, 0, n-1);

	next = new  int[n];

	for( int i = 0; i < n; i++) {
		if(sortArray[i] == firstChar) loc = findCharLoc(arr, sortArray[i], n, begLoc[sortArray[i]] + 1);
		else if(begLoc[sortArray[i]] == 0) {
			loc = findCharLoc(arr, sortArray[i], n, 0);
			if(loc == 0) firstChar = sortArray[i];
		} else loc = findCharLoc(arr, sortArray[i], n, begLoc[sortArray[i]] + 1);
		begLoc[sortArray[i]] = loc;
		next[i] = loc;
		}

	delete []sortArray;
	return next;
}

// Do pos : vị trí mảng ban đầu, xoay 1 ký tự thì ra ký tự đầu tiên, cứ xây dựng tiếp tục đến ký tự cuối.
wchar_t* getBWTDecoder(wchar_t* arr, int n, int* next, unsigned int pos) {
	wchar_t* bWTDecoder;

	bWTDecoder = new wchar_t[n];
	for(int i = 0; i < n; i++) {
		pos = next[pos];
		bWTDecoder[i] = arr[pos];
	}
	bWTDecoder[n] = '\0';

	return bWTDecoder;
}

// pos : vị trí mảng ban đầu(=k).
wchar_t* bWTDecoder(wchar_t* arr,  int n, unsigned int pos) {
	 int* next;
	wchar_t* bWTDecoder;

	next = computeNext(arr, n);
	bWTDecoder = getBWTDecoder(arr, n, next, pos);
	delete []next;

	return bWTDecoder;
}