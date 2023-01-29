#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#define SIDE 3
#define BOT_1_MOVE 'O'
#define BOT_2_MOVE 'X'
#define BOT_1_TURNS 1
#define BOT_2_TURNS 0

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
    int minimax(int depth, bool isAI, bool perspective, bool print);
    void showScoreAnalysis();
    int getRandomSquare(int bestScore);
    int bestMove(int moveIndex, bool perspective);

    char board[SIDE][SIDE];
    int scoreBoard[SIDE][SIDE];
};

#endif // TIC_TAC_TOE_H
