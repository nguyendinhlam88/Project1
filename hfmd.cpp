#include <iostream>
#include <cmath>
#include <map>
#include <stack>
#include <string>
#include "hfm.h"

using namespace std;

void parseHuffman(wchar_t* huffman, int sText, wchar_t* &header, int sHeader, wchar_t* &hfmChar) {
	int idx1 = 0, idx2 = 0;

	header = huffman + 3;
	hfmChar = huffman + 3 + sHeader;
}

// Chuyển đầu vào sang mã nhị phân.
wstring toBin(wchar_t* hfmChar, int size, int nChar32, int nAddBit) {
	unsigned int index, value, temp;
	wstring hfmCode;

	index = 0;
	for(int i = 0; i < size; i++) {
		value = hfmChar[i];
		if(value == 983039) value = 8;

		for(int j = 0; j != 32; j++) {
			if(nChar32 == 0 && j == 15) break;
			if(index == (32 * nChar32 + (size - nChar32)*15 - nAddBit)) return hfmCode;
			if(nChar32 > 0) {
				temp = pow(2, 31-j); 
				nChar32 -= 1;
			} else temp = pow(2, 14-j);
			if(value >= temp) {
				hfmCode += L'1';
				value -= temp;
			} else hfmCode += L'0';
			index++;
		}
	}

	return hfmCode;
}

void buildDict(wchar_t* header, int sHeader, map<wstring, wchar_t> &dict) {
	stack<wstring> st;
	int size, dem;
	wstring temp;

	temp = L"";
	dem = 0;
	for(int i = 0; i < sHeader; i++) { // Bắt đầu từ 1 để xét đến stack rỗng chuyển sang nhánh phải của rỗng.
		if(st.empty() && dem < 3) {
			dem++;
			if(dem == 2) {
				temp = L"1";
				st.push(L"1");
			}
		}
		if(header[i] == L'0') {
			temp += L'0';
			st.push(temp);
		} else {
			dict[temp] = header[i+1];
			i++;
			st.pop();
			if(st.empty()) continue;
			temp = st.top() + L'1';
			st.pop();
			st.push(temp);
		}
	}
}

wstring decodeHuffman(wstring hfmCode, map<wstring, wchar_t> dict) {
	int size;
	wstring hfmDecode, temp;

	size = hfmCode.length();
	for(int i = 0; i < size; i++)  {
		temp += hfmCode[i];
		if(dict.count(temp) != 0) {
			hfmDecode += dict[temp];
			temp = L"";
		}
	}

	return hfmDecode;
}

wstring hfmDecoder(wchar_t* huffman, int sText) {
	int sHeader, nAddBit, nChar32;
	wchar_t pos;
	map<wstring, wchar_t> dict;	
	wchar_t *hfmChar, *header;
	wstring hfmDecode, hfmCode;

	sHeader = huffman[0];
	nChar32 = huffman[1] - 48;
	nAddBit = huffman[2]; // Số lượng bit thêm vào cuối.
	parseHuffman(huffman, sText, header, sHeader, hfmChar);
	hfmCode = toBin(hfmChar, (sText-sHeader-3), nChar32, nAddBit);
	buildDict(header, sHeader, dict);
	hfmDecode = decodeHuffman(hfmCode, dict);

	// delete []huffman;
	return hfmDecode;
}

