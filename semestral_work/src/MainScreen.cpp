//
//  MainScreen.cpp
//  TowerDefense
//
//  Created by Tomáš Taro on 05/05/2018.
//  Copyright © 2018 Tomáš Taro. All rights reserved.
//

#include "MainScreen.hpp"
#include "NewGameScreen.hpp"
#include "LoadGameScreen.hpp"

void MainScreen::showMenu(const unsigned int chosenOption) const {
    int height = -2;
    
    wattroff(window, COLOR_PAIR(3));
    
    for (unsigned int i = 0; i<messages.size(); i++) {
        if (i == chosenOption) {
            wattron(window, COLOR_PAIR(3));
        }
        mvwaddstr(window, getmaxy(window) / 2 + height, (getmaxx(window) - messages[i].size()) / 2, messages[i].c_str());
        height += 2;
        if (i == chosenOption) {
            wattroff(window, COLOR_PAIR(3));
        }
    }
    
    wrefresh(window);
}

unsigned int MainScreen::showScreen() {
    
    clear();
    noecho();
    cbreak();
    keypad(window, TRUE);
    
    showMenu();
    
    unsigned int chosenOption = 0;
    
    while (true) {
        
        int ch = wgetch(window);
        
        switch (ch) {
            case KEY_UP: {
                chosenOption--;
                
                if (chosenOption == -1) {
                    chosenOption = 2;
                }
                
                break;
            }
            case KEY_DOWN: {
                chosenOption++;
                
                if (chosenOption == 3) {
                    chosenOption = 0;
                }
                
                break;
            }
            case 10: {
                switch (chosenOption) {
                    case 0: {                        
                        return 0;
                    }
                    case 1: {
                        return 1;
                    }
                    case 2: {
                        return 2;
                    }
                }
                break;
            }
        }
        
        showMenu(chosenOption);
    }
}

