 #include "functions.h"

//Print text "Settings" (Ascii Art)
void printSettingsText(WINDOW *winSettings){
	int yPos = LINES / 16, xPos = (COLS - 36) / 2;
	wattron(winSettings, A_BOLD );
	mvwprintw(winSettings, yPos++, xPos," ____       _   _   _                ");  
	mvwprintw(winSettings, yPos++, xPos,"/ ___|  ___| |_| |_(_)_ __   __ _ ___ "); 
	mvwprintw(winSettings, yPos++, xPos,"\\___ \\ / _ \\ __| __| | '_ \\ / _` / __|");
	mvwprintw(winSettings, yPos++, xPos," ___) |  __/ |_| |_| | | | | (_| \\__ \\");
	mvwprintw(winSettings, yPos++, xPos,"|____/ \\___|\\__|\\__|_|_| |_|\\__, |___/");
	mvwprintw(winSettings, yPos++, xPos,"                            |___/     ");
	wattroff(winSettings, A_BOLD );
	wrefresh(winSettings);
}

//Create settings menu and return the choice
int createSettings(WINDOW *winSettings, int n_optSettings, char *optSettings[]){
	keypad(winSettings, TRUE);
	int current = 0, choice = -1, inputKey;
	showSettings(winSettings, current, n_optSettings, optSettings);
	//O bucla infinita in care se poate naviga meniul folosind KEY_UP
	//si KEY_DOWN, respectiv ENTER(case 10) pentru alegere
	while(1){
		inputKey = wgetch(winSettings);
		switch(inputKey){
			case KEY_UP:
				if(current == 0)
					current = n_optSettings - 1;
				else
					current--;
				break;
			case KEY_DOWN:
				if(current == n_optSettings - 1)
					current = 0;
				else
					current++;
				break;
			case 10:
				choice = current;
				break;
			default:
				break;
		}
		showSettings(winSettings, current, n_optSettings, optSettings);
		if(choice != -1)
			break;
	}

	return choice;
}

//Show settings menu at each call of createSettings
void showSettings(WINDOW *winSettings, int current, int n_optSettings, char *optSettings[]){
	werase(winSettings);
	wrefresh(winSettings);
	printSettingsText(winSettings);
	int maxLines, maxCols;
	getmaxyx(winSettings, maxLines, maxCols);
	int y = maxLines / 3, x = maxCols / 4;
	int index;
	for(index = 0; index < n_optSettings; index++, y = y + 2){
		if(current == index){
			wattron(winSettings, A_BOLD);
			mvwprintw(winSettings, y, x, "%s", optSettings[index]);
			wattroff(winSettings, A_BOLD);
		}
		else
			mvwprintw(winSettings, y, x, "%s", optSettings[index]);
	}
	wrefresh(winSettings);
}

//Print submenu AutoMove
void printAutoMoveSett(WINDOW *winSettings, int seconds){
	int maxLines, maxCols;
	getmaxyx(winSettings, maxLines, maxCols);
	int y = maxLines / 3, x = maxCols / 2;
	move(y, x);
	char toPrint[30] = "<<- ", aux[3];
	if (seconds == 0)
		strcat(toPrint, "NONE ->>");
	else{
		sprintf(aux, "%d", seconds);
		strcat(toPrint, aux);
		strcat(toPrint, " ->>");
	}
	wattron(winSettings, COLOR_PAIR(21) | A_BOLD);
	mvwprintw(winSettings, y, x, "%s", toPrint);
	wattroff(winSettings, COLOR_PAIR(21) | A_BOLD);
	wclrtoeol(winSettings);
	wrefresh(winSettings);
}

//Set timer for autoMove option
void setAutoMoveTime(WINDOW *winSettings, int *secAutoMove){
	int inputKey, seconds;
	seconds = *secAutoMove;
	if(seconds > 10)
		seconds = 0;
	printAutoMoveSett(winSettings, seconds);
	while(1){
		inputKey = wgetch(winSettings);
		inputKey = tolower(inputKey);
		if(inputKey == 10){

			break;
		}
		switch(inputKey){
			case KEY_LEFT:
				if(seconds != 0)
					seconds--;
				else
					seconds = 10;
				printAutoMoveSett(winSettings, seconds);
				break;
			case KEY_RIGHT:
				if(seconds != 10)
					seconds++;
				else
					seconds = 0;
				printAutoMoveSett(winSettings, seconds);
				break;
		}
	}
	if(seconds == 0)
		seconds = 1 << 30;
	*secAutoMove = seconds;
}

