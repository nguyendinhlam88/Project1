#include <iostream>
#include "bwt.h"
#include "mtf.h"
#include "hfm.h"
#include "encode.h"
#include "decode.h"
#include "io.h"
#include <codecvt>

using namespace std;

void menu() {
	wcout <<" ----------- " << endl;
	wcout <<"|1. Encode  |" << endl; 
	wcout <<"|2. Decode  |" << endl;
	wcout <<" ----------- " << endl;
}

wstring toString(wchar_t* arr, int sText) {
	int sArr;  
	wstring temp;

	temp = L"";
	for(int i = 0; i < sText; i++) {
		temp += arr[i];
	}

	return temp;
}

int main(int argc, char *argv[]) {
	wchar_t* fileContent;
	int select, sText, pos1 = 0, pos2 = 0;
	wstring encode, decode;
	string filename, ioName;

	locale::global(locale(locale(""), new codecvt_utf8<wchar_t>));

    wcin.imbue(locale());
    wcout.imbue(locale());

	menu();
	cout << "Nhấn 1 hoặc 2 để chọn : ";
	wcin >> select;

	switch(select) {
		case 1: 
			wcout << "Enter filename to encode :" << endl;
			cin >> filename;
			fileContent = readFile(filename, sText, false);
			encode = encodeText(fileContent, sText);
			writeFile(filename + ".b2zip", encode, false); 
			break;
		case 2:
			wcout << "Enter filename to decode :" << endl;
			cin >> filename;
			fileContent = readFile(filename, sText, true);
			pos1 = filename.find(".");
			pos2 = filename.find(".", pos1+1);
			ioName = filename.substr(0, pos1) + "(1)" + filename.substr(pos1, pos2-pos1); 
			decode  = decodeText(toString(fileContent, sText));
			writeFile(ioName, decode, true);
			break;
		default :
			cout << "Vui lòng nhập 1 - 2" << endl;
	}

	return 0;
}