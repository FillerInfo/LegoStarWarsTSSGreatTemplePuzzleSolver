typedef int Board[5][5];
void printBoard(Board* board);
int hasRandSol(Board* board);
void resetSteps();
int countOnes(Board* board);
int changeBoard(Board* board, int row, int col);
void printSteps();