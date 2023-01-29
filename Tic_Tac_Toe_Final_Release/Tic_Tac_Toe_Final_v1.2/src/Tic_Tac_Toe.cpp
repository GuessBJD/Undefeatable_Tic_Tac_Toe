#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <time.h>
#include "Tic_Tac_Toe.h"

using namespace std;

void Tictactoe::interface(){
    cout<<"\n-------------------------------------------------------------------\n\n";
    cout<<"\t\t\t Tic-Tac-Toe\n\n";
    cout<<"\t\t PLAYER = [ X ]      AI_BOT = [ O ]\n";
    cout<<"\n-------------------------------------------------------------------\n\n";
    char continu='y';
    do {
        int choice;
        //Prompts player option to start first
         cout<<"Would you like to start first? \n";
         cout<<"1. Yes\n";
         cout<<"2. No\n";
         cout<<"Enter your choice: ";
         cin>>choice;

         switch(choice)
         {
         case 1:
             {
                //Player starts first
                startTicTacToe(PLAYERTURNS);
                break;
             }

         case 2:
            {
                //AI-BOT starts first
                startTicTacToe(AITURNS);
                break;
            }

         default:
            {
                //print error after entering invalid options
                cout<<"Enter a valid option.";
            }
         }

        cout<<"\nWould you like to quit?(y/n) : ";
        cin>>continu;
        cout<<"\n";
    } while(continu=='n');
}

//Function to display the board status
void Tictactoe::displayBoard(bool trigger)
{

    if(trigger == true)
    {
        cout << "\t\t\t "<<setw(2) << scoreBoard[0][0] << " | " <<setw(2) << scoreBoard[0][1] << " | " <<setw(2) << scoreBoard[0][2] <<"\n";
        cout << "\t\t\t--------------\n";
        cout << "\t\t\t "<<setw(2) << scoreBoard[1][0] << " | " <<setw(2) << scoreBoard[1][1] << " | " <<setw(2) << scoreBoard[1][2] <<"\n";
        cout << "\t\t\t--------------\n";
        cout << "\t\t\t "<<setw(2) << scoreBoard[2][0] << " | " <<setw(2) << scoreBoard[2][1] << " | " <<setw(2) << scoreBoard[2][2] <<"\n\n";
    }

    else
    {
        cout << "\t\t\t " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] <<"\n";
        cout << "\t\t\t-----------\n";
        cout << "\t\t\t " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] <<"\n";
        cout << "\t\t\t-----------\n";
        cout << "\t\t\t " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] <<"\n\n";
    }
}

//function to display the game's instruction
void Tictactoe::displayInstructions()
{
    cout << "The first player or bot to get 3 marks in a row (up, down, across, or diagonally) is the winner.";
    cout << "\nChoose a cell numbered from 1 to 9 as below\n\n";
    cout << "\t\t\t 1 | 2 | 3 \n";
    cout << "\t\t\t-----------\n";
    cout << "\t\t\t 4 | 5 | 6 \n";
    cout << "\t\t\t-----------\n";
    cout << "\t\t\t 7 | 8 | 9 \n\n";

}

//function to initialize the game
//set the board empty
void Tictactoe::initialiseBoard()
{
    // Initially the board is empty
    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
            board[i][j] = ' ';
    }

}

//returns true when any of the row
//is crossed with X or O
bool Tictactoe::rowWin()
{
    for (int i = 0; i < SIDE; i++)
    {
        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2] &&
            board[i][0] != ' ')
            return (true);
    }
    return(false);
}

//returns true when any of the column
//is crossed with X or O
bool Tictactoe::columnWin()
{
    for (int i = 0; i < SIDE; i++)
    {
        if (board[0][i] == board[1][i] &&
            board[1][i] == board[2][i] &&
            board[0][i] != ' ')
            return (true);
    }
    return(false);
}

//returns true when either diagonal
//is crossed with X or O
bool Tictactoe::diagonalWin()
{
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2] &&
        board[0][0] != ' ')
        return(true);

    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0] &&
        board[0][2] != ' ')
        return(true);

    return(false);
}

//declares the winner of the game
void Tictactoe::who_wins(int whoseTurn)
{
    if (whoseTurn == AITURNS)
    {
        cout<<"AI_BOT wins!!\n";
    }
    else
    {
        cout<<"PLAYER wins!!\n";
    }
}

