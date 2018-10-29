#include "functions.h"

//Takes the nickname from STDIN in string username[10]
void takeUsernameForLeaderbord(WINDOW *winGame, char username[10]){
	keypad(winGame, TRUE);
	int inputKey;
	username[10] = '\0';
	int index = 0;
	while(index != 10)
		username[index++] = ' ';
	index = 0;
	while(1){
		inputKey = wgetch(winGame);
		inputKey = tolower(inputKey);
		if(inputKey == 10 && index > 0){
			return;
		}
		else if ((inputKey == KEY_BACKSPACE || inputKey == 127 || inputKey == 8) && index > 0) {
			username[index-1] = ' ';
			mvwaddch(winGame, LINES / 3 + 3, COLS / 12 + 23 + index--, ' ');
			wrefresh(winGame);
		}
		else if(isalnum(inputKey) && index < 10){
			username[index++] = inputKey;
			wattron(winGame, A_BOLD | A_REVERSE);
			mvwaddch(winGame, LINES / 3 + 3, COLS / 12 + 23 + index, inputKey);
			wattroff(winGame, A_BOLD | A_REVERSE);
			wrefresh(winGame);
		}
	}
}

//Print message when High Score is achieved
void printNewEntry(WINDOW *winGame, int finalScore){
	int yPos = LINES / 3, xPos = COLS / 12;
	wattron(winGame, COLOR_PAIR(23) | A_BOLD);
	mvwprintw(winGame, yPos++, xPos, "New HIGH SCORE! Congratulations!");
	mvwprintw(winGame, yPos++, xPos, "Your score: %d", finalScore);
	wattroff(winGame, COLOR_PAIR(23) |A_BOLD);
	yPos++;
	wattron(winGame, COLOR_PAIR(24) | A_BOLD);
	mvwprintw(winGame, yPos++, xPos, "Register your score: ");
	mvwprintw(winGame, yPos++, xPos, "Type your name and press ENTER");
	wattroff(winGame, COLOR_PAIR(24) | A_BOLD);
	wrefresh(winGame);

}
//Create string with final score, nickname and number of obstacles to be add
//in leaderbord.txt and in Leaderbord menu
void createNewEntry(WINDOW *winGame, char newEntry[50], int finalScore, 
	int Obstacles){
	
	char aux1[10], username[10];
	//Add nickname
	takeUsernameForLeaderbord(winGame, username);
	strcpy(newEntry, username);
	strcat(newEntry, "\t\t");
	//Add number of obstacles
	if(Obstacles == 0)
		strcat(newEntry, "NONE \t\t");
	else{
		sprintf(aux1, "%d", Obstacles);
		strcat(newEntry, "  ");
		strcat(newEntry, aux1);
		strcat(newEntry, "  \t\t");
	}
	//Add final score
	sprintf(aux1, "%d", finalScore);
	strcat(newEntry, aux1);
	strcat(newEntry, "\n");
}

//Read existent entries in Leaderbord(leaderbord.txt) and verify if new High Score
//was achieved; if yes then a new entry will be created
int readFileMaxScore(WINDOW *winGame, char entries[12][50], FILE *file, 
	int finalScore, int Obstacles){
	
	int number = 0, p = 1, pos = -1, nEntries = 0, index;
	char aux[50];
	char newEntry[50];
	while(nEntries != 10){
		if(fgets(aux, 50, file) == NULL)
			break;
		number = 0; 
		p = 1;
		index = strlen(aux) - 2;
		while(isdigit(aux[index])){
			number = number + (int)(aux[index] - '0') * p;
			p = p * 10;
			index--;
		}
		if(finalScore > number && pos == -1){
			pos = 1;
			printNewEntry(winGame, finalScore);
			createNewEntry(winGame, newEntry, finalScore, Obstacles);
			strcpy(entries[nEntries], newEntry);
			nEntries++;
		}
		strcpy(entries[nEntries], aux);
		nEntries++;
	}
	if(nEntries < 10 && pos == -1){
		pos = 1;
		printNewEntry(winGame, finalScore);
		createNewEntry(winGame, newEntry, finalScore, Obstacles);
		strcpy(entries[nEntries], newEntry);
		nEntries++;
	}
	if(nEntries > 10)
		nEntries = 10;
	return pos;
}

//Verify if new High Score was achieved; return 1 for yes, 0 otherwise
//Update the Leaderbord(leaderbord.txt)
int verifyScoreForLeaderbord(WINDOW *winGame, int finalScore, int Obstacles){
	FILE *file = fopen("leaderbord.txt", "r");
	char entries[12][50];
	int i, pos;
	if(file){
		pos = readFileMaxScore(winGame, entries, file, finalScore, Obstacles);
		fclose(file);
		file = fopen("leaderbord.txt", "w");
		for(i = 0; i < 10; i++){
			if(entries[i][10] == '\t' && entries[i][11] == '\t')
				fprintf(file, "%s", entries[i]);
		}
		fclose(file);
	}
	if(pos == 1)
		return 1;
	else
		return 0;	
}

