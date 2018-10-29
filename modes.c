#include "functions.h"

//Fill board cells with colors
void fillCells(WINDOW *winGame, int startX, int startY, int num_Color){
	int t1, t2;
	for(t1 = startX - 4; t1 <= startX + 4; t1++){
			for(t2 = startY - 1; t2 <= startY + 1; t2++){
				wattron(winGame, COLOR_PAIR(num_Color) | A_BOLD);
				mvwprintw(winGame, t2, t1, "%s", " ");
				wattroff(winGame, COLOR_PAIR(num_Color) | A_BOLD);
		}
	}
}

//Update board and score for Classic Mode
void printBoardClassic(WINDOW *winGame, int board[4][4], int score){
	//Initializarea variabilelor si calculul coordonatelor
	werase(winGame);
	wrefresh(winGame);
	refresh();
	printInfo(winGame);
	int startX, startY, scoreX, scoreY;
	scoreX = 2;
	scoreY = 2;
	int num_Color = 0;
	createBorders(winGame);
	//Print score
	wattron(winGame, COLOR_PAIR(32) | A_BOLD );
	mvwprintw(winGame, scoreY, scoreX, "Score: %d", score);
	wattroff(winGame, COLOR_PAIR(32) | A_BOLD );
	startX = COLS / 2 -  15;
	startY = LINES / 2 - 6;
	int i, j;
	char toPrint[6];
	//Print board and for each unique values a color is set
	for(i = 0 ; i < 4; i++){
		for(j  = 0; j < 4; j++){
			if(board[i][j] != 0){
				if(board[i][j] > 0){
					num_Color = ((int)Log2(board[i][j]) + 1) % 9;
					if(num_Color == 0)
						num_Color = 4;
					fillCells(winGame, startX, startY, num_Color);
					sprintf(toPrint, "%d", board[i][j]);
					wattron(winGame, COLOR_PAIR(num_Color) | A_BOLD);
					mvwprintw(winGame, startY, startX - strlen(toPrint) / 2, "%s", toPrint);
					wattroff(winGame, COLOR_PAIR(num_Color) | A_BOLD);
				}
				//Print obstacles if they exist
				else{
					strcpy(toPrint, "XXXX");
					wattron(winGame, COLOR_PAIR(22) | A_REVERSE);
					mvwprintw(winGame, startY, startX - strlen(toPrint) / 2, "%s", toPrint);
					wattroff(winGame, COLOR_PAIR(22) | A_REVERSE);
				}
			}
	
			startX = startX + 10;
			wrefresh(winGame);
			refresh();
		}
		startX = startX - 10 * 4;
		startY = startY + 4;
	}
	wrefresh(winGame);
	refresh();
}

//Update board and score for Reverse Mode
void printBoardReverse(WINDOW *winGame, int board[4][4]){
	//Initializarea variabilelor si calculul coordonatelor
	werase(winGame);
	wrefresh(winGame);
	refresh();
	printInfo(winGame);
	int startX, startY, scoreX, scoreY;
	scoreX = 2;
	scoreY = 2;
	int num_Color = 0;
	createBorders(winGame);
	//Print score
	wattron(winGame, COLOR_PAIR(32) | A_BOLD );
	mvwprintw(winGame, scoreY, scoreX, "Score: N/A");
	wattroff(winGame, COLOR_PAIR(32) | A_BOLD );
	startX = COLS / 2 -  15;
	startY = LINES / 2 - 6;
	int i, j, value;
	char toPrint[6];
	//Print board and for each unique values a color is set
	for(i = 0 ; i < 4; i++){
		for(j  = 0; j < 4; j++){
			if(board[i][j] != 0){
				//Values go from 2048 to 1
				if(board[i][j] > 0){
					num_Color = ((int)Log2(board[i][j]) + 1) % 9;
					value = 4096 / board[i][j];
					if(num_Color == 0)
						num_Color = 4;
					fillCells(winGame, startX, startY, num_Color);
					sprintf(toPrint, "%d", value);
					wattron(winGame, COLOR_PAIR(num_Color) | A_BOLD);
					mvwprintw(winGame, startY, startX - strlen(toPrint) / 2, "%s", toPrint);
					wattroff(winGame, COLOR_PAIR(num_Color) | A_BOLD);
				}
				//Print obstacles if they exist
				else{
					strcpy(toPrint, "XXXX");
					wattron(winGame, COLOR_PAIR(22) | A_REVERSE);
					mvwprintw(winGame, startY, startX - strlen(toPrint) / 2, "%s", toPrint);
					wattroff(winGame, COLOR_PAIR(22) | A_REVERSE);
				}
			}	
			startX = startX + 10;
			wrefresh(winGame);
			refresh();
		}
		startX = startX - 10 * 4;
		startY = startY + 4;
	}
	wrefresh(winGame);
	refresh();
}