//returns true if the game ends
//else it returns false
bool Tictactoe::gameOver()
{
    return(rowWin() || columnWin() || diagonalWin());
}

// Function to calculate best score
int Tictactoe::minimax(int depth, bool isAI, bool print)
{
	int score = 0;
	int bestScore = 0;
	bool siblings = false;
	//if game is over
	if (gameOver() == true)
	{
		if (isAI == true) //if Player won return negative
        {
			return depth - 10;
        }
		if (isAI == false) //if AI won return positive
        {
			return 10 - depth;
        }
	}
	else
	{
		if (depth < 9)
		{
		    //if its AI's turn
			if (isAI == true)
			{
			    //initialize bestScore to -999
				bestScore = -999;
				for (int i = 0; i < SIDE; i++)
				{
					for (int j = 0; j < SIDE; j++)
					{
					    //if current cell is empty
						if (board[i][j] == ' ')
						{
							//if the previous child (the node found on the previous loop)
							//has siblings (which is the node found in this loop) print joint
							if (print == true && siblings == true)
								cout << "-.\n";

							board[i][j] = AIMOVE;//AI-BOT places marker on cell
							//calculate the score of current move
							score = minimax(depth + 1, false, print);

							//print for analysis
							if (print) {
								if (gameOver() == true)
									for (int i = depth; i < 8; i++)
										cout << setw(9) << ' ';
								cout << '(' << i * 3 + j + 1 << '|' << right << setw(3) << score << ")--";
							}
							//for upcoming siblings determination
							if (siblings == false)
								siblings = true;
							//print for analysis

							board[i][j] = ' '; //empties the cell placed
							//if the score calculated > than the best score
							if (score > bestScore)
							{
								bestScore = score; //bestScore equals current score
							}
						}
					}
				}
				return bestScore;
			}
			//else if its the player's turn
			else
			{
			    //initialize bestScore to 999
				bestScore = 999;
				for (int i = 0; i < SIDE; i++)
				{
					for (int j = 0; j < SIDE; j++)
					{
					    //if current cell is empty
						if (board[i][j] == ' ')
						{
							//if the previous child (the node found on the previous loop)
							//has siblings (which is the node found in this loop) print joint
							if (print == true && siblings == true)
								cout << "-.\n";

                            //place the player's marker on current cell
							board[i][j] = PLAYERMOVE;
							//calculate the score of this move
							score = minimax(depth + 1, true, print);

							//print for analysis
							if (print) {
								if (gameOver() == true)
									for (int i = depth; i < 8; i++)
										cout << setw(9) << ' ';
								cout << '(' << i * 3 + j + 1 << '|' << right << setw(3) << score << ")--";
							}
							//for upcoming siblings determination
							if (siblings == false)
								siblings = true;
							//print for analysis

							//empty the current cell
							board[i][j] = ' ';

							//if the player's score < bestScore
							if (score < bestScore)
							{
								bestScore = score; //bestScore equals current score
							}
						}
					}
				}
				return bestScore;
			}
		}
		else
		{
			return 0;
		}
	}
}

void Tictactoe::showScoreAnalysis()
{
    cout<<endl;
    cout<<"Show Score:"<<endl;
    displayBoard(true);
}

//This function is to get a random square with the best score
int Tictactoe::getRandomSquare(int bestScore)
{
    int repeat=0;
    int bestsquare=-1;
    srand (static_cast<unsigned int>(time(NULL)));
    for (int i=0;i<SIDE;i++)
    {
        for(int j=0;j<SIDE;j++)
        {
            if (scoreBoard[i][j]==bestScore)
            {
                repeat++;
            }
        }
    }
    repeat = rand()%repeat;
    for(int x=0;x<SIDE;x++)
    {
        for (int y=0;y<SIDE;y++)
        {
            if (scoreBoard[x][y] == bestScore)
            {
                if (repeat == 0)
                {
                    bestsquare = (x*3) + y;
                    cout << '(' << bestsquare+1<< '|' << right << setw(3) << bestScore << ")<---Pick\n";
                    break;
                }
                else
                    repeat--;
            }
        }
        if (bestsquare != -1)
            break;

    }
    return bestsquare;
}

