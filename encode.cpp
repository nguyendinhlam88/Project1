#include <iostream>
#include "bwt.h"
#include "mtf.h"
#include "hfm.h"
#include "encode.h"
#include <string>

using namespace std;

wchar_t* getUnicode() {
	wchar_t* unicode;
	int idx;

	idx = 0;
	unicode = new wchar_t[319137];
	for(int i = 0; i < 55204; i++) {
		if(i == 8) continue;
		else {
			unicode[idx] = wchar_t(i);
			idx++;
		}
	}

	for(int i = 63744; i < 262144; i++) {
		unicode[idx] = wchar_t(i);
		idx++;
	}

	for(int i = 917504; i < 983039; i++) {
		unicode[idx] = wchar_t(i);
		idx++;
	}
	unicode[idx] = '\0';

	return unicode;
}

wstring encodeText(wchar_t* text, int sText) {
	int pos, sMTF;
	wchar_t *bWTEncoder1, *unicode, *mTFEncoder1;
	wstring hfmEncoder1;

	unicode = getUnicode();
	bWTEncoder1 = bWTEncoder(text, sText, pos);
	mTFEncoder1 = mTFEncoder(bWTEncoder1, unicode, sText);
	hfmEncoder1 = hfmEncoder(mTFEncoder1, sText);
	hfmEncoder1 += wchar_t(pos+48);

	return hfmEncoder1;
}
