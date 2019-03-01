//
//  main.cpp
//  TowerDefense
//
//  Created by Tomáš Taro on 05/05/2018.
//  Copyright © 2018 Tomáš Taro. All rights reserved.
//

#include <ncurses.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "WelcomeScreen.hpp"
#include "MainScreen.hpp"
#include "NewGameScreen.hpp"
#include "LoadGameScreen.hpp"

#define DELAY 35000
using namespace std;

int main() {
	
	initscr();
	    
    start_color();
    init_pair(3,COLOR_BLUE,COLOR_WHITE);
	
	WelcomeScreen welcomeScreen;
	
	welcomeScreen.showScreen();
	
	MainScreen mainScreen;
	
	while (true) {
		unsigned int chosenOption = mainScreen.showScreen();
        
        if (chosenOption == 0) {
            NewGameScreen newGameScreen;
            newGameScreen.showScreen();
        } else if (chosenOption == 1) {
            LoadGameScreen loadGameScreen;
            loadGameScreen.showScreen();
        } else {
			// Exit has been chosen
			endwin();
			break;
		}
	}
	
	return 0;
}