// Function to calculate best move
int Tictactoe::bestMove(int moveIndex)
{
	int a = -1, b = -1;
	int score = 0, bestScore = -999;
	int deepth;
	bool print = false;
	bool siblings = false;
	if (moveIndex > 4) {
		print = true;
		deepth = 9 - moveIndex;
		if(deepth % 2 == 0){
            for (int i = 0; i < deepth; i++) {
                if (i % 2 == 0)
                    cout << left << setw(9) << " MIN";
                else
                    cout << left << setw(9) << " MAX";
            }
		}
		else{
            for (int i = 0; i < deepth; i++) {
                if (i % 2 == 0)
                    cout << left << setw(9) << " MAX";
                else
                    cout << left << setw(9) << " MIN";
            }
		}
		cout << endl;
	}
	for (int i = 0; i < SIDE; i++)
	{
		for (int j = 0; j < SIDE; j++)
		{
			if (board[i][j] == ' ')
			{
				//if the previous child (the node found on the previous loop)
				//has siblings (which is the node found in this loop) print joint
				if (print == true && siblings == true)
					cout << "-.\n";

				board[i][j] = AIMOVE;
				score = minimax(moveIndex + 1, false, print);

				//print for analysis
				if (print) {
					if (gameOver() == true)
						for (int i = moveIndex; i < 8; i++)
							cout << setw(9) << ' ';
					cout << '(' << i * 3 + j + 1 << '|' << right << setw(3) << score << ")--";
				}
				//for upcoming siblings determination
				if (siblings == false)
					siblings = true;
				//print for analysis

				board[i][j] = ' ';
				if (score > bestScore)
				{
					bestScore = score;
					a = i;
					b = j;
				}
				scoreBoard[i][j]=score;
			}
			else
            {
                scoreBoard[i][j]= 99;
            }
		}
	}
	return getRandomSquare(bestScore);
}

//function to start the tic-tac-toe game
void Tictactoe::startTicTacToe(bool Turns)
{
    int moveIndex = 0, x = 0, y = 0;

    //prints the instruction
    displayInstructions();

    // Keep playing till the game is over or it is a draw
    while (gameOver() == false && moveIndex != SIDE*SIDE)
    {
        int n;
        //if its the AI's turn
        if (Turns == AITURNS)
        {
            //calculates the best move
            cout << "---------- AI's Turns ----------\n";
            n = bestMove(moveIndex);
            x = n / SIDE;
            y = n % SIDE;
            board[x][y] = AIMOVE; //AI places marker
            showScoreAnalysis();
            cout<<"AI_BOT has put an " <<AIMOVE <<" in cell " <<n+1 <<"\n\n";
            displayBoard(false); //display the board's status
            moveIndex ++;
            Turns = PLAYERTURNS; //switch turn to player
            cout << "---------- AI's Turns Over ----------\n\n";
        }
        //if its the player's turn
        else
        {
            cout << "---------- PLAYER's Turns ----------\n";
            cout<<"You can insert into the following cells : ";
            for(int i=0; i<SIDE; i++)
                for (int j = 0; j < SIDE; j++)
                    if (board[i][j] == ' ')
                    {
                        //prints the available cells to place
                        cout<<(i * 3 + j) + 1 <<" ";
                    }
            cout<<"\n\nEnter the position = ";
            cin>>n; //prompts marker position
            n--;
            x = n / SIDE;
            y = n % SIDE;
            if(board[x][y] == ' ' && n<9 && n>=0)
            {
                board[x][y] = PLAYERMOVE; //place player's marker in cell
                cout<<"\nPLAYER has put an " <<PLAYERMOVE <<" in cell " <<n+1 <<"\n\n";
                displayBoard(false); //prints board status
                moveIndex ++;
                Turns = AITURNS; //switch turn to AI-BOT
            }
            //if placed cell is not empty
            else if(board[x][y] != ' ' && n<9 && n>=0)
            {
                //print error
                cout<<"\nPosition is occupied, select any one place from the available places\n\n";
            }

            //if entered position is out of bound
            else if(n<0 || n>8)
            {
                //print error
                cout<<"Invalid position\n";
            }
            else;
            cout << "---------- PLAYERS's Turns Over ----------\n\n";
        }
    }

    // If the game ends with a draw
    if (gameOver() == false && moveIndex == SIDE * SIDE)
    {
        cout<<"It's a draw\n";
    }
    else
    {
        // Toggling the user to declare the actual winner
        if (Turns == AITURNS)
            Turns = PLAYERTURNS;
        else
            Turns = AITURNS;

        who_wins(Turns);
    }
    initialiseBoard(); //Reset
}