//Update board and score for Logarithmic Mode
void printBoardLogarithmic(WINDOW *winGame, int board[4][4]){
	//Initializarea variabilelor si calculul coordonatelor
	werase(winGame);
	wrefresh(winGame);
	refresh();
	printInfo(winGame);
	int startX, startY, scoreX, scoreY;
	scoreX = 2;
	scoreY = 2;
	int num_Color = 0;
	createBorders(winGame);
	//Print score
	wattron(winGame, COLOR_PAIR(32) | A_BOLD );
	mvwprintw(winGame, scoreY, scoreX, "Score: N/A");
	wattroff(winGame, COLOR_PAIR(32) | A_BOLD );
	startX = COLS / 2 -  15;
	startY = LINES / 2 - 6;
	int i, j, value;
	char toPrint[6];
	//Print board and for each unique values a color is set
	for(i = 0 ; i < 4; i++){
		for(j  = 0; j < 4; j++){
			if(board[i][j] != 0){
				//Values go from 1 to log2(2^x)
				if(board[i][j] > 0){
					value = (int)Log2(board[i][j]);
					num_Color = (value + 1) % 9;
					if(num_Color == 0)
						num_Color = 4;
					fillCells(winGame, startX, startY, num_Color);
					sprintf(toPrint, "%d", value);
					wattron(winGame, COLOR_PAIR(num_Color) | A_BOLD);
					mvwprintw(winGame, startY, startX - strlen(toPrint) / 2, "%s", toPrint);
					wattroff(winGame, COLOR_PAIR(num_Color) | A_BOLD);
				}
				//Print obstacles if they exist
				else{
					strcpy(toPrint, "XXXX");
					wattron(winGame, COLOR_PAIR(22) | A_REVERSE);
					mvwprintw(winGame, startY, startX - strlen(toPrint) / 2, "%s", toPrint);
					wattroff(winGame, COLOR_PAIR(22) | A_REVERSE);
				}
			}	
			startX = startX + 10;
			wrefresh(winGame);
			refresh();
		}
		startX = startX - 10 * 4;
		startY = startY + 4;
	}
	wrefresh(winGame);
	refresh();
}

//Update board and score for Alphabet Mode
void printBoardAlphabet(WINDOW *winGame, int board[4][4]){
	//Initializarea variabilelor si calculul coordonatelor
	werase(winGame);
	wrefresh(winGame);
	refresh();
	printInfo(winGame);
	int startX, startY, scoreX, scoreY;
	scoreX = 2;
	scoreY = 2;
	int num_Color = 0;
	createBorders(winGame);
	//Print score
	wattron(winGame, COLOR_PAIR(32) | A_BOLD );
	mvwprintw(winGame, scoreY, scoreX, "Score: N/A");
	wattroff(winGame, COLOR_PAIR(32) | A_BOLD );
	startX = COLS / 2 -  15;
	startY = LINES / 2 - 6;
	int i, j;
	char toPrint[6], value;
	//Print board and for each unique values a color is set
	for(i = 0 ; i < 4; i++){
		for(j  = 0; j < 4; j++){
			if(board[i][j] != 0){
				//Values go from A to Z
				if(board[i][j] > 0){
					value = (char)((int)Log2(board[i][j]) + 64);
					num_Color = (value + 1) % 9;
					if(num_Color == 0)
						num_Color = 4;
					fillCells(winGame, startX, startY, num_Color);
					wattron(winGame, COLOR_PAIR(num_Color) | A_BOLD);
					mvwprintw(winGame, startY, startX - 1 / 2, "%c", value);
					wattroff(winGame, COLOR_PAIR(num_Color) | A_BOLD);
				}
				//Print obstacles if they exist
				else{
					strcpy(toPrint, "XXXX");
					wattron(winGame, COLOR_PAIR(22) | A_REVERSE);
					mvwprintw(winGame, startY, startX - strlen(toPrint) / 2, "%s", toPrint);
					wattroff(winGame, COLOR_PAIR(22) | A_REVERSE);
				}
			}	
			startX = startX + 10;
			wrefresh(winGame);
			refresh();
		}
		startX = startX - 10 * 4;
		startY = startY + 4;
	}
	wrefresh(winGame);
	refresh();
}

//Generate Fibonacci's numbers
void generateFibonacci(int *fib){
	int i;
	fib[0] = 1;
	fib[1] = 1;
	for(i = 2; i < 12; i++)
		fib[i] = fib[i - 1] + fib[i - 2];
}

//Update board and score for Fibonnaci Mode
void printBoardFibonacci(WINDOW *winGame, int board[4][4]){
	//Initializarea variabilelor si calculul coordonatelor
	werase(winGame);
	wrefresh(winGame);
	refresh();
	printInfo(winGame);
	int startX, startY, scoreX, scoreY;
	scoreX = 2;
	scoreY = 2;
	int num_Color = 0;
	createBorders(winGame);
	//Print score
	wattron(winGame, COLOR_PAIR(32) | A_BOLD );
	mvwprintw(winGame, scoreY, scoreX, "Score: N/A");
	wattroff(winGame, COLOR_PAIR(32) | A_BOLD );
	startX = COLS / 2 -  15;
	startY = LINES / 2 - 6;
	int i, j, value;
	char toPrint[6];
	int fib[32];
	generateFibonacci(fib);
	//Afisarea tablei de joc si atribuirea unei culori in functie de valoare
	//pentru 0 se alege culoarea de fundal identica cu cea a culorii cifrei
	for(i = 0 ; i < 4; i++){
		for(j  = 0; j < 4; j++){
			if(board[i][j] != 0){
				if(board[i][j] > 0){
					value = (int)Log2(board[i][j]);
					num_Color = (value + 1) % 9;
					if(num_Color == 0)
						num_Color = 4;
					fillCells(winGame, startX, startY, num_Color);
					sprintf(toPrint, "%d", fib[value]);
					wattron(winGame, COLOR_PAIR(num_Color) | A_BOLD);
					mvwprintw(winGame, startY, startX - strlen(toPrint) / 2, "%s", toPrint);
					wattroff(winGame, COLOR_PAIR(num_Color) | A_BOLD);
				}
				//Print obstacles if they exist
				else{
					strcpy(toPrint, "XXXX");
					wattron(winGame, COLOR_PAIR(22) | A_REVERSE);
					mvwprintw(winGame, startY, startX - strlen(toPrint) / 2, "%s", toPrint);
					wattroff(winGame, COLOR_PAIR(22) | A_REVERSE);
				}
			}	
			startX = startX + 10;
			wrefresh(winGame);
			refresh();
		}
		startX = startX - 10 * 4;
		startY = startY + 4;
	}
	wrefresh(winGame);
	refresh();
}
