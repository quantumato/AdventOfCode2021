#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<cstdio>
#include<cstring>

using namespace std;

struct line {
	pair<int,int> A;
	pair<int,int> B;
};

vector<line*> ReadInput(string inputFile) {
	vector<line*> lines;
	ifstream file(inputFile);
	char inBuffer[100];
	for(string in; getline(file, in);){
		strncpy(inBuffer, in.c_str(), 100);
		char *token;
		token = strtok(inBuffer," ->,");
		int A = strtol(token, NULL, 10);
		token = strtok(NULL," ->,");
		int B = strtol(token, NULL, 10);
		token = strtok(NULL," ->,");
		int C = strtol(token, NULL, 10);
		token = strtok(NULL," ->,");
		int D = strtol(token, NULL, 10);

		line* l = new line();
		l->A = pair<int,int>(A,B);
		l->B = pair<int,int>(C,D);
		lines.push_back(l);
	}
	return lines;
}

int main() {
	vector<line*> lines = ReadInput("testinput.txt");

	for(int i=0;i<lines.size();i++){
		printf("%d,%d -> %d,%d\n", lines[i]->A.first,lines[i]->A.second,lines[i]->B.first,lines[i]->B.second);
	}
	return 0;
}
