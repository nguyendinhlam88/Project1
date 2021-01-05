#include <iostream>
#include <fstream>
#include <string>
#include "io.h"
#include <codecvt>
#include <stdio.h>

using namespace std;

wchar_t* readFile(string filename, int &sText, bool isCompressed) {
	wifstream file;
	file.open(filename, ios::in);
	wchar_t* fileContent;
	unsigned int size, i, sLine;
	wchar_t ch;
	wstring line;
	unsigned int index = 0;

	if(file.is_open()) {
		file.seekg(0, ios::end);
		size = file.tellg();
		file.seekg(0);
		fileContent  = new wchar_t[size+1];
		if(fileContent == NULL) {
			exit(1);
		}
		while(1) {
			line = L"";
			getline(file, line);
			sLine = line.length();
			for(i = 0; i < sLine; i++) {
				fileContent[index] = line[i];
				index++;
			}
			if(file.eof()) {
				break;
			}
			fileContent[index] = L'\n';
			index++;
		}
		if(isCompressed == false) {
			fileContent[index] = wchar_t(1); 
			index++;
		}
		fileContent[index] = '\0';
		sText = index;
	} else {
		cout << "Error in reading " << filename << endl;
	}
	file.close();

	return fileContent;
}

void writeFile(string filename, wstring fileContent, bool isDecompressed) {
	wofstream file;
	file.open(filename, ios::out|ios::app);
	flush(file);
	unsigned int sText, count, i;

	locale::global(locale(locale(""), new codecvt_utf8<wchar_t>));
    file.imbue(locale());

	if(file.is_open()) {
		if(isDecompressed == true) file << noskipws << fileContent.substr(0, fileContent.length()-1);
		else file << noskipws << fileContent;
		file.close();
	} else {
		cout << "Error in writing to " << filename << endl;
	}
}