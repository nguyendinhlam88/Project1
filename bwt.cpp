#include <iostream>
#include <algorithm>
#include <string.h>
#include <map>

using namespace std;

struct Rotation{
	int index;
	char* suffix;
};

bool cmpRotation(Rotation tmp1, Rotation tmp2){
	int cmp = strcmp(tmp1.suffix, tmp2.suffix);
	if(cmp >= 0) return false;
	return true;
}

void rotate(char* &text){
	int n = strlen(text);
	char temp = text[0];
	for(int i = 0; i < n; i++){
		if(i == n-1) text[n-1] = temp;
		else text[i] = text[i+1];
	}
}

int* computeSuffixArrayIndex(char* text, int n, int &k){
	Rotation temp[n];
	int* suffix_arr_index = new int[n];

	//Mảng hậu tố.
	for(int i = 0; i < n; i++){
		temp[i].index = i;
		temp[i].suffix =  new char[n];
		if(i == 0) strcpy(temp[i].suffix, text);
		else {
			//Mỗi lần quay 1 so với xâu quay lần trước.
			rotate(text);
			strcpy(temp[i].suffix, text);
		}
	}

	//Sắp xếp mảng temp theo thứ tự AlphaBeta của phần tử suffix : không hiểu tại sao nó sort() sai 1 cái :))
	sort(temp, temp + n, cmpRotation);

	//Tính suffix_arr_index dựa trên danh sách đã sắp xếp.
	for(int j = 0; j < n; j++){
		suffix_arr_index[j] = temp[j].index;
		if(temp[j].index == 0) k = j; //Hàng chứa xâu gốc theo index 0.
		delete [](temp[j].suffix);
	}

	rotate(text); //Quay về xâu cũ


	return suffix_arr_index;
}

char* getLastColumn(char* text, int* suffix_arr_index, int n){
	char* bwt = new char[n];
	int index;

	for(int i = 0; i < n; i++){
		index = suffix_arr_index[i];
		if(index == 0) bwt[i] = text[n-1];
		else bwt[i] = text[index - 1];
	}
	return bwt;
}

//Inverse ngược từ n -> 1.
char* inverseBWT(char* bwt, int n, int k){
	//Mảng lưu trữ xâu sau khi khôi phục.
	char* Q = new char[n];

	//Mảng lưu trữ vị trí đầu tiên của các ký tự theo thứ tự trong F.
	map<char, int> dict;
	int dem = 0;
	//Mảng theo thứ tự từ điển.
	char F[n];
	strcpy(F, bwt);
	sort(F, F + n);
	//Số lần xuất hiện ký tự bwt[i] trước bwt[i].
	int C[n];
	dict[bwt[0]] = 0;

	for(int i = 1; i < n; i++){
		if(F[i] != F[i-1]){
			dict[F[i]] = i;
		}
		
	}

	string s = "";

	for(int i = 0; i < n; i++){
		if(s.length() == 0) C[i] = 0;
		else {
			C[i] = count(s.begin(), s.end(), bwt[i]);
		} 
		s += bwt[i];
	}

	for(int j = n - 1; j >= 0; j--){
		Q[j] = bwt[k];
		k = C[k] + dict[bwt[k]];
	}
	return Q;
}

int main(){
	char arr[] = "SIX.MIXED.PIXIES.SIFT.SIXTY.PIXIE.DUST.BOXES";
	int n = strlen(arr);
	int k;
	int* suffix_arr_index = computeSuffixArrayIndex(arr, n, k);
	cout << "K :" << k << endl;
	char* bwt = getLastColumn(arr, suffix_arr_index, n);
	cout << "BWT :" << bwt << endl; 
	char* original = inverseBWT(bwt, n, k);
	cout << "original :" << original<< endl;
	delete []original;
	return 0;
}