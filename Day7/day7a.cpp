#include<iostream>
#include<vector>
#include<cstdio>
#include<fstream>
#include<sstream>
#include<string>
#include<algorithm>
#include<climits>
#include<ctime>

using namespace std;

vector<int> ReadInput(string inputFile) {
	vector<int> crabs;
	ifstream file(inputFile);
	istringstream iss;
	for(string line; getline(file, line, ',');) {
		int tmp;
		iss.str(line);
		iss >> tmp;
		crabs.push_back(tmp);
		iss.clear();
	}
	return crabs;
}

vector<int> TestInput(int size) {
	vector<int> crabs;
	srand(time(NULL));
	for(int i=0;i<size;i++){
		crabs.push_back(1+rand()/((RAND_MAX+1u)/100));
	}
	return crabs;
}

int FuelCost(int position, vector<int> crabs) {
	int sum=0;
	for(int i=0;i<crabs.size();i++){
		sum+=abs(crabs[i]-position);
	}
	return sum;
}

pair<int,int> MinFuelCostBF(vector<int> crabs) {
	int min = *min_element(crabs.begin(),crabs.end());
	int max = *max_element(crabs.begin(),crabs.end());
	//sort(crabs.begin(),crabs.end());
	//int min = crabs[0];
	//int max = crabs[crabs.size()-1];
	int bestFuelCost = INT_MAX;
	int bestPos = -1;
	//printf("median: %d\n",crabs.size()%2 == 0 ? crabs[((crabs.size()/2)-1] : crabs[crabs.size()/2]));
	for(int i=min;i<max;i++){
		int cost = FuelCost(i,crabs);
		if(cost < bestFuelCost){
			bestFuelCost = cost;
			bestPos = i;
		}
	}
	return pair<int,int>(bestFuelCost,bestPos);
}

int main() {
	vector<int> crabs = ReadInput("input.txt");
	//vector<int> crabs = TestInput(20);
	for(int i=0;i<crabs.size();i++){
		printf("%d ",crabs[i]);
	}
	printf("\n");
	pair<int,int> result = MinFuelCostBF(crabs);
	printf("Fuel Cost:%d\nPosition:%d\n",result.first, result.second);
	return 0;
}
