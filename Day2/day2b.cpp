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
	int aim=0;
	int offset =0;
	for(int i=0; i < input.size(); i++) {
		if(input[i].first == "forward") {
			offset = input[i].second;
			x+=offset;
			y+=offset*aim;
		}
		else if(input[i].first == "backward") {
			x-=input[i].second;	//aim doesn't affect going backwards?
		}
		else if(input[i].first == "up") {
			aim-=input[i].second;
		}
		else if(input[i].first == "down") {
			aim+=input[i].second;
		}
	}
	printf("x: %d, y: %d, x*y: %d", x, y, x*y);
	return 0;
}
