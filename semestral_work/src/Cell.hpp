//
//  Cell.hpp
//  
//
//  Created by Tomáš Taro on 05/05/2018.
//

#ifndef Cell_hpp
#define Cell_hpp

#include "StoredTower.hpp"
#include "Soldier.hpp"

#include <vector>
#include <memory>

using namespace std;

/**
 * Cell class, which represents one cell in game map
 */
class Cell {
public:

    /**
     * Cell constructor
     *
     * @param X X-coordination in the map
     * @param Y Y-coordination in the map
     *
     */
	Cell(const unsigned int X, const unsigned int Y);
    
    /**
     * Cell constructor
     *
     * @param X X-coordination in the map
     * @param Y Y-coordination in the map
     * @param type type of the cell - # as Wall, ' ' as Road
     *
     */
	Cell(const char type, const unsigned int X, const unsigned int Y);
    
    /**
     * Cell virtual destructor
     */
	virtual ~Cell();
	
    /**
     * Get cell type
     *
     * @return char - cell type
     */
	char getChar() const;
    
    /**
     * Set cell type
     *
     * @param char - sets type of cell
     */
	void setChar(const char newChar);
	
    /**
     * Get X coordinate of the cell
     *
     * @return unsigned int - X coordinate
     */
	unsigned int getX() const;
    
    /**
     * Get Y coordinate of the cell
     *
     * @return unsigned int - Y coordinate
     */
	unsigned int getY() const;
	
    /**
     * Store tower, which has range onto this cell
     *
     * @param weak_ptr<StoredTower> - weak pointer to that tower
     */
	void addTowerInRange(const weak_ptr<StoredTower> & towerPointer);
	
    /**
     * Get all towers, which have range onto this cell
     *
     * @return vector<weak_ptr<StoredTower>> - vector of weak pointers to towers, which have range to this cell
     */
	vector<weak_ptr<StoredTower>> & getTowersInRange();
	
    /**
     * Get BFS status of this cell
     *
     * @return int - -1/0/1 states
     */
	int getStatus() const;
    
    /**
     * Set BFS status of this cell
     *
     * @param int - -1/0/1 states
     */
	void setStatus(const int newStatus);
	
    /**
     * Get BFS predecessor of this cell
     *
     * @return Cell * - cell pointer to the predecessor of this cell
     */
	Cell * getBefore() const;
    
    /**
     * Set BFS predecessor of this cell
     *
     * @param Cell ** - cell pointer to the predecessor of this cell
     */
	void setBefore(Cell ** before);
			
protected:
	// Coordinates
	unsigned int X = 0, Y = 0;
	
	// Type of tower
	char type = '\0';
	
	// BFS
	Cell * before = nullptr;
	int status = -1;
	
	// Towers in range
	vector<weak_ptr<StoredTower>> towersInRange;
};

#endif /* Cell_hpp */
