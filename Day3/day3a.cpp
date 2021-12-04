#include<iostream>
#include<vector>
#include<fstream>
#include<cstdio>
#define NUM_BITS 12
using namespace std;

vector<int> ReadInputInt(string inputFile) {
	ifstream inFile(inputFile);
	vector<int> input;
	for(string tmp;inFile >> tmp;) {
		int converted = strtol(tmp.c_str(), NULL, 2);
		input.push_back(converted);
	}
	return input;
}

int CountInputBits(string inputFile) {
	ifstream inFile(inputFile);
	vector<int> oneCounts(NUM_BITS, 0);
	int totalInputs=0;
	int bitRepresentation=0;

	//count the ones in each place
	for(string bitString;inFile >> bitString;totalInputs++) {
		for(int i=0; i<bitString.size(); i++) {
			if(bitString[i] == '1'){
				oneCounts[i]++;
			}
		}
	}
	printf("Counts:\n");
	for(int i=0; i < oneCounts.size();i++) {
		printf("%d ",oneCounts[i]);
	}
	printf("\n");

	for(int i=0;i < oneCounts.size();i++) {
		if((totalInputs - oneCounts[i]) < (totalInputs/2)){	//more than half the inputs are ones
			bitRepresentation |= 1u << (oneCounts.size()-1-i);
		}
	}
	return bitRepresentation;
}

int main(int argc, char** argv) {
	//vector<string> input = ReadInput("input.txt");
	/*for(int i = 0; i < input.size(); i++) {
		printf("%d\n", input[i]);
	}*/
	int result = CountInputBits("input.txt");
	printf("gamma: %u 0x%x\n", result, result);
	unsigned int inverse = result^((1u<<NUM_BITS)-1);
	printf("epsilon: %u 0x%x\n", inverse,inverse);
	printf("total power consumption: %u\n", result*inverse);
	return 0;
}
