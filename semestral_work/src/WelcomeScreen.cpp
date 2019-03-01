//
//  WelcomeScreen.cpp
//  TowerDefense
//
//  Created by Tomáš Taro on 05/05/2018.
//  Copyright © 2018 Tomáš Taro. All rights reserved.
//

#include "WelcomeScreen.hpp"

unsigned int WelcomeScreen::showScreen() {
	noecho();
	curs_set(FALSE);
	
	string welcomeMessage = "Tower Defense game by Tomáš Taro";
	string introMessage = "Written in C++";
	
	mvwprintw(window, getmaxy(window) / 2 - 2, (getmaxx(window) - welcomeMessage.size()) / 2, welcomeMessage.c_str());
	
	mvwprintw(window, getmaxy(window) / 2, (getmaxx(window) - introMessage.size()) / 2, introMessage.c_str());
	
	wrefresh(window);
	
    wgetch(window);
	
	wclear(window);
	
	return 0;
};
