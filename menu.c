#include "functions.h"

//Print text "2048" (Ascii Art)
void print2048Text(){
	int yPos = LINES / 16, xPos = (COLS - 26) / 2;
	attron(COLOR_PAIR(20) | A_BOLD | A_BLINK);
	mvprintw(yPos++, xPos," ____   ___  _  _    ___");  
	mvprintw(yPos++, xPos,"|___ \\ / _ \\| || |  ( _ )"); 
	mvprintw(yPos++, xPos,"  __) | | | | || |_ / _ \\ ");
	mvprintw(yPos++, xPos," / __/| |_| |__   _| (_) |");
	mvprintw(yPos++, xPos,"|_____|\\___/   |_|  \\___/");
	attroff(COLOR_PAIR(20) | A_BOLD | A_BLINK);
	refresh();
}



//Create menu
int createMenu(WINDOW *winMenu, int n_optMenu, char *optMenu[]){
	int maxROW, maxCOL;
	getmaxyx(stdscr, maxROW, maxCOL);
	int startX = (maxCOL - width) / 2;
	int startY = (maxROW - height) / 2 + 5;
	winMenu = newwin(height, width, startY, startX);
	keypad(winMenu, TRUE);
	int current = 0, choice = -1, inputKey;
	showMenu(winMenu, current, n_optMenu, optMenu);

	print2048Text();
	//Navigate through menu with KEY_UP and KEY_DOWN
	//Waits for ENTER to exit 
	while(1){
		inputKey = wgetch(winMenu);
		switch(inputKey){
			case KEY_UP:
				if(current == 0)
					current = n_optMenu - 1;
				else
					current--;
				break;
			case KEY_DOWN:
				if(current == n_optMenu - 1)
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
		showMenu(winMenu, current, n_optMenu, optMenu);
		if(choice != -1)
			break;
	}
	return choice;
}

//Print menu at each call from createMenu
void showMenu(WINDOW *winMenu, int current, int n_optMenu, char *optMenu[]){
	wbkgd(winMenu, COLOR_PAIR(20));
	int index;
	int y = height / 16, x;
	for(index = 0; index < n_optMenu; index++){
		y = y + 2;
		x = (width - strlen(optMenu[index])) / 2; 
		if(current == index){
			wattron(winMenu, A_BOLD);
			mvwprintw(winMenu, y, x, "%s", optMenu[index]);
			wattroff(winMenu, A_BOLD);
		}
		else
			mvwprintw(winMenu, y, x, "%s", optMenu[index]);
	}
	wrefresh(winMenu);
}

