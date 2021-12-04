#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

vector<int> ReadInput(string filename) {
	ifstream infile;
	infile.open(filename);
	vector<int> buf;

	int tmp;
	while(infile >> tmp) {
		buf.push_back(tmp);
	}
	return buf;
}
int main(int argc, char** argv) {
	int counter = 0;
	vector<int> input = ReadInput("input");
	for(int i=0; i < input.size()-3; i++) {
		//calc current 3-day sum
		int csum = input[i] + input[i+1] + input[i+2];
		int nsum = input[i+1] + input[i+2] + input[i+3];
		if(nsum > csum) {
			counter++;
		}
	}
	cout << counter;
	return 0;
}
