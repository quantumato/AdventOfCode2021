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
	for(int i=1; i < input.size(); i++) {
		if(input[i] > input[i-1]) {
			counter++;
		}
	}
	cout << counter;
	return 0;
}
