#include <iostream>
#include <fstream>
#include <algorithm>
#include <string.h>

using namespace std;

typedef struct{
	int index;
	char* suffix;
}Rotation;

bool compareRotation(Rotation tmp1,Rotation tmp2){
	//strcmp không đáp ứng được sách bwt.
	int i = 0;
	while(i < 50){
		if(tmp1.suffix[i] > tmp2.suffix[i]){
			return false;
		} else if(tmp1.suffix[i] < tmp2.suffix[i]){
			return true;
		}
		i++;
		
	}
	return true;
}

int* buildSuffixArray(char* text, int len){
	
	Rotation tmp[len];
	//Intantiate a dynamic suffix_arr to return.
	int* suffix_arr = new int[len] ;

	for(int i = 0; i < len; i++){
		tmp[i].index = i;
		tmp[i].suffix = text + i;
	}

	//Sort tmp by tmp[i].suffix
	sort(tmp, tmp + len, compareRotation);

	//Assign tmp[i].index for suffix_arr[i] to know the original rotation order  
	for(int j = 0; j < len; j++){
		suffix_arr[j] = tmp[j].index;
	}

	return suffix_arr;
}

char* BWT(char* text, int* suffix_arr, int len){
	char* bwt = new char[len];

	//Because rotation by 1 character.
	int i = 0;
	for(int i = 0; i < len; i++){
		int j = suffix_arr[i] - 1;
		if(j < 0) j += len;
		bwt[i] = text[j];
	}

	return bwt;
}



int main(){

	//Chuyển đổi xuôi.
	// Input : "SIX.MIXED.PIXIES.SIFT.SIXTY.PIXIE.DUST.BOXES"
   	ifstream myfile;
    myfile.open("test1.txt");

    if(myfile.is_open()){
    	int begin = myfile.tellg();
    	myfile.seekg(0, ios::end);
    	int end = myfile.tellg();
    	int size = end - begin;
    	myfile.seekg(0);
    	char text[size];
    	int i = 0;

    	while(!myfile.eof()){
    		string line;
    		getline(myfile, line);
    		int i = 0;
    		while(i < line.length()){
    			text[i] = line[i];
    			i++;
    		}
    	}

    	int len = sizeof(text)/sizeof(char);
    	int* suffix_arr = buildSuffixArray(text, len);
    	char* output = BWT(text, suffix_arr, len);

    	cout << output;

    } 
    else cout << "Fail to read file" << endl;

    myfile.close();
    //Chuyển đổi ngược.

    return 0;
}