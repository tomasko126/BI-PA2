//
//  NewGameScreen.hpp
//  TowerDefense
//
//  Created by Tomáš Taro on 08/05/2018.
//  Copyright © 2018 Tomáš Taro. All rights reserved.
//

#ifndef NewGameScreen_hpp
#define NewGameScreen_hpp

#include "Screen.hpp"
#include "Game.hpp"

#include <unistd.h>
/*
 * NewGameScreen class, responsible for showing up New Game screen
 */
class NewGameScreen : public Screen {
public:
    /**
     * Constructor, which initializes the screen
     */
	NewGameScreen();
	
	virtual unsigned int showScreen() override;
    
    /**
     * Display current round and money available
     */
    void showGameInfo() const;
    
    /**
     * Draw current map
     *
     * @return unsigned int - max Y coordinate of the map on the screen
     */
	unsigned int drawMap() const;
    
    /**
     * Draw tower types available to place into the map
     *
     * @param height - Y coordinate, from where we should begin showing up the tower types
     *
     * @return unsigned int - Y coordinate of the last drawn tower type
     */
	unsigned int drawTowerTypes(const unsigned int height) const;
    
    /**
     * Display command box, which lets user to type in commands
     *
     * @param height - Y coordinate, from which we should start begin drawing the command box
     *
     * @return unsigned int - 0, when the game has ended
     */
	unsigned int displayAndProcessInput(const unsigned int height);
    
    /**
     * Execute user's input
     *
     * @param input - user's input
     *
     * @return unsigned int - 0, when game shall continue, otherwise returns 1
     */
	unsigned int executeInput(const string input);
	
protected:
	Game game;
};

#endif /* NewGameScreen_hpp */
