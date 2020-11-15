#include <iostream>
#include <iostream>
#include <cmath>
#include <map>
#include <stack>
#include <string>
#include "hfm.h"

using namespace std;

// Chuyển đầu vào sang mã nhị phân.
string convert_to_bin(string hfmc, int bit_num, int bit_add) {
	int size = hfmc.length();
	string hfmcode;
	int index = 0;

	for(int i = 0; i < size; i++) {
		int value = hfmc[i];

		for(int j = 0; j != bit_num; j++) {
			if (index == (size*bit_num - bit_add)) {
				return hfmcode;
			}
			int temp = pow(2, 6-j);
			if(value >= temp) {
				hfmcode += '1';
				index++;
				value -= temp;
			} else {
				hfmcode += '0';
				index++;
			}
		}
	}
	return hfmcode;
}

void build_dict(string header, map<string, char> &dict) {
	stack<string> st;
	int size = header.length();
	string temp = "";
	int dem = 0;

	for(int i = 0; i < size; i++) { // Bắt đầu từ 1 để xét đến stack rỗng chuyển sang nhánh phải của rỗng.
		if(st.empty() && dem < 3) {
			dem++;
			if(dem == 2) {
				temp = "1";
				st.push("1");
			}
		}
		if(header[i] == '0') {
			temp += '0';
			st.push(temp);
		} else {
			dict[temp] = header[i+1];
			i++;
			st.pop();
			if(st.empty()) continue;
			temp = st.top() + '1';
			st.pop();
			st.push(temp);
		}
	}
}

string decode_huffman(string hfmcode, map<string, char> dict) {
	int size = hfmcode.length();
	string decode;
	string temp;

	for(int i = 0; i < size; i++)  {
		temp += hfmcode[i];
		if(dict.count(temp) != 0) {
			decode += dict[temp];
			temp = "";
		}
	}
	return decode;
}

string hfmd(string huffman, int n) {
	int header_size = huffman[0];
	int bit_num = huffman[1] - 48;	// Ascii : 7 bit
	int bit_add = huffman[2] - 48; // Số lượng bit thêm vào cuối.
	map<string, char> dict;	

	string header = huffman.substr(3, header_size);
	string hfmc = huffman.substr(header_size+3);
	string hfmcode = convert_to_bin(hfmc, bit_num, bit_add);
	build_dict(header, dict);
	string decode = decode_huffman(hfmcode, dict);

	return decode;
}

