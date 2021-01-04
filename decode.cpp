#include <iostream>
#include "bwt.h"
#include "mtf.h"
#include "hfm.h"
#include "decode.h"
#include "encode.h"
#include <string>

using namespace std;

wchar_t* decodeText(wstring text) {
	int sHuffman, pos;
	wstring hfmDecoder1;
	wchar_t *unicode, *mTFDecoder1, *bWTDecoder1;

	unicode = getUnicode();
	pos = text[text.length()-1] - 48;
	text = text.substr(0, text.length()-1);
	hfmDecoder1 = hfmDecoder(text);
	sHuffman = hfmDecoder1.length();
	mTFDecoder1 = mTFDecoder(hfmDecoder1, unicode, sHuffman);
	bWTDecoder1 = bWTDecoder(mTFDecoder1, sHuffman, pos);
	return bWTDecoder1;
}