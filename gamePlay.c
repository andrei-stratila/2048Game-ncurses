#include "functions.h"

double Log2(double x){
	return log(x) / log(2.0);
}

//Reset score and board
void resetBoard(int board[4][4], int *score){
	int i, j;
	*score = 0;
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			board[i][j] = 0;
}

//Reset previous board and prevscore
void resetPrevBoard(int prevBoard[4][4], int *prevScore){
	int i, j;
	*prevScore = 0;
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			prevBoard[i][j] = 0;
}


//Print info about controls
void printInfo(WINDOW *winGame){
	int infoY = LINES - 10;
	wattron(winGame, COLOR_PAIR(31) | A_BOLD | A_BLINK);	
	mvwprintw(winGame, infoY++, (COLS - 36) / 2, "Press < A or Arrow LEFT > to move left");
	mvwprintw(winGame, infoY++, (COLS - 36) / 2, "Press < D or Arrow RIGHT > to move right");
	mvwprintw(winGame, infoY++, (COLS - 36) / 2, "Press < S or Arrow DOWN > to move down");
	mvwprintw(winGame, infoY++, (COLS - 36) / 2, "Press < W or Arrow UP > to move up");
	wattroff(winGame, COLOR_PAIR(31) | A_BOLD | A_BLINK);

	wattron(winGame, COLOR_PAIR(32) | A_BOLD | A_BLINK);	
	mvwprintw(winGame, LINES - 4, (COLS - 18 ) / 2, "Press < Q > to quit");
	wattroff(winGame, COLOR_PAIR(32) | A_BOLD | A_BLINK);
	wrefresh(winGame);
}

//Print current time
void printTime(WINDOW *winGame){
	time_t currentTime = time(NULL);
	struct tm *area = localtime(&currentTime);
	int timeY = 1, timeX = 2;
	wattron(winGame, COLOR_PAIR(32) | A_BOLD | A_BLINK);		
	mvwprintw(winGame, timeY, timeX, "Time: %s", asctime(area));
	wattroff(winGame, COLOR_PAIR(32) | A_BOLD | A_BLINK);
}

//Print board borders
void createBorders(WINDOW *winGame){
	int centerX = COLS / 2;
	int centerY = LINES / 2;
	int startX = centerX - 20, stopX = centerX + 20;
	int startY = centerY - 8, stopY = centerY + 8;
	int i,j;
	wattron(winGame, COLOR_PAIR(25) | A_BOLD | A_BLINK);
	mvwaddch(winGame, startY, startX, ACS_ULCORNER);
	mvwaddch(winGame, centerY, centerX, ACS_PLUS);
	mvwaddch(winGame, startY, stopX, ACS_URCORNER);
	mvwaddch(winGame, stopY, startX, ACS_LLCORNER);
	mvwaddch(winGame, stopY, stopX, ACS_LRCORNER);
	for(i = startX + 1; i < stopX; i++){
		for(j = startY; j <= stopY; j = j + 4){
			if(j == startY && (i - startX) % 10 == 0)
				mvwaddch(winGame, j, i, ACS_TTEE);
			else if(j == stopY && (i - startX) % 10 == 0)
				mvwaddch(winGame, j, i, ACS_BTEE);
			else
				mvwaddch(winGame, j, i, ACS_HLINE);
		}
	}
	for(j = startX; j <= stopX; j = j + 10){
		for(i = startY + 1; i < stopY; i++){
				mvwaddch(winGame, i, j, ACS_VLINE);
		}
	}
	wattroff(winGame, COLOR_PAIR(25) | A_BOLD | A_BLINK);
	wrefresh(winGame);
	refresh();
}

//Return number of empty cells in board and find their positions
int verifyEmptyCells(int board[4][4], int emptyRow[16], int emptyCol[16]){
	int i, j, n_Pairs = 0;
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4;j++){
			if(board[i][j] == 0){
				emptyRow[n_Pairs] = i;
				emptyCol[n_Pairs] = j;
				n_Pairs++;
			}
		}
	}
	return n_Pairs;
}

//Generate random value in board
void generateRandom(int board[4][4]){
	int random_Pair, random_Val, n_Pairs;
	srand(time(NULL));
	int values[] = {2, 4};
	int emptyRow[16], emptyCol[16];
	n_Pairs = verifyEmptyCells(board, emptyRow, emptyCol);
	random_Pair = rand() % n_Pairs;
	random_Val = rand() % 2;
	board[emptyRow[random_Pair]][emptyCol[random_Pair]] = values[random_Val];
}