//Print text "Leaderbord" (Ascii Art)
void printLeaderbordText(WINDOW *winLeaderbord){
	int yPos = LINES / 16, xPos = (COLS - 56) / 2;
	wattron(winLeaderbord, A_BOLD );
	mvwprintw(winLeaderbord, yPos++, xPos," _                   _           _                   _ ");  
	mvwprintw(winLeaderbord, yPos++, xPos,"| |    ___  __ _  __| | ___ _ __| |__   ___  _ __ __| |"); 
	mvwprintw(winLeaderbord, yPos++, xPos,"| |   / _ \\/ _` |/ _` |/ _ \\ '__| '_ \\ / _ \\| '__/ _` |");
	mvwprintw(winLeaderbord, yPos++, xPos,"| |__|  __/ (_| | (_| |  __/ |  | |_) | (_) | | | (_| |");
	mvwprintw(winLeaderbord, yPos++, xPos,"|_____\\___|\\__,_|\\__,_|\\___|_|  |_.__/ \\___/|_|  \\__,_|");
	wattroff(winLeaderbord, A_BOLD );

	wattron(winLeaderbord, COLOR_PAIR(20) | A_BOLD );	
	mvwprintw(winLeaderbord, ++yPos, (COLS - 12 ) / 2,"CLASSIC MODE");
	wattroff(winLeaderbord, COLOR_PAIR(20) | A_BOLD );

	wattron(winLeaderbord, COLOR_PAIR(32) | A_BOLD );	
	mvwprintw(winLeaderbord, LINES - 2, (COLS - 18 ) / 2, "Press < Q > to quit");
	wattroff(winLeaderbord, COLOR_PAIR(32) | A_BOLD );	
	wrefresh(winLeaderbord);
}

//Print Leaderbord in window game
void printScoresLeaderbord(WINDOW *winLeaderbord, char entries[10][50]){
	int yPos = LINES / 16 + 8, xPos = (COLS - 65) / 2;
	wattron(winLeaderbord, COLOR_PAIR(23) | A_BOLD );
	mvwprintw(winLeaderbord, yPos++, xPos,"Pos\tName\t\t\tObstacles\tScores");
	wattron(winLeaderbord, COLOR_PAIR(23) | A_BOLD );
	xPos++;
	yPos++;
	int index;
	for(index = 0; index < 10; index++){
		if(!isalnum(entries[index][0]))
			break;
		wattron(winLeaderbord, COLOR_PAIR(20) | A_BOLD );
		mvwprintw(winLeaderbord, yPos, xPos, "%s", entries[index]);
		wattron(winLeaderbord, COLOR_PAIR(20) | A_BOLD );
		yPos = yPos + 2;
	}
	wrefresh(winLeaderbord);
}

//Read entries from file
void readFileData(char entries[10][50], FILE *file){
	int nEntries = 0;
	char aux[40];
	while(1){
		if(fgets(aux, 40, file) == NULL)
			break;
		if(isalnum(aux[0]))
			strcat(entries[nEntries++], aux);
	}
}

//Open leaderbord file(leaderbord.txt) and create the entries 
void importScores(WINDOW *winLeaderbord){
	FILE *file = fopen("leaderbord.txt", "r");
	char entries[10][50] = { "1.\t", "2.\t", "3.\t", "4.\t", "5.\t", 
							"6.\t", "7.\t", "8.\t", "9.\t", "10.\t"};
	if(file){
		readFileData(entries, file);
		printScoresLeaderbord(winLeaderbord, entries);
		fclose(file);
	}
	else{
		mvwprintw(winLeaderbord, COLS / 2, (COLS - 31) / 2, "Leaderbord file doesn't exist!");
		mvwprintw(winLeaderbord, COLS / 2, (COLS - 24) / 2, "Something went wrong...");
		wrefresh(winLeaderbord);
	}
}

//Main function for Leaderbord menu
void managerLeaderbord(WINDOW *winLeaderbord){
	wbkgd(winLeaderbord, COLOR_PAIR(20));
	wrefresh(winLeaderbord);
	int inputKey;
	importScores(winLeaderbord);
	//Bucla ce asteapta Q drept input pentru iesire
	while(1){
		nodelay(winLeaderbord, TRUE);
		inputKey = wgetch(winLeaderbord);
		inputKey = tolower(inputKey);
		if(inputKey == 'q'){
			werase(winLeaderbord);
			wrefresh(winLeaderbord);
			return;
		}
		printLeaderbordText(winLeaderbord);
	}
}