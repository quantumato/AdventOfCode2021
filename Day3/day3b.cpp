#include<iostream>
#include<vector>
#include<fstream>
#include<cstdio>
#define NUM_BITS 12
using namespace std;

vector<string> ReadInputString(string inputFile) {
	ifstream inFile(inputFile);
	vector<string> input;
	for(string tmp;inFile >> tmp;) {
		input.push_back(tmp);
	}
	return input;
}

string CountO2Bits(vector<string> input, bool isO2) {
	int totalInputs=0;
	int bitRepresentation=0;
	vector<string> myInput = input;

	//check the (MSB->) nth bit
	for(int n=0;n < NUM_BITS;n++) {
		int oneCount=0;
		char mostCommon;
		//count ones
		for(int i=0; i < myInput.size(); i++) {
			if(myInput[i][n] == '1') {oneCount++;}
		}
		//determine most common character
		if(isO2) {
			if((myInput.size()-oneCount) <= (myInput.size()/2)) {
				mostCommon = '1';
			}
			else {
				mostCommon = '0';
			}
		}
		else {
			if((myInput.size()-oneCount) > (myInput.size()/2)) {
				mostCommon = '1';
			}
			else {
				mostCommon = '0';
			}
		}
		//add to new vector
		vector<string> tmp;
		for(int i = 0; i < myInput.size();i++) {
			if(myInput[i][n] == mostCommon) {
				tmp.push_back(myInput[i]);
			}
		}
		if(tmp.size() == 1) {
			return tmp[0];
		}
		myInput = tmp;
	}
	return "NULL";
}

int main(int argc, char** argv) {
	//vector<string> input = ReadInput("input.txt");
	/*for(int i = 0; i < input.size(); i++) {
	  printf("%d\n", input[i]);
	  }*/
	vector<string> input = ReadInputString("input.txt");
	string O2Rating = CountO2Bits(input, true);
	string CO2Rating = CountO2Bits(input, false);
	printf("O2 Rating: %s\n", O2Rating.c_str()); 
	printf("CO2 Rating: %s\n", CO2Rating.c_str()); 
	int O2 = strtol(O2Rating.c_str(), NULL, 2);
	int CO2 = strtol(CO2Rating.c_str(), NULL, 2);
	printf("result: %d\n", O2*CO2);
	return 0;
}