//Update board for key A
int updateBoard_A(int board[4][4]){
	int aux[4][4];
	int i,j,t,nr;
	int score = 0;
	for(i = 0; i < 4; i++){
		nr = 0;
		for(j = 0; j < 4; j++){
			if(board[i][j] == 0){
				continue;
			}
			else{
				for(t = j + 1; t < 4; t++){
					if(board[i][t] == board[i][j]){
						board[i][j] = board[i][j] * 2;
						score = score + board[i][j];
						board[i][t] = 0;
						break;
					}
					else if(board[i][t] != 0)
						break;
				}
				aux[i][nr++] = board[i][j];
			}
		}
		while(nr != 4)
			aux[i][nr++] = 0;
	}
	memcpy(board, aux, 4 * 4 * sizeof(int));
	return score;
}

//Update board for key D
int updateBoard_D(int board[4][4]){
	int aux[4][4];
	int i, j, t, nr;
	int score = 0;
	for(i = 0; i < 4; i++){
		nr = 0;
		for(j = 3; j >= 0; j--){
			if(board[i][j] == 0){
				nr++;
				continue;
			}
			else{
				for(t = j - 1; t >= 0; t--){
					if(board[i][t] == board[i][j]){
						board[i][j] = board[i][j] * 2;
						score = score + board[i][j];
						board[i][t] = 0;
						break;
					}
					else if(board[i][t] != 0)
						break;
				}
			}
		}
		for(t = 0; t < nr; t++)
			aux[i][t] = 0;
		for(t = 0; t < 4; t++)
			if(board[i][t] != 0)
				aux[i][nr++] = board[i][t];
	}

	memcpy(board, aux, 4 * 4 * sizeof(int));
	return score;
}


//Update board for key S
int updateBoard_S(int board[4][4]){
	int aux[4][4];
	int i, j, t, nr;
	int score = 0;
	for(i = 0; i < 4; i++){
		nr = 0;
		for(j = 3; j >= 0; j--){
			if(board[j][i] == 0){
				nr++;
				continue;
			}
			else{
				for(t = j - 1; t >= 0; t--){
					if(board[t][i] == board[j][i]){
						board[j][i] = board[j][i] * 2;
						score = score + board[j][i];
						board[t][i] = 0;
						break;
					}
					else if(board[t][i] != 0)
						break;
				}
			}
		}
		for(t = 0; t < nr; t++)
			aux[t][i] = 0;
		for(t = 0; t < 4; t++)
			if(board[t][i] != 0)
				aux[nr++][i] = board[t][i];
	}

	memcpy(board, aux, 4 * 4 * sizeof(int));
	return score;
}

//Update board for key W
int updateBoard_W(int board[4][4]){
	int aux[4][4];
	int i, j, t, nr;
	int score = 0;
	for(i = 0; i < 4; i++){
		nr = 0;
		for(j = 0; j < 4; j++){
			if(board[j][i] == 0){
				continue;
			}
			else{
				for(t = j + 1; t < 4; t++){
					if(board[t][i] == board[j][i]){
						board[j][i] = board[j][i] * 2;
						score = score + board[j][i];
						board[t][i] = 0;
						break;
					}
					else if(board[t][i] != 0)
						break;
				}
				aux[nr++][i] = board[j][i];
			}
		}
		while(nr != 4)
			aux[nr++][i] = 0;
	}

	memcpy(board, aux, 4 * 4 * sizeof(int));
	return score;
}

//Verify if board changed
int boardUnchanged(int board[4][4], int prevBoard[4][4]){
	int i, j;
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			if(board[i][j] != prevBoard[i][j])
				return 0;
	return 1;
}

//Return number of empty cells in board
int countEmptyCells(int board[4][4]){
	int i, j, emptyCell = 0;
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			if(board[i][j] == 0)
				emptyCell++;
	return emptyCell;
}


