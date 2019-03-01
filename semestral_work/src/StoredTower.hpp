//
//  StoredTower.hpp
//  
//
//  Created by Tomáš Taro on 05/05/2018.
//

#ifndef StoredTower_hpp
#define StoredTower_hpp

#include <vector>

using namespace std;

/*
 * StoredTower class represents stored tower in the game
 */
class StoredTower {
public:
    /**
     * StoredTower empty constructor
     */
	StoredTower();
    
    /**
     * StoredTower constructor
     *
     * @param health - health of the tower to be added
     * @param cost - cost of the tower to be added
     * @param range - range of the tower to be added
     * @param attack - attack power of the tower to be added
     * @param character - char of the tower to be added
     */
	StoredTower(const int health, const unsigned int cost, const unsigned int range, const unsigned int attack, const char character);
	
    /**
     * Get char of the tower
     *
     * @return const char - char of the tower, which is shown in the map
     */
	const char getCharacter() const;
    
    /**
     * Get current health of the tower
     *
     * @return const int - current health of the tower
     */
	const int getHealth() const;
    
    /**
     * Get cost of the tower
     *
     * @return const unsigned int - how much the current tower costs
     */
	const unsigned int getCost() const;
    
    /**
     * Get range of the current tower
     *
     * @return const unsigned int - range of the current tower
     */
	const unsigned int getRange() const;
    
    /**
     * Get attack power of the current tower
     *
     * @return const unsigned int - attack power of the current tower
     */
	const unsigned int getAttack() const;
    
    /**
     * Set attack power of the current tower
     *
     * @param const unsigned int - new attack power of the current tower
     */
	void setAttack(const unsigned int newAttack);
	
    /**
     * Get tower's coordinates
     *
     * @return pair of unsigned ints - X/Y coordinates of the current tower
     */
	pair<unsigned int, unsigned int> getTowerCoordinates() const;
    
    /**
     * Set tower's coordinates
     *
     * @param X - X coordinate of the tower
     * @param Y - Y coordinate of the tower
     */
	void setTowerCoordinates(const unsigned int X, const unsigned int Y);
	
    /**
     * Find out, whether the tower is alive or not
     *
     * @return bool - true if the tower is alive, false otherwise
     */
	bool isAlive() const;
    
    /**
     * Find out, whether the tower is alive or not
     *
     * @param minusHealth - how much tower's hp should be lowered
     *
     * @return bool - true if the tower is alive, false otherwise
     */
	bool lowerHealth(const unsigned int minusHealth);
	
protected:
	char character = '\0';
	
	int health = 0;
	unsigned int cost = 0;
	unsigned int range = 0;
	unsigned int attack = 0;
	unsigned int X = 0;
	unsigned int Y = 0;
};
#endif /* StoredTower_hpp */
