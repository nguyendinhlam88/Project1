#include <iostream>
#include <algorithm>
#include <string.h>
#include <map>
#include <fstream>

using namespace std;

struct Rotation{
	int index;
	char* suffix;
};

struct Node{ //For huffman.
	char ch; //Nút lá mới có.
	int fre; //Trọng số của nút(tần số).
	Node* left;
	Node* right;
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

//BWT
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

//Inverse BWT
char* inverseBWT(char* bwt, int n, int k){
	//Mảng lưu trữ xâu sau khi khôi phục.
	char* Q = new char[n];

	//Mảng theo thứ tự từ điển.
	char F[n];
	strcpy(F, bwt);
	sort(F, F + n);

	//map lưu trữ vị trí đầu tiên của các ký tự theo thứ tự trong F.
	map<char, int> dict;
	int dem = 0;
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

unsigned short int* MTF(char* bwt, int n, string characters, int m){
	int* mtf = int[];
	for(int i = 0; i < n; i++){
		int pos = characters.find(bwt[i]);
		mtf[i] = pos;
		characters = characters[pos] + characters.substr(0, pos) + characters.substr(pos+1, m);
	}
	return mtf;
}

char* huffman(int* mtf, int* frequency){
}

int main(){
	string filename;
	string characters; //Các chữ cái được sử dụng trong text

	cout << "Enter your filename : ";
	cin >> filename;

	fstream myfile(filename);

	if(myfile.is_open()){
		myfile.seekg(0, ios::end);
		int n = myfile.tellg();
		myfile.seekg(0, ios::beg);
		char text[n];
		int index = 0;
		char ch;

		while(myfile.get(ch)){
			text[index] = ch;
			if(count(characters.begin(), characters.end(), ch) == 0) characters += ch;
			index ++;
		}
		sort(characters.begin(), characters.end()); //Sắp xếp các ký tự trong biến "characters" theo alphabet.

		n = strlen(text);
		int k;
		int* suffix_arr_index = computeSuffixArrayIndex(text, n, k);
		char* bwt = getLastColumn(text, suffix_arr_index, n);
		cout << "BWT :" << bwt << endl;

		char* original = inverseBWT(bwt, n, k);
		cout << "original :" << original<< endl;
		delete []original;

		int* mtf = MTF(bwt, n, characters, characters.length());

		} else cout << "Fail to read " + filename << endl;
	return 0;
}