//Verify if game is over
int gameOver(int board[4][4], int prevBoard[4][4]){
	
	updateBoard_A(board);
	if(boardUnchanged(board, prevBoard) == 0){
		memcpy(board, prevBoard, 4 * 4 * sizeof(int));
		return 0;
	}
	updateBoard_S(board);
	if(boardUnchanged(board, prevBoard) == 0){
		memcpy(board, prevBoard, 4 * 4 * sizeof(int));
		return 0;
	}
	updateBoard_D(board);
	if(boardUnchanged(board, prevBoard) == 0){
		memcpy(board, prevBoard, 4 * 4 * sizeof(int));
		return 0;
	}
	updateBoard_W(board);
	if(boardUnchanged(board, prevBoard) == 0){
		memcpy(board, prevBoard, 4 * 4 * sizeof(int));
		return 0;
	}
	return 1;
}

//Automove in the direction where score would be max
char autoMove(int board[4][4], int prevBoard[4][4]){
	char selectKey;
	int maxEmptyCells = -1, nrEmptyCells = 0;

	updateBoard_W(board);
	nrEmptyCells = countEmptyCells(board);
	if(nrEmptyCells >= maxEmptyCells){
		maxEmptyCells = nrEmptyCells;
		if(boardUnchanged(board, prevBoard) == 0)
			selectKey = 'w'; 
	}
	memcpy(board, prevBoard, 4 * 4 * sizeof(int));

	updateBoard_A(board);
	nrEmptyCells = countEmptyCells(board);
	if(nrEmptyCells >= maxEmptyCells){
		maxEmptyCells = nrEmptyCells;
		if(boardUnchanged(board, prevBoard) == 0)
			selectKey = 'a'; 
	}
	memcpy(board, prevBoard, 4 * 4 * sizeof(int));

	updateBoard_S(board);
	nrEmptyCells = countEmptyCells(board);
	if(nrEmptyCells >= maxEmptyCells){
		maxEmptyCells = nrEmptyCells;
		if(boardUnchanged(board, prevBoard) == 0)
			selectKey = 's'; 
	}
	memcpy(board, prevBoard, 4 * 4 * sizeof(int));

	updateBoard_D(board);
	nrEmptyCells = countEmptyCells(board);
	if(nrEmptyCells >= maxEmptyCells){
		maxEmptyCells = nrEmptyCells;
		if(boardUnchanged(board, prevBoard) == 0)
			selectKey = 'd'; 
	}
	memcpy(board, prevBoard, 4 * 4 * sizeof(int));

	return selectKey;
}

//Take input from STDIN
char inputChar(WINDOW *winGame, int board[4][4], int prevBoard[4][4], int secAutoMove){
	int input;
	time_t begin,end;
	int seconds;
	time(&begin);
	while(1){
		nodelay(winGame, TRUE);
		time(&end);
		seconds = difftime(end, begin);
		printTime(winGame);
			keypad(winGame, TRUE);
		input = wgetch(winGame);
		switch(input){
			case KEY_UP:
				input = 'w';
				break;
			case KEY_DOWN:
				input = 's';
				break;
			case KEY_LEFT:
				input = 'a';
				break;
			case KEY_RIGHT:
				input = 'd';
				break;
			default:
				break;
		}
		input = tolower(input);
		if(seconds == secAutoMove){
			input = autoMove(board, prevBoard);
			return input;
		}
		if(strchr("asdwq", input))
			return input;
	}
}


//Print text "Game Over" (Ascii Art)
void printGameOverText(WINDOW *winGame){
	int yPos = 3, xPos = (COLS - 52) / 2;
	wattron(winGame, A_BOLD | A_BLINK);
	mvwprintw(winGame, yPos++, xPos,"   ____                       ___                 _ ");  
	mvwprintw(winGame, yPos++, xPos,"  / ___| __ _ _ __ ___   ___ / _ \\__   _____ _ __| |"); 
	mvwprintw(winGame, yPos++, xPos," | |  _ / _` | '_ ` _ \\ / _ | | | \\ \\ / / _ | '__| |");
	mvwprintw(winGame, yPos++, xPos," | |_| | (_| | | | | | |  __| |_| |\\ V |  __| |  |_|");
	mvwprintw(winGame, yPos++, xPos,"  \\____|\\__,_|_| |_| |_|\\___|\\___/  \\_/ \\___|_|  (_)");
	wattroff(winGame, A_BOLD | A_BLINK);
	wrefresh(winGame);                                       
}

