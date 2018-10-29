#include "functions.h"

int startApp(WINDOW *winMenu, int n_optMenu, char *optMenu[]){
	int choice;
	//Create menu and return option
	choice = createMenu(winMenu, n_optMenu, optMenu);
	if(strcmp(optMenu[choice],"New Game") == 0)
		return 0;
	else if(strcmp(optMenu[choice],"Resume") == 0)
		return 1;
	else if(strcmp(optMenu[choice],"Quit") == 0)
		return 2;
	else if(strcmp(optMenu[choice],"Settings") == 0)
		return 3;
	else if(strcmp(optMenu[choice],"Leaderbord") == 0)
		return 4;
	return 2;
}

//Initialize colors for game
void initColors(){
	//For values in board
	init_color(COLOR_BLACK, 0, 0, 0);
	init_color(COLOR_GREEN, 0, 255, 0);
	init_color(COLOR_RED, 255, 0, 0);
	init_pair(1, COLOR_WHITE, COLOR_CYAN);
	init_pair(2, COLOR_WHITE, COLOR_RED);
	init_pair(3, COLOR_WHITE, COLOR_GREEN);
	init_pair(4, COLOR_WHITE, COLOR_YELLOW);
	init_pair(5, COLOR_WHITE, COLOR_BLUE);
	init_pair(6, COLOR_WHITE, COLOR_MAGENTA);
	init_pair(7, COLOR_WHITE, COLOR_CYAN);
	init_pair(8, COLOR_WHITE, COLOR_RED);
	init_pair(9, COLOR_WHITE, COLOR_GREEN);
	init_pair(10, COLOR_WHITE, COLOR_YELLOW);
	//Menu
	init_pair(20, COLOR_YELLOW, COLOR_BLACK);
	//Settings
	init_pair(21, COLOR_GREEN, COLOR_BLACK);
	//Obstacles
	init_pair(22, COLOR_YELLOW, COLOR_YELLOW);
	//Leaderdbord
	init_pair(23, COLOR_RED, COLOR_BLACK);
	//Nickname
	init_pair(24, COLOR_BLUE, COLOR_BLACK);
	//Borders
	init_pair(25, COLOR_WHITE, COLOR_BLACK);
	init_pair(30, COLOR_WHITE, COLOR_WHITE);
	//Infos, Time and Score
	init_pair(31, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(32, COLOR_WHITE, COLOR_BLACK);
}

//Create file leaderbord.txt if it doesn't exist
void createFile_Leaderdbord(){
	FILE *file = fopen("leaderbord.txt", "r");
	if(!file){
		file = fopen("leaderbord.txt", "a");
		fclose(file);
	}
}

int main(){
	
	//Init game variables and curses options 
	WINDOW *winMenu, *winGame, *winSettings, *winLeaderbord;
	PANEL *panGame;
	char *optMenu[] = {	"New Game", "Resume", "Leaderbord", "Settings", "Quit" };
	int n_optMenu = sizeof(optMenu) / sizeof(optMenu[0]);
	int board[4][4], score = 0, secAutoMove = 3, mode = 0, Obstacles = 0;
	int gameState, reset = 1;
	
	initscr();
	clear();
	noecho();
	cbreak();
	curs_set(0);
	keypad(stdscr, TRUE);
	start_color();
	initColors();
	resetBoard(board, &score);
	createFile_Leaderdbord();

	//Init windows and panels for game
	winMenu = newwin(LINES, COLS, 0, 0);
	winSettings = newwin(LINES, COLS, 0, 0);
	winLeaderbord = newwin(LINES, COLS, 0, 0);
	winGame = newwin(LINES, COLS, 0, 0);
	panGame = new_panel(winGame);
	hide_panel(panGame);
	update_panels();
	doupdate();
	
	//Waits for Quit options
	while(1){
		gameState = startApp(winMenu, n_optMenu, optMenu);
		//New Game or Resume 
		if(gameState == 1 || gameState == 0){
			if(gameState == 1 && reset == 1)
				continue;
			else if(gameState == 0){
				//Board reset for new game
				resetBoard(board, &score);
				reset = 1;
			}
			delwin(winMenu);
			show_panel(panGame);
			update_panels();
			doupdate();
			playGame(board, winGame, &score, &reset, secAutoMove, mode, Obstacles);
			hide_panel(panGame);
			update_panels();
			doupdate();
		}
		else if(gameState == 3){
			delwin(winMenu);
			int prevMode = mode, prevObstacles = Obstacles;
			managerSettings(winSettings, &secAutoMove, &mode, &Obstacles);
			if(prevMode != mode || prevObstacles != Obstacles){
				resetBoard(board, &score);
				reset = 1;
			}
		}
		else if(gameState == 4){
			delwin(winMenu);
			managerLeaderbord(winLeaderbord);
		}
		else
			break;
	}
	
	refresh();
	endwin();
	return 0;
}