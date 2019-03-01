//
//  MainScreen.hpp
//  TowerDefense
//
//  Created by Tomáš Taro on 05/05/2018.
//  Copyright © 2018 Tomáš Taro. All rights reserved.
//

#ifndef MainScreen_hpp
#define MainScreen_hpp

#include "Screen.hpp"

#include <unistd.h>
#include <iostream>
#include <vector>

using namespace std;

/**
 * MainScreen class responsible for showing up main game menu
 */
class MainScreen : public Screen {
public:
	MainScreen() : Screen() {}
    
    virtual unsigned int showScreen() override;
    
    /**
     * Display menu with options
     *
     * @param chosenOption - which option shall be highlighted
     */
    void showMenu(const unsigned int chosenOption = 0) const;
private:
    vector<string> messages = {"New Game", "Load Game", "Exit"};
};

#endif /* MainScreen_hpp */