//Game over for classic mode
void stateGameOverClassic(WINDOW *winGame, int finalScore, int Obstacles){
	char inputKey;
	printGameOverText(winGame);
	int highScore = 0;
	//Verificare scor de introdus in Leaderbord
	highScore = verifyScoreForLeaderbord(winGame, finalScore, Obstacles);
	wrefresh(winGame);
	if(highScore == 1)
		return;
	
	int yPos = LINES / 3, xPos = COLS / 12;
	wattron(winGame, COLOR_PAIR(23) | A_BOLD);
	mvwprintw(winGame, yPos++, xPos, "Congratulations!");
	mvwprintw(winGame, yPos++, xPos, "Your score: %d", finalScore);
	wattroff(winGame, COLOR_PAIR(23) |A_BOLD);
	//Waits for Q (quit)
	while(1){
		nodelay(winGame, TRUE);
		printTime(winGame);
		inputKey = wgetch(winGame);
		inputKey = tolower(inputKey);	
		if(inputKey == 'q')
			return;
	}
}

//Game over for every mode except Classic
void stateGameOver(WINDOW *winGame){
	char inputKey;
	printGameOverText(winGame);
	wrefresh(winGame);
	//Waits for Q (quit)
	while(1){
		nodelay(winGame, TRUE);
		printTime(winGame);
		inputKey = wgetch(winGame);
		inputKey = tolower(inputKey);	
		if(inputKey == 'q')
			return;
	}
}

//Update board in window
void printBoardforMode(WINDOW *winGame, int board[4][4], int score, int mode){
	if(mode == 0)
		printBoardClassic(winGame, board, score);
	else if(mode == 1)
		printBoardReverse(winGame, board);
	else if(mode == 2)
		printBoardLogarithmic(winGame, board);
	else if(mode == 3)
		printBoardAlphabet(winGame, board);
	else if(mode == 4)
		printBoardFibonacci(winGame, board);
}

//Create obstacles
void createObstacles(int board[4][4], int Obstacles){
	int randomX, randomY, negValue = 0;
	srand(time(NULL));
	int values[] = {0, 1, 2, 3};
	while(Obstacles != 0){
		randomX = rand() % 4;
		randomY = rand() % 4;
		if(board[values[randomX]][values[randomY]] == 0){
			negValue--;
			board[randomX][randomY] = negValue;
			Obstacles--;
		}
	}
}

//Main function for gameplay
void playGame(int board[4][4], WINDOW *winGame, int *score, int *reset, 
	int secAutoMove, int mode, int Obstacles){
	
	wbkgd(winGame, COLOR_PAIR(20));
	int prevBoard[4][4], prevScore = 0, verifyMove;
	printBoardforMode(winGame, board, *score, mode);
	if(*reset == 1){
		if(Obstacles != 0)
			createObstacles(board, Obstacles);
		mvwprintw(winGame, 4, 10, "");
		resetPrevBoard(prevBoard, &prevScore);
		*reset = 0;
	}

	//Two random numbers for new game
	if(*score == 0 && countEmptyCells(board) == 16){
		generateRandom(board);
		generateRandom(board);
		printBoardforMode(winGame, board, *score, mode);
	}	

	int inputKey;
	int scoreToAdd = 0;
	while(1){
		//Update previous board and score
		memcpy(prevBoard, board, 4 * 4 * sizeof(int));
		prevScore = *score;

		//Take input
		inputKey = inputChar(winGame, board, prevBoard, secAutoMove);
		
		//Exit game for q
		if(inputKey == 'q')
			return;

		//Verify if game over
		if(countEmptyCells(board) == 0){
			if(gameOver(prevBoard, board) == 1){
				if(mode == 0){
					*reset = 1;
					stateGameOverClassic(winGame, *score, Obstacles);
					break;
				}
				else{
					stateGameOver(winGame);
					break;
				}
			}	
		} 
		switch(inputKey){
			case 'a':
				scoreToAdd = updateBoard_A(board); 
				break;
			case 's':
				scoreToAdd = updateBoard_S(board);
				break;
			case 'd':
				scoreToAdd = updateBoard_D(board);
				break;
			case 'w':
				scoreToAdd = updateBoard_W(board);
				break;
			default:
				break;
		}
		*score = *score + scoreToAdd;
		printBoardforMode(winGame, board, *score, mode);

		//Generate random value if board changed
		verifyMove = boardUnchanged(board, prevBoard);
		if(verifyMove == 0){
			generateRandom(board);
			printBoardforMode(winGame, board, *score, mode);
		}

	}
}