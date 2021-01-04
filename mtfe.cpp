#include <iostream>
#include <string>
#include "mtf.h"

using namespace std;

int findCharLoc(wchar_t* unicode, wchar_t ch) {

	for(int i = 0; i < 319137; i++) {
		if(unicode[i] == ch) return i;
	}

	return -1;
}

void changeUnicode(wchar_t* unicode, int loc) {
	wchar_t ch;

	ch = unicode[loc];
	for(int i = loc; i != 0; i--) {
		unicode[i] = unicode[i-1];
	}
	unicode[0] = ch;
} 

// arr : mảng ban đầu(Burror Wheeler Transform, unicode : wstring các ký tự của bài đã dùng.
wchar_t* mTFEncoder(wchar_t* arr, wchar_t* unicode, int n) {
	wchar_t* mTFEncoder; // Vì vị trí của các ký tự xuất hiện trong mảng < 128 nên chuyển vị trí sang wchar_t cho tiết kiệm bộ nhớ.
	int loc;

	mTFEncoder = new wchar_t[n];
	for(int i = 0; i < n; i++) {
		loc = findCharLoc(unicode, arr[i]);
		if(loc == 8) mTFEncoder[i] = wchar_t(983039);
		else mTFEncoder[i] = wchar_t(loc);
		if (loc != 0) changeUnicode(unicode, loc);
	}

	return mTFEncoder;
}
