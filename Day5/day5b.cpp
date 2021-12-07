#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<cstdio>
#include<cstring>

#define side_length 1000	//assume max area size of 1000x1000

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

//I don't think there will be more than 32676 intersections
vector<vector<short> > DrawGrid(vector<line*> lines) {
	vector<vector<short> > grid(side_length, vector<short>(side_length, 0));

	for(int i=0;i<lines.size();i++) {
		//vertical line ie. x1 == x2
		int x1 = lines[i]->A.first;
		int x2 = lines[i]->B.first;
		int y1 = lines[i]->A.second;
		int y2 = lines[i]->B.second;
		
		//diagonals
		if(abs(y2-y1) == abs(x2-x1)) {
			//always go left to right
			if(x1 > x2) {
				int tmp = x1;
				x1 = x2;
				x2 = tmp;
				tmp = y1;
				y1 = y2;
				y2 = tmp;
			}
			//SE diagonal
			if((x1 - x2) == (y1 - y2)) {
				for(int offset=0;(x1+offset)<=x2;offset++){
					grid[y1+offset][x1+offset]++;
				}
			}
			//SW diagonal
			else {
				for(int offset=0;(x1+offset)<=x2;offset++){
					grid[y1-offset][x1+offset]++;
				}
			}
		}

		//vertical line
		if(x1 == x2) {
			if(y1 > y2) {
				int tmp = y1;
				y1 = y2;
				y2 = tmp;
			}
			for(int y=y1;y<=y2;y++){
				grid[y][x1]++;
			}
			continue;
		}

		//horizontal line
		if(y1 == y2) {
			if(x1 > x2) {
				int tmp = x1;
				x1 = x2;
				x2 = tmp;
			}
			for(int x=x1;x<=x2;x++) {
				grid[y1][x]++;
			}
		}
	}
	return grid;
}

int CountIntersections(vector<vector<short> > grid) {
	int counter=0;
	for(int i=0;i<grid.size();i++){
		for(int j=0;j<grid.size();j++){
			if(grid[i][j]>1){
				counter++;
			}
		}
	}
	return counter;
}

void PrintGrid(vector<vector<short> > grid) {
	for(int i=0;i<grid.size();i++){
		for(int j=0;j<grid[i].size();j++){
			printf("%d ",grid[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int main() {
	vector<line*> lines = ReadInput("input.txt");

	for(int i=0;i<lines.size();i++){
		printf("%d,%d -> %d,%d\n", lines[i]->A.first,lines[i]->A.second,lines[i]->B.first,lines[i]->B.second);
	}
	vector<vector<short> > grid = DrawGrid(lines);
	PrintGrid(grid);
	int intersections = CountIntersections(grid);
	printf("Intersections: %d\n", intersections);
	return 0;
}