//Print submenu Game mode option
void printModeGameSett(WINDOW *winSettings, int gameMode){
	char *gameMode_list[] = {"CLASSIC", "REVERSE", "LOGARITHMIC", "ALPHABET", "FIBONACCI"};
	int maxLines, maxCols;
	getmaxyx(winSettings, maxLines, maxCols);
	int y = maxLines / 3 + 2, x = maxCols / 2;
	move(y, x);
	char toPrint[30] = "<<- ";
	strcat(toPrint, gameMode_list[gameMode]);
	strcat(toPrint, " ->>");
	wattron(winSettings, COLOR_PAIR(21) | A_BOLD);
	mvwprintw(winSettings, y, x, "%s", toPrint);
	wattroff(winSettings, COLOR_PAIR(21) | A_BOLD);
	wclrtoeol(winSettings);
	wrefresh(winSettings);
}

//Menu for choosing gamemode
void setMode(WINDOW *winSettings, int *mode){
	int inputKey, gameMode;
	gameMode = *mode;
	printModeGameSett(winSettings, gameMode);
	while(1){
		inputKey = wgetch(winSettings);
		inputKey = tolower(inputKey);
		if(inputKey == 10){

			break;
		}
		switch(inputKey){
			case KEY_LEFT:
				if(gameMode != 0)
					gameMode--;
				else
					gameMode = 4;
				printModeGameSett(winSettings, gameMode);
				break;
			case KEY_RIGHT:
				if(gameMode != 4)
					gameMode++;
				else
					gameMode = 0;
					printModeGameSett(winSettings, gameMode);
				break;
		}
	}
	*mode = gameMode;
}

//Print submenu Obstacles
void printObstaclesSett(WINDOW *winSettings, int Obstacles){
	int maxLines, maxCols;
	getmaxyx(winSettings, maxLines, maxCols);
	int y = maxLines / 3 + 4, x = maxCols / 2;
	move(y, x);
	char toPrint[30] = "<<- ", aux[3];
	if (Obstacles == 0)
		strcat(toPrint, "NONE ->>");
	else{
		sprintf(aux, "%d", Obstacles);
		strcat(toPrint, aux);
		strcat(toPrint, " ->>");
	}
	wattron(winSettings, COLOR_PAIR(21) | A_BOLD);
	mvwprintw(winSettings, y, x, "%s", toPrint);
	wattroff(winSettings, COLOR_PAIR(21) | A_BOLD);
	wclrtoeol(winSettings);
	wrefresh(winSettings);
}

//Set number of obstacles
void setObstacles(WINDOW *winSettings, int *Obstacles){
	int inputKey, n_obstacles;
	n_obstacles = *Obstacles;
	printObstaclesSett(winSettings, n_obstacles);
	while(1){
		inputKey = wgetch(winSettings);
		inputKey = tolower(inputKey);
		if(inputKey == 10)
			break;
		switch(inputKey){
			case KEY_LEFT:
				if(n_obstacles != 0)
					n_obstacles--;
				else
					n_obstacles = 3;
				printObstaclesSett(winSettings, n_obstacles);
				break;
			case KEY_RIGHT:
				if(n_obstacles != 3)
					n_obstacles++;
				else
					n_obstacles = 0;
					printObstaclesSett(winSettings, n_obstacles);
				break;
		}
	}
	*Obstacles = n_obstacles;
}

//Main function for Game Settings
void managerSettings(WINDOW *winSettings, int *secAutoMove, int *mode, int *Obstacles){
	wbkgd(winSettings, COLOR_PAIR(20));
	wrefresh(winSettings);
	char *optSettings[] = {	"Timer AutoMove", "Mode", "Obstacles", "Back" };
	int n_optSettings = sizeof(optSettings) / sizeof(optSettings[0]);
	int choiceSettings = -1;
	while(1){
		choiceSettings = createSettings(winSettings, n_optSettings, optSettings);
		if(strcmp(optSettings[choiceSettings],"Back") == 0){
			wclear(winSettings);
			wrefresh(winSettings);
			return;
		}
		else if(strcmp(optSettings[choiceSettings],"Timer AutoMove") == 0){
			setAutoMoveTime(winSettings, secAutoMove);
		}
		else if(strcmp(optSettings[choiceSettings],"Mode") == 0){
			setMode(winSettings, mode);
		}
		else if(strcmp(optSettings[choiceSettings],"Obstacles") == 0){
			setObstacles(winSettings, Obstacles);
		}
	}
}