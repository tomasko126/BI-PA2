//
//  Road.hpp
//  TowerDefense
//
//  Created by Tomáš Taro on 18/05/2018.
//  Copyright © 2018 Tomáš Taro. All rights reserved.
//

#ifndef Road_hpp
#define Road_hpp

#include "Cell.hpp"
#include "Soldier.hpp"

/*
 * Road class represents road in the map
 */
class Road : public Cell {
public:
    /**
     * Road constructor
     *
     * @param X X-coordination in the map
     * @param Y Y-coordination in the map
     *
     */
	Road(const unsigned int X, const unsigned int Y);
    
    Road(const char character, const unsigned int X, const unsigned int Y);
	
    /**
     * Add soldier to the current cell
     *
     * @param newSoldier - soldier, which should be placed into this cell
     */
	void addSoldier(const Soldier & newSoldier);
    
    /**
     * Return soldier in the current cell
     *
     * @return Soldier - soldier placed in the current cell
     */
	Soldier & getSoldier();
    
    /**
     * Remove soldier from the current cell
     */
	void removeSoldier();
    
    /**
     * Attack soldier
     *
     * @param tower - pointer to the tower, which attacks the soldier
     *
     * @return pair of bools - 1. is soldier alive?; 2. is tower alive?
     */
	pair<bool, bool> attackSoldier(StoredTower * tower);
	
private:
	Soldier soldier;
};

#endif /* Road_hpp */
