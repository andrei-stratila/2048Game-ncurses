//MENU.C
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <panel.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#define height 20
#define width 20

void print2048();
void showMenu(WINDOW *winMenu, int current, int n_optMenu, char *optMenu[]);
int createMenu(WINDOW *winMenu, int n_optMenu, char *optMenu[]);

double Log2(double x);
void resetBoard(int board[4][4], int *score);
void resetPrevBoard(int prevBoard[4][4], int *prevScore);
void printInfo(WINDOW *winGame);
void printTime(WINDOW *winGame);
void createBorders(WINDOW *winGame);

int createMenu(WINDOW *winMenu, int n_optMenu, char *optMenu[]);
void createBoard(int board[4][4]);
int startApp(WINDOW *winMenu, int n_optMenu, char *optMenu[]);
int updateBoard_W(int board[4][4]);
int updateBoard_A(int board[4][4]);
int updateBoard_D(int board[4][4]);
int updateBoard_W(int board[4][4]);
void resetBoard(int board[4][4], int *score);
void printBoardClassic(WINDOW *winGame, int board[4][4], int score);
void printBoardReverse(WINDOW *winGame, int board[4][4]);
void printBoardLogarithmic(WINDOW *winGame, int board[4][4]);
void printBoardAlphabet(WINDOW *winGame, int board[4][4]);
void printBoardFibonacci(WINDOW *winGame, int board[4][4]);
void playGame(int board[4][4], WINDOW *winGame, int *score, int *reset, 
	int secAutoMove, int mode, int Obstacles);
void print2048Text();

void printSettingsText(WINDOW *winSettings);
void managerSettings(WINDOW *winSettings, int *secAutoMove, int *mode, int *Obstacles);
void showSettings(WINDOW *winSettings, int current, int n_optSettings, char *optSettings[]);
int createSettings(WINDOW *winSettings, int n_optSettings, char *optSettings[]);
void setAutoMoveTime(WINDOW *winSettings, int *secAutoMove);
void printModeGameSett(WINDOW *winSettings, int gameMode);

void managerLeaderbord(WINDOW *winLeaderbord);
void readFileData(char entries[10][50], FILE *file);
void takeUsernameForLeaderbord(WINDOW *winGame, char username[10]);
void printNewEntry(WINDOW *winGame, int finalScore);
void createNewEntry(WINDOW *winGame, char newEntry[50], int finalScore, int Obstacles);
int readFileMaxScore(WINDOW *winGame, char entries[12][50], FILE *file, int 
	finalScore, int Obstacles);
int verifyScoreForLeaderbord(WINDOW *winGame, int finalScore, int Obstacles);