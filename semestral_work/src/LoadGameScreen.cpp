//
//  LoadGameScreen.cpp
//  TowerDefense
//
//  Created by Tomáš Taro on 30/05/2018.
//  Copyright © 2018 Tomáš Taro. All rights reserved.
//

#include "LoadGameScreen.hpp"

LoadGameScreen::LoadGameScreen() : NewGameScreen() {}

unsigned int LoadGameScreen::showScreen() {
	// Load saved game
    unsigned int result = game.loadSavedGame();
    
    if (result == 1) {
        showFailedIOMessage(1);
        wgetch(window);
        return 0;
    }
    
    // Show useful game info
    showGameInfo();
	
	// Draw map
	unsigned int mapHeight = drawMap();
    
    // Draw available towers
	unsigned int towersHeight = drawTowerTypes(mapHeight);
	
    // Draw input and get commands from user
	displayAndProcessInput(towersHeight);
    
    wclear(window);
    wrefresh(window);
	
	return 0;
}
