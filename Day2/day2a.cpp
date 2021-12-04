#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<cstdio>

using namespace std;

vector<pair<string, int> > ReadInput(string filename){
	ifstream inputFile;
	inputFile.open(filename);
	
	vector<pair<string,int> > input;
	pair<string,int> tmp;
	istringstream ss;
	string direction;
	int offset;
	for(string line; getline(inputFile, line);){
		ss.str(line);
		ss >> direction >> offset;
		ss.clear();
		input.push_back(pair(direction, offset));
	}
	return input;
}

int main(int argc, char** argv) {
	vector<pair<string, int> > input = ReadInput("input.txt");
	int x=0;
	int y=0;
	for(int i=0; i < input.size(); i++) {
		if(input[i].first == "forward") {
			x+=input[i].second;
		}
		else if(input[i].first == "backward") {
			x-=input[i].second;
		}
		else if(input[i].first == "up") {
			y-=input[i].second;
		}
		else if(input[i].first == "down") {
			y+=input[i].second;
		}
	}
	printf("x: %d, y: %d, x*y: %d", x, y, x*y);
	return 0;
}
