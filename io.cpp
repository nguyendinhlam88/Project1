#include <iostream>
#include <fstream>
#include <string>
#include "io.h"
#include <codecvt>
#include <stdio.h>

using namespace std;

wchar_t* readFile(string filename, int &sText, bool isCompressed) {
	wfstream file;
	file.open(filename, ios::in);
	wchar_t* fileContent;
	int end, size;
	wchar_t ch;
	int index = 0;

	if(file.is_open()) {
		file.seekg(0, ios::end);
		end = file.tellg();
		file.seekg(0);
		size = end;
		fileContent  = new wchar_t[size];
		while(1) {
			file >> noskipws >> ch;
			if(file.eof()) {
				break;
			}
			fileContent[index] = ch;
			index++;
		}
		if(isCompressed == false) {
			fileContent[index] = wchar_t(1); 
			index++;
		}
		fileContent[index] = '\0';
		sText = index;
		file.close();
	} else {
		cout << "Error in reading " << filename << endl;
	}

	return fileContent;
}

void writeFile(string filename, wstring fileContent, bool isDecompressed) {
	wofstream file;
	file.open(filename);
	flush(file);
	int sText;

	locale::global(locale(locale(""), new codecvt_utf8<wchar_t>));
    file.imbue(locale());
    sText = fileContent.length();

	if(file.is_open()) {
		if(isDecompressed == true) file << noskipws << fileContent.substr(0, fileContent.length()-1);
		else file << noskipws << fileContent;
		file.close();
	} else {
		cout << "Error in writing to " << filename << endl;
	}
}