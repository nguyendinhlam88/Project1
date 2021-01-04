#include <iostream>
#include <string>
#include "mtf.h"

using namespace std;

// arr : chuỗi mTFEncoder.
wchar_t* mTFDecoder(wstring arr, wchar_t* unicode, int n) {
	wchar_t* mTFDecoder;

	mTFDecoder = new wchar_t[n];
	for(int i = 0; i < n; i++) {
		if(arr[i] == 983039) arr[i] = 8;
		mTFDecoder[i] = unicode[arr[i]];
		changeUnicode(unicode, arr[i]);
	}
	mTFDecoder[n] = '\0';

	return mTFDecoder;
}
