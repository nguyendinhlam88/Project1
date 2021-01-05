#include <iostream>
#include "bwt.h"
#include "mtf.h"
#include "hfm.h"
#include "encode.h"
#include <string>

using namespace std;

wchar_t* getUnicode() {
	wchar_t* unicode;
	int idx = 0;

	unicode = new wchar_t[325542];
	for(int i = 0; i < 55204; i++) {
		if(i == 8) continue;
		else {
			unicode[idx] = wchar_t(i);
			idx++;
		}
	}

	for(int i = 57344; i < 262144; i++) {
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

void toChar(unsigned int pos, wchar_t &ch1, wchar_t &ch2) {
	unsigned int tmp1, tmp2 = 0, tmp3 = 0;

	for(int i = 0; i < 30; i++) {
		tmp1 = pow(2, 29-i);
		if(pos >= tmp1) {
			if(i < 15) tmp2 += pow(2, 14-i);
			if(i > 14) tmp3 += tmp1;		
			pos -= tmp1;
		}
	}
	ch1 = wchar_t(tmp2);
	ch2 = wchar_t(tmp3);
}

wstring encodeText(wchar_t* text, int sText) {
	unsigned int pos;
	int sMTF;
	wchar_t *bWTEncoder1, *unicode, *mTFEncoder1;
	wstring hfmEncoder1;
	wchar_t ch1, ch2;
	unicode = getUnicode();
	bWTEncoder1 = bWTEncoder(text, sText, pos);
	mTFEncoder1 = mTFEncoder(bWTEncoder1, unicode, sText);
	hfmEncoder1 = hfmEncoder(mTFEncoder1, sText);
	if(((pos > 55203 && pos < 57344) || (pos > 262144 && pos < 917504) || pos > 983039)) {
		toChar(pos, ch1, ch2);
		hfmEncoder1 = hfmEncoder1 + ch1 + L"" + ch2;
	} else {
		hfmEncoder1 = L"0" + hfmEncoder1 + wchar_t(pos);
	}

	return hfmEncoder1;
}