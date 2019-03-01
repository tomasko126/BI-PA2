//
//  Map.hpp
//  
//
//  Created by Tomáš Taro on 05/05/2018.
//

#ifndef Map_hpp
#define Map_hpp

#include "Cell.hpp"
#include "Tower.hpp"
#include "Road.hpp"
#include "Wall.hpp"

#include <list>
#include <map>

using namespace std;

/*
 * Map class represents game map
 */
class Map {
public:
    /**
     * Map empty constructor
     */
	Map();
    
    /**
     * Map constructor
     *
     * @param X - max X-coordination in the map
     * @param Y - max Y-coordination in the map
     */
	Map(const unsigned int X, const unsigned int Y);
    
    /**
     * Map destructor
     */
	~Map();

    /**
    * Set start coordinates, where soldiers will be coming from
    *
    * @param X - X-coordination in the map
    * @param Y - Y-coordination in the map
    */
	void setStart(const unsigned int X, const unsigned int Y);
	
    /**
     * Set end coordinates, whose soldiers should reach
     *
     * @param X - X-coordination in the map
     * @param Y - Y-coordination in the map
     */
	void setEnd(const unsigned int X, const unsigned int Y);
	
    /**
     * Find path from start coordinates to the end coordinates for soldiers
     */
	void findPath();
    
    /**
    * Find out, whether we can place a new tower to X/Y coordinates
    *
    * @param X - X-coordination in the map
    * @param Y - Y-coordination in the map
    *
    * @return boolean - true, if we can place a new tower into the cell, false otherwise
    */
    bool canPlaceTower(const unsigned int X, const unsigned int Y) const;
	
    /**
     * Place new tower into the desired cell
     *
     * @param towerToAdd - weak ptr to the tower we are going to add
     * @param towerName - name of the tower shown in the map
     * @param X - X-coordination in the map
     * @param Y - Y-coordination in the map
     *
     * @return unsigned int - always 0
     */
	unsigned int placeNewTower(const weak_ptr<StoredTower> & towerToAdd, const char towerName, const unsigned int X, const unsigned int Y);
	
    /**
     * Place weak pointer to all cells, where the tower has got range
     *
     * @param towerPointer - weak ptr to the tower we are going to add
     * @param X - X-coordination in the map
     * @param Y - Y-coordination in the map
     * @param currentTowerRange - range of the tower
     */
	void placeTowerInRange(const weak_ptr<StoredTower> & towerPointer, const unsigned int X, const unsigned int Y, const unsigned int currentTowerRange);
	
	vector<vector<Cell*>> map;
	vector<Cell*> cesta;
	
private:
	unsigned int width = 0;
	unsigned int heigth = 0;
	unsigned int startX = 0, startY = 0, endX = 0, endY = 0;
};

#endif /* Map_hpp */
