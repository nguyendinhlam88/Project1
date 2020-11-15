#include <iostream>
#include <algorithm>
#include <string.h>
#include <map>
#include <cmath>
#include "hfm.h"

using namespace std;

struct Node {
	char ch;
	bool is_leave;
	float weight;
	Node* left;
	Node* right;
};

bool cmpN(Node node1, Node node2) {
	return node1.weight <= node2.weight;
}

// output : bảng chữ cái của arr(không phải ascii), origin(arr).
string build_alphabet(string arr, string &origin, int n) {
	string alphabet;

	for(int i = 0; i < n; i++) {
		origin += arr[i];
		int fre = count(alphabet.begin(), alphabet.end(), arr[i]);
		if(fre == 0) {
			alphabet += arr[i];
		}
	}

	return alphabet;
}

// ouput : tần suất xuất hiện của các chữ cái.
float* get_frequency(string origin, string alphabet, int n) {
	int size = alphabet.length();
	float* frequency = new float[size];

	for(int i = 0; i < size; i++) {
		int dem  = count(origin.begin(), origin.end(), origin[i]);
		frequency[i] = (1.0*dem)/n;
	} 

	return frequency;
}

// Xây dựng các nút lá và xắp sếp theo thứ tự tăng dần.
Node* build_node_array(string alphabet, float* frequency) {
	int size = alphabet.length();
	Node* node_array = new Node[size];

	for(int i = 0; i < size; i++) {
		node_array[i].ch = alphabet[i];
		node_array[i].weight = frequency[i];
		node_array[i].is_leave = true;
	}

	sort(node_array, node_array + size, cmpN);
	return node_array;
}

// Sau khi thực hiện xong thì root node ở node_array[size-1].
void build_huffman_tree(Node* node_array, int size) {

	for(int i = 1; i < size; i++) { // Tạo ra n - 1 nút để về 1 nút gốc. 
		Node* new_node = new Node;
		new_node -> ch = ' ';
		new_node -> weight = node_array[i-1].weight + node_array[i].weight;
		new_node -> is_leave = false;
		Node temp = node_array[i];
		node_array[i] = *(new_node);
		*(new_node) = temp;
		node_array[i].left = node_array + i - 1;
		node_array[i].right = new_node;
		if( i == size - 1) {
			break;
		}
		sort(node_array + i, node_array + size, cmpN);
	}
}

void get_huffman(Node root, map<char, string> &dict, string &xau, string &header) {

	if(root.is_leave == true) {
		dict[root.ch] = xau;
		header += '1';
		header += root.ch;
		xau = xau.substr(0, xau.length()-1);

		return;
	} 
	if(root.right != NULL) {

		header += '0';
		string xau1 = xau + '0';
		get_huffman(*root.left, dict, xau1, header);

		string xau2 = xau + '1';
		get_huffman(*root.right, dict, xau2, header);
		xau = xau.substr(0, xau.length()-1);

		return;
	}
}

// Chuyển các dãy 8 bit nhị phân tới char.
string convert_to_char(string huffman) {
	string temp = "";
	string bit_0 = "000000";
	int size = huffman.length();
	int index = 0;

	if(size % 7 != 0) huffman += bit_0.substr(0, (7 - (size % 7)));
	int char_num = huffman.length()/7;

	
	while (index < char_num) {
		int sum = 0;
		for(int i = 0; i < 7; i++){
			if(huffman[index*7 + i] == '1') {
				sum += pow(2, 6 - i);
			}
		}
		temp += char(sum);
		index ++;
	}

	return temp;
}

string hfme(string arr, int n) {
	string origin; // Chuyển arr -> string cho dễ sử dụng.
	map<char, string> dict;
	string xau; // xâu : ánh xạ từ ký tự sang xâu 01.
	string huffman;
	string header;

	string alphabet = build_alphabet(arr, origin, n);
	float* frequency = get_frequency(origin, alphabet, n);
	Node* node_array = build_node_array(alphabet, frequency);

	delete []frequency;
	build_huffman_tree(node_array, alphabet.length());
	Node root = node_array[alphabet.length()-1];
	get_huffman(root, dict, xau, header);

	delete []node_array; // Chưa giải phóng hết.
	for(int i = 0; i < n; i++) {
		huffman += dict[arr[i]];
	}
	string bit_num = "7"; // Số bit biểu diễn.
	char bit_add = 48 + (7 - huffman.length() % 7); // Số bit 0 thêm vào.
	huffman = char(header.length()) + bit_num + bit_add + header + convert_to_char(huffman);

	return huffman;
}