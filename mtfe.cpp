#include <iostream>
#include <string>
#include "mtf.h"

using namespace std;

// arr : bwt array, n : chiều dài mảng.
string mtfe(char* arr, int n, string ascii) {
	string mtfe; // Vì vị trí của các ký tự xuất hiện trong mảng < 128 nên chuyển vị trí sang char cho tiết kiệm bộ nhớ.

	for(int i = 0; i < n; i++) {
		int loc = ascii.find(arr[i]);
		mtfe += char(loc);
		if (loc != 0) {
			ascii = ascii[loc] + ascii.substr(0, loc) + ascii.substr(loc + 1);
		}
	}

	return mtfe;
}
