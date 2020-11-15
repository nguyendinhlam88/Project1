#include <iostream>
#include <string>
#include "mtf.h"

using namespace std;

// arr : mtfencoder, n : chiều dài mảng.
char* mtfd(string arr, int n, string ascii) {
	char* mtfd = new char[n]; // Vì vị trí của các ký tự xuất hiện trong mảng < 128 nên chuyển vị trí sang char cho tiết kiệm bộ nhớ.

	for(int i = 0; i < n; i++) {
		mtfd[i] = ascii[arr[i]];
		ascii = ascii[arr[i]] + ascii.substr(0, arr[i]) + ascii.substr(arr[i] + 1);
	}

	mtfd[n] = '\0';
	return mtfd;
}
