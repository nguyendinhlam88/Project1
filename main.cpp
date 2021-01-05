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

int main(int argc, char *argv[]) {
	wchar_t* fileContent;
	int select, sText;
	wstring encode, decode;
	string filename;

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
			writeFile("1" + filename, encode, false);
			break;
		case 2:
			wcout << "Enter filename to decode :" << endl;
			cin >> filename;
			fileContent = readFile(filename, sText, true);
			decode  = decodeText(fileContent, sText);
			writeFile("Archive.txt", decode, true);
			break;
		default :
			cout << "Vui lòng nhập 1 - 2" << endl;
	}

	return 0;
}