// Name of program mainreturn.cpp
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>

#include "funcDefs.h"

using namespace std;  

int steps[100];

int main(int argc, char** argv){
	srand(time(NULL));

	Board board;
	resetSteps();

	string line;
	ifstream myfile(argv[1]);
	if(myfile.is_open()){
		int row = 0;
		while(getline(myfile,line)){
			for(int col = 0; col < 5; col++){
				board[row][col] = line[col] == '0' ? 0 : 1;
			}
			row++;
		}
		myfile.close();
	}
	else{
		cout << "Unable to open file";
	}

	cout << "Starting board:\n";
	printBoard(&board);

	int result = hasRandSol(&board);
	while(result != -1){
		printBoard(&board);
		printSteps();
		cout << "No solution at " << result << " steps.\n";
		resetSteps();
		result = hasRandSol(&board);
	}

	cout << "Solution found!!\n";
	printBoard(&board);
	printSteps();

	// cout << "\n\n";
	// changeBoard(&board, 5, 2);
	// printBoard(&board);


	return 0;
}

int hasRandSol(Board* board){
	int onesCount = countOnes(board);

	for(int i = 0; i < 100; i++){
		//pick random square
		int row = rand() % 6;
		int col = rand() % 6;

		//change board based on square
		onesCount += changeBoard(board, row, col);

		steps[i] = row * 10 + col;

		// board is all ones
		if(onesCount == 25){
			return -1;
		}
	}

	return onesCount;
}

void printBoard(Board* board){
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 5; j++){
			cout << (*board)[i][j] << " ";
		}
		cout << "\n";
	}
}

void printSteps(){
	for(int i = 0; i < 100; i++){
		cout << steps[i] << " ";
	}
	cout << "\n";
}

void resetSteps(){
	for(int i = 0; i < 100; i++){
		steps[i] = -1;
	}
}

int countOnes(Board* board){
	int count = 0;
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 5; j++){
			if((*board)[i][j] == 1){
				count++;
			}
		}
	}
	return count;
}

int changeBoard(Board* board, int row, int col){
	int diff = 0;

	for(int x = row - 1; x <= row + 1; x++){
		for(int y = col - 1; y <= col + 1; y++){
			if(x == row && y == col){
				//do not flip
			}
			else if(x >= 0 && y >= 0 && x <= 4 && y <= 4){
				//flip
				int old = (*board)[x][y];
				int val;
				if(old == 0){
					val = 1;
				}
				else{
					val = 0;
				}
				(*board)[x][y] = val;

				//update diff
				diff += val - old;
			}
		}
	}

	return diff;
}