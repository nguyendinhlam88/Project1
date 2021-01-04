#include <iostream>
#include <map>
#include "bwt.h"

using namespace std;

int findCharLoc(wchar_t* arr, wchar_t ch, int n, int start) {
	for(int i = start; i < n; i++) {
		if(arr[i] == ch) return i;
	}

	return -1;
}

/* next[i] với i là vị trí của ví dụ 'abc', 
next[i] : 'bca' : chuỗi chuyển sang trái 1 ký tự */
int* computeNext(wchar_t* arr, int n) {
	wchar_t sortArray[n], firstChar;
	int* next; // Vị trí sau khi quay 1 
	map<wchar_t, int> begLoc; // Lưu lại vị trí đầu của các ký tự.
	int loc;

	for(int i = 0; i < n; i++) {
		sortArray[i] = arr[i];
	}
	sort(sortArray, sortArray + n);
	next = new int[n];

	for(int i = 0; i < n; i++) {
		if(sortArray[i] == firstChar) loc = findCharLoc(arr, sortArray[i], n, begLoc[sortArray[i]] + 1);
		else if(begLoc[sortArray[i]] == 0) {
			loc = findCharLoc(arr, sortArray[i], n, 0);
			if(loc == 0) firstChar = sortArray[i];
		} else loc = findCharLoc(arr, sortArray[i], n, begLoc[sortArray[i]] + 1);
		begLoc[sortArray[i]] = loc;
		next[i] = loc;
		}

	return next;
}

// Do pos : vị trí mảng ban đầu, xoay 1 ký tự thì ra ký tự đầu tiên, cứ xây dựng tiếp tục đến ký tự cuối.
wchar_t* getBWTDecoder(wchar_t* arr, int n, int* next, int pos) {
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
wchar_t* bWTDecoder(wchar_t* arr, int n, int pos) {
	int* next;
	wchar_t* bWTDecoder;

	next = computeNext(arr, n);
	bWTDecoder = getBWTDecoder(arr, n, next, pos);
	delete []next;

	return bWTDecoder;
}