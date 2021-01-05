#include <iostream>
#include "bwt.h"
#include "mtf.h"
#include "hfm.h"
#include "decode.h"
#include "encode.h"
#include <string>

using namespace std;

unsigned int toInt(wchar_t ch1, wchar_t ch2) {
	int tmp1, tmp2, tmp;
	unsigned int pos = 0;

	tmp1 = int(ch1);
	tmp2 = int(ch2);
	for(int i = 14; i >= 0; i--) {
		tmp = pow(2, i);
		if(tmp1 >= tmp) {
			pos += pow(2, 15 + i);
			tmp1 -= tmp;
		} 
		if(tmp2 >= tmp) {
			pos += tmp;
			tmp2 -= tmp;
		}
	}

	return pos;
}

wchar_t* decodeText(wchar_t* text, int sText) {
	unsigned int sHuffman, pos, len;
	wstring hfmDecoder1;
	wchar_t *unicode, *mTFDecoder1, *bWTDecoder1;

	unicode = getUnicode();
	if(text[0] == L'0') {
		pos = text[sText-1];
		text = text + 1;
		text[sText-1] = L'\0';
		sText -= 2;
	} else {
		pos = toInt(text[sText-2], text[sText-1]);
		text[sText-2] = L'\0';
		sText -= 2;
	}

	hfmDecoder1 = hfmDecoder(text, sText);
	sHuffman = hfmDecoder1.length();
	mTFDecoder1 = mTFDecoder(hfmDecoder1, unicode, sHuffman);
	bWTDecoder1 = bWTDecoder(mTFDecoder1, sHuffman, pos);

	return bWTDecoder1;
}