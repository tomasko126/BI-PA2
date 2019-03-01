//
//  Tower.hpp
//  
//
//  Created by Tomáš Taro on 05/05/2018.
//

#ifndef Tower_hpp
#define Tower_hpp

#include "StoredTower.hpp"
#include "Cell.hpp"
#include "Road.hpp"

/**
 * Tower class, which represents tower in map
 */
class Tower : public Road {
public:
    /**
     * Tower constructor
     *
     * @param towerType - char of tower to be shown in the map
     * @param X - X-coordination in the map
     * @param Y - Y-coordination in the map
     */
	Tower(const char towerType, const unsigned int X, const unsigned int Y);
	
    /**
     * Store tower in the current cell
     *
     * @param newTower - weak pointer to the shared pointer in the towers vector
     */
	void storeTower(const weak_ptr<StoredTower> & newTower);
    
    /**
     * Return stored tower in the current cell
     *
     * @return weak_ptr<StoredTower> - reference to the weak pointer stored in the current cell
     */
	weak_ptr<StoredTower> & getStoredTower();
		
private:
	weak_ptr<StoredTower> tower;
};

#endif /* Tower_hpp */
