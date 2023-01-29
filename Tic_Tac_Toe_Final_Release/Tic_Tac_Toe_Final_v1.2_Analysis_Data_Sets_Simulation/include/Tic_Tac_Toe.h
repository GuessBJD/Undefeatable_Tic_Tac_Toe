#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#define SIDE 3
#define AIMOVE 'O'
#define PLAYERMOVE 'X'
#define AITURNS 1
#define PLAYERTURNS 0

class Tictactoe
{

public:
    void interface();
    Tictactoe() //constructor
    {
        initialiseBoard(); //initialize an empty board
        for(int i = 0; i < SIDE; i++)
            for(int j = 0; j < SIDE; j++)
                scoreBoard[i][j] = 99;
    }

private:
    void startTicTacToe(bool Turns);
    void displayBoard(bool trigger);
    void displayInstructions();
    void initialiseBoard();
    bool rowWin();
    bool columnWin();
    bool diagonalWin();
    void who_wins(int whoseTurn);
    bool gameOver();
    int minimax(int depth, bool isAI, bool print);
    void showScoreAnalysis();
    int getRandomSquare(int bestScore);
    int bestMove(int moveIndex);

    char board[SIDE][SIDE];
    int scoreBoard[SIDE][SIDE];
};

#endif // TIC_TAC_TOE_H
