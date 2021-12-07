#include<cstdio>
#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<climits>
using namespace std;
#define BOARD_SIZE 5


/* we just need the sum of each board and the links matrix to calculate the winning score*/
/* jk maybe. It presents a problem when summing up unmarked numbers */

struct input {
	vector<int> drawnNumbers;
	vector<vector<vector<int> > > boards;
	vector<vector<vector<int> > > links;
};

input* ReadInput(string inputFile) {
	input* _input = new input();
	ifstream file(inputFile);
	string line;
	getline(file, line);
	istringstream is;
	is.str(line);
	for(string tok; getline(is, tok, ',');) {
		_input->drawnNumbers.push_back(stoi(tok));
		is.clear();
	}

	//read boards
	bool flag = true;
	vector<vector<int> > board;
	vector<vector<int> > linkBoard;
	for(string row; getline(file, row);) {
		if(row == "") {	//whitespace row
			if(flag) {
				flag = false;
				continue;
			}
			_input->boards.push_back(board);
			_input->links.push_back(linkBoard);
			board.clear();
			linkBoard.clear();
			continue;
		}
		istringstream iss;
		iss.str(row);
		vector<int> boardRow;
		vector<int> linkRow;
		for(int tmp; iss >> tmp;) {
			//find in drawn numbers
			int index=-1;
			for(int i=0;i<_input->drawnNumbers.size();i++) {
				if(_input->drawnNumbers[i] == tmp) {
					index = i;
					break;
				}
			}
			//add index of drawn number to list of links
			linkRow.push_back(index);
			boardRow.push_back(tmp);
		}
		board.push_back(boardRow);
		linkBoard.push_back(linkRow);
	}
	_input->boards.push_back(board);
	_input->links.push_back(linkBoard);
	file.close();
	return _input;
}


int SumBoardScore(input* game, int winningBoard, int winNumIndex) {
	int sum = 0;
	printf("Winning Index: %d\n", winNumIndex);
	printf("\nScore calculation:\n");
	for(int i=0;i<BOARD_SIZE;i++){
		for(int j=0;j<BOARD_SIZE;j++){
			if(game->links[winningBoard][i][j] > winNumIndex || game->links[winningBoard][i][j] == -1) {
				printf("%d ",game->boards[winningBoard][i][j]);
				sum += game->boards[winningBoard][i][j];
			}
		}
	}
	printf("\n");
	return sum;
}


//returns index of winning number for given board
int WinningNum(input* game, int boardIndex) {
	vector<vector<int> > board = game->boards[boardIndex];
	vector<vector<int> > links = game->links[boardIndex];
	//check rows
	vector<int> rows;
	for(int i=0;i<BOARD_SIZE;i++) {
		int winner = -1;
		for(int j=0;j<BOARD_SIZE;j++) {
			//highest index in links is the winning number for this row
			if(links[i][j] > winner) {
				winner = links[i][j];
			}
		}
		if(winner > 0){
			rows.push_back(winner);
		}
	}
	//check columns
	vector<int> columns;
	for(int j=0;j<BOARD_SIZE;j++) {
		int winner = -1;
		for(int i=0;i<BOARD_SIZE;i++) {
			//highest index in links is the winning number for this row
			if(links[i][j] > winner) {
				winner = links[i][j];
			}
		}
		if(winner > 0){
			columns.push_back(winner);
		}
	}
	/*	Just Kidding diagonals don't count. But if they did...

	//diagonals
	int SEDiagWinner = -1;
	int SWDiagWinner = -1;
	for(int i=0;i<BOARD_SIZE;i++){
		if(links[i][i] > SEDiagWinner) {
			SEDiagWinner = links[i][i];
		}
		if(links[i][BOARD_SIZE-1-i] > SWDiagWinner) {
			SWDiagWinner = links[i][BOARD_SIZE-1-i];
		}
	}*/

	//find index of winning number (if any) for this board
	int BoardWinner = INT_MAX;
	for(int i=0;i<rows.size();i++) {
		if(rows[i] < BoardWinner) {
			BoardWinner = rows[i];
		}
	}
	for(int i=0;i<columns.size();i++) {
		if(columns[i] < BoardWinner) {
			BoardWinner = columns[i];
		}
	}
	/*if((SEDiagWinner > 0) && (SEDiagWinner < BoardWinner)) {
		BoardWinner = SEDiagWinner;
	}
	if((SWDiagWinner > 0) && (SWDiagWinner < BoardWinner)) {
		BoardWinner = SWDiagWinner;
	}*/
	return BoardWinner;
}
int PlayGame(input* game) {
	vector<int> winningNumPerBoard;
	for(int i=0;i<game->boards.size();i++){
		winningNumPerBoard.push_back(WinningNum(game,i));
	}

	printf("Winning Index Per Board:\n");
	for(int i=0;i<winningNumPerBoard.size();i++){
		printf("%d ",winningNumPerBoard[i]);
	}
	printf("\n");

	int winNumIndex = INT_MAX;
	int BoardIndex;
	for(int i=0;i<winningNumPerBoard.size();i++){
		if(winningNumPerBoard[i] < winNumIndex){
			BoardIndex = i;
			winNumIndex = winningNumPerBoard[i];
		}
	}
	int winningNumber = game->drawnNumbers[winNumIndex];
	int boardScore = SumBoardScore(game, BoardIndex , winningNumPerBoard[BoardIndex]);
	printf("winning board: %d\n", BoardIndex);
	printf("winning draw index: %d\n", winNumIndex);
	printf("Score: %d\n", boardScore);
	return winningNumber * boardScore;
}

int main() {
	input* game = ReadInput("testinput.txt");
	printf("boards: %d\n", game->boards.size());
	for(int i = 0; i < game->boards.size();i++) {
		printf("\n\n");
		for(int j=0; j < game->boards[i].size();j++) {
			for(int k=0; k < game->boards[i][j].size();k++) {
				printf("%d ", game->boards[i][j][k]);
			}
			printf("\n");
		}
	}
	printf("\n\nlinks: %d\n", game->links.size());
	for(int i = 0; i < game->links.size();i++) {
		printf("\n\n");
		for(int j=0; j < game->links[i].size();j++) {
			for(int k=0; k < game->links[i][j].size();k++) {
				printf("%d ", game->links[i][j][k]);
			}
			printf("\n");
		}
	}
	printf("Winning Score: %d\n", PlayGame(game));
	return 0;
}
