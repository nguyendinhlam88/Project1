#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <cmath>
#include "hfm.h"

using namespace std;

struct Node {
	wchar_t ch;
	bool isLeave;
	int weight;
	Node* left;
	Node* right;
};

// ouput : tần suất xuất hiện của các chữ cái.
void getFrequency(wchar_t* arr, map<wchar_t, int> &frequency, int n) {
	for(int i = 0; i < n; i++) {
		frequency[arr[i]] += 1;
	} 
}

void merge(Node* nArray, int beg, int mid, int end) {
	int n1, n2, idx = 0, l = 0, r = 0, k = beg;

	n1 = mid - beg + 1;
	n2 = end - mid;
	Node lArray[n1], rArray[n2];

	for(int i = beg; i <= mid; i++) {
		lArray[idx].ch = nArray[i].ch;
		lArray[idx].isLeave = nArray[i].isLeave;
		lArray[idx].weight = nArray[i].weight;
		lArray[idx].left = nArray[i].left;
		lArray[idx].right = nArray[i].right;
		idx++;
	}

	idx = 0;
	for(int i = mid+1; i <= end; i++) {
		rArray[idx].ch = nArray[i].ch;
		rArray[idx].isLeave = nArray[i].isLeave;
		rArray[idx].weight = nArray[i].weight;
		rArray[idx].left = nArray[i].left;
		rArray[idx].right = nArray[i].right;
		idx++;
	}

	while(l < n1 && r < n2) {
		if(lArray[l].weight < rArray[r].weight) {
			nArray[k].ch = lArray[l].ch;
			nArray[k].isLeave = lArray[l].isLeave;
			nArray[k].weight = lArray[l].weight;
			nArray[k].left = lArray[l].left;
			nArray[k].right = lArray[l].right;
			l++;
			k++;
		} else if(lArray[l].weight > rArray[r].weight) {
			nArray[k].ch = rArray[r].ch;
			nArray[k].isLeave = rArray[r].isLeave;
			nArray[k].weight = rArray[r].weight;
			nArray[k].left = rArray[r].left;
			nArray[k].right = rArray[r].right;
			r++;
			k++;
		} else {
			nArray[k].ch = lArray[l].ch;
			nArray[k].isLeave = lArray[l].isLeave;
			nArray[k].weight = lArray[l].weight;
			nArray[k].left = lArray[l].left;
			nArray[k].right = lArray[l].right;
			l++;
			k++;
			nArray[k].ch = rArray[r].ch;
			nArray[k].isLeave = rArray[r].isLeave;
			nArray[k].weight = rArray[r].weight;
			nArray[k].left = rArray[r].left;
			nArray[k].right = rArray[r].right;
			r++;
			k++;
		}
	}

	while(l < n1) {
		nArray[k].ch = lArray[l].ch;
		nArray[k].isLeave = lArray[l].isLeave;
		nArray[k].weight = lArray[l].weight;
		nArray[k].left = lArray[l].left;
		nArray[k].right = lArray[l].right;
		l++;
		k++;
	}

	while(r < n2) {
		nArray[k].ch = rArray[r].ch;
		nArray[k].isLeave = rArray[r].isLeave;
		nArray[k].weight = rArray[r].weight;
		nArray[k].left = rArray[r].left;
		nArray[k].right = rArray[r].right;
		r++;
		k++;
	}
}

void mergeSort(Node* nArray, int beg, int end) {
	int mid;

	if(beg == end) return;
	else if(beg < end){
		mid = (beg + end)/2;
		mergeSort(nArray, beg, mid);
		mergeSort(nArray, mid+1, end);
		merge(nArray, beg, mid, end);
	}
}

// nArray : một mảng các nút của các ký tự và tuần suất của nó.
Node* buildNodeArray(map<wchar_t, int> frequency) {
	int size, idx = 0;
	Node* nArray;

	size = frequency.size();
	nArray = new Node[size];
	for(auto item : frequency) {
			nArray[idx].ch = item.first;
			nArray[idx].weight = item.second;
			nArray[idx].isLeave = true;
			idx++;
	}
	mergeSort(nArray, 0, size - 1);

	return nArray;
}

// Sau khi thực hiện xong thì root node ở node_array[size-1].
void buildHuffmanTree(Node* nArray, int n) {
	Node* newNode;
	Node temp;

	for(int i = 1; i < n; i++) { 
		newNode = new Node;
		newNode -> ch = L' ';
		newNode -> weight = nArray[i-1].weight + nArray[i].weight;
		newNode -> isLeave = false;
		temp = nArray[i];
		nArray[i] = *(newNode);
		*(newNode) = temp;
		nArray[i].left = nArray + i - 1;
		nArray[i].right = newNode;
		if(i == (n - 1)) {
			break;
		}
		mergeSort(nArray, i, n - 1);
	}
}

void getHuffmanEncoder(Node root, map<wchar_t, wstring> &dict, wstring &xau, wstring &header) {

	if(root.isLeave == true) {
		dict[root.ch] = xau;
		header += L'1';
		header += root.ch;
		xau = xau.substr(0, xau.length()-1);
		return;
	} 
	if(root.right != NULL) {

		header += L'0';
		wstring xau1 = xau + L'0';
		getHuffmanEncoder(*root.left, dict, xau1, header);

		wstring xau2 = xau + L'1';
		getHuffmanEncoder(*root.right, dict, xau2, header);
		xau = xau.substr(0, xau.length()-1);

		return;
	}
}

// Chuyển các dãy 32 bit nhị phân tới wchar_t.
wstring toChar(wstring huffman, wstring &nChar32, wchar_t &nAddBit) {
	wstring toChar = L"", bit0 = L"0000000000000000000000000000000";
	int size, index, sum;
	bool chkFirst;

	nChar32 = L"";
	chkFirst = false;
	size = huffman.length();
	index = 0;
	
	while (index < size) {
		sum = 0;
		if(chkFirst == true && (size - index) > 1 && (size - index) < 15) {
			nAddBit = 15 - (size - index);
			huffman += bit0.substr(nAddBit);
		}
		if( chkFirst == false && (size - index) > 1 && (size - index) < 32) {
			nAddBit = 32 - (size - index);
			huffman += bit0.substr(nAddBit);
		}
		if(chkFirst == false) {
			for(int i = 0; i < 32; i++){
				if(huffman[(index/32)*32 + i] == L'1') sum += pow(2, 31 - i);
			}
		} else {
			for(int i = 0; i < 15; i++){
				if(huffman[(index/15)*15 + i] == L'1') sum += pow(2, 14 - i);
			}
		}
		if(chkFirst == false && ((sum > 55203 && sum < 57344) || (sum > 262144 && sum < 917504) || sum > 983039)) {
			chkFirst = true;
			nChar32 += wchar_t(index/32 + 48);
			continue;
		}
		if(!chkFirst) index += 32;
		else index += 15;
		if(sum == 8) sum = wchar_t(983039);
		toChar += wchar_t(sum);
	}

	return toChar;
}

wstring hfmEncoder(wchar_t* arr, int n) {
	map<wchar_t, wstring> dict;
	wstring xau, hfmEncoder = L"", header, nChar32, toChar1; // xâu : ánh xạ từ ký tự sang xâu 01.
	map<wchar_t, int> frequency;
	Node* nArray;
	Node root;
	wchar_t nAddBit;

	getFrequency(arr, frequency, n);
	nArray = buildNodeArray(frequency);
	buildHuffmanTree(nArray, frequency.size());
	root = nArray[frequency.size() - 1];
	getHuffmanEncoder(root, dict, xau, header);

	delete []nArray;
	for(int i = 0; i < n; i++) {
		hfmEncoder += dict[arr[i]];
	}
	toChar1 = toChar(hfmEncoder, nChar32, nAddBit);
	hfmEncoder = wchar_t(header.length()) + nChar32 + nAddBit + header + toChar1;

	delete []arr;
	return hfmEncoder;
}