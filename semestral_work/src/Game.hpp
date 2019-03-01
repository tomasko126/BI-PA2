//
//  Game.hpp
//  TowerDefense
//
//  Created by Tomáš Taro on 05/05/2018.
//  Copyright © 2018 Tomáš Taro. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include "Map.hpp"
#include "StoredTower.hpp"
#include "Road.hpp"
#include "Wall.hpp"
#include "Tower.hpp"
#include "Soldier.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <memory>
#include <vector>
#include <set>
#include <list>

/**
 * Game class, which is responsible for loading/saving/creating game and overall gameplay
 */
class Game {
public:
    
    /**
     * Game constructor
     */
	Game();
	
    /**
     * Start new game
     */
	unsigned int startNewGame();
    
    /**
     * Load saved game
     */
	unsigned int loadSavedGame();
    
    /**
     * Save current game
     */
	unsigned int saveGame();
    
    /**
     * Destroy current game's data
     */
	void destroyGame();
    
    /**
     * Get current round number
     *
     * @return unsigned int - current round number
     */
    unsigned int getRound() const;
    
    /**
     * Get available money
     *
     * @return unsigned int - current money available
     */
    unsigned int getMoneyAvailable() const;

	void prepareRound();
    
    /**
     * Find path for soldiers using BFS
     */
    void findPath();
    
    /**
     * Move soldiers one by one
     */
	unsigned int moveSoldiers();
    
    /**
     * Reset BFS status of each cell
     */
	void cleanUpMap();

    /**
     * Place new tower onto map
     *
     * @param X X-coordination in the map
     * @param Y Y-coordination in the map
     * @param towerName name of the tower being added
     *
     * @return unsigned int - which determines the success
     */
	unsigned int placeNewTower(const char towerName, const unsigned int X, const unsigned int Y);
	
	Map mapa;
	
    map<char, StoredTower> defaultTowers;
    
private:
    vector<Soldier> defaultSoldiers;
    
    vector<Soldier> soldiers;
    vector<shared_ptr<StoredTower>> towers;
    
    unsigned int round = 0;
    unsigned int moneyAvailable = 500;
    
    unsigned int noOfEachSoldierOnMap = 2;
    unsigned int noOfLiveSoldiers = 0;
    unsigned int noOfLiveTowers = 0;
};

#endif /* Game_hpp */
