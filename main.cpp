#include <iostream>
#include <string>
#include "bwt.h"
#include "mtf.h"
#include "hfm.h"

using namespace std;

string get_ascii() {
	string ascii;

	for(int i = 0; i < 128; i++) {
		ascii += char(i);
	}

	return ascii;
}

int main(int argc, char *argv[]) {
	char text[] = "SIX.MIXED.PIXIES.SIFT.SIXTY.PIXIE.DUST.BOXES$";
	string ascii = get_ascii();
	int k;
	int n = strlen(text);

	cout << "original: " << text << endl;
	char* bwte1 = bwte(text, n, k);
	cout << "bwte1 :" << bwte1 << endl;
	string mtfe1 = mtfe(bwte1, n, ascii);
	cout << "mtfe1 :" << mtfe1 << endl;
	string hfme1 = hfme(mtfe1, mtfe1.length());
	cout << "hfme1 :" << hfme1 << endl;

	string hfmd1 = hfmd(hfme1, hfme1.length());
	cout << "hfmd1 :" << hfmd1 << endl;
	char* mtfd1 = mtfd(hfmd1, hfmd1.length(), ascii);
	cout << "mtfd1 : " << mtfd1 << endl;
	char* bwtd1 = bwtd(mtfd1, strlen(mtfd1), k);
	cout << "bwtd1" << ":" << bwtd1 << endl;

	return 0;
}