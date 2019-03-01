//
//  Screen.cpp
//  TowerDefense
//
//  Created by Tomáš Taro on 05/05/2018.
//  Copyright © 2018 Tomáš Taro. All rights reserved.
//

#include "Screen.hpp"

using namespace std;

Screen::Screen() : window(newwin(getmaxy(stdscr), getmaxx(stdscr), 0, 0)) {
	maxX = getmaxy(stdscr);
	maxY = getmaxx(stdscr);
}

Screen::~Screen() {
	delwin(window);
};

void Screen::showFailedIOMessage(const unsigned int idxOfMessage) const {
    string failMessage;
    if (idxOfMessage == 1) {
        failMessage = "Loading of the game file has failed!";
    } else if (idxOfMessage == 0) {
        failMessage = "Game save has failed!";
    }
    mvwaddstr(window, 0, (getmaxx(window) - failMessage.size()) / 2, failMessage.c_str());
    
    wrefresh(window);
    wmove(window, 0, 0);
    wclrtoeol(window);
}
