//
//  Soldier.hpp
//  TowerDefense
//
//  Created by Tomáš Taro on 10/05/2018.
//  Copyright © 2018 Tomáš Taro. All rights reserved.
//

#ifndef Soldier_hpp
#define Soldier_hpp

#include "StoredTower.hpp"
#include "Cell.hpp"

#include <vector>

using namespace std;

/*
 * Soldier class, which represents one soldier in the map
 */
class Soldier {
public:
    /**
     * Soldier constructor
     */
	Soldier();
    
    /**
     * Soldier constructor
     *
     * @param hp - hp of the soldier to be created
     * @param character - char of the soldier to be shown on the map
     * @param attackPower - how much hp the soldier can lower one tower
     */
	Soldier(const int hp, const char character, const unsigned int attackPower);
	
    /**
     * Get current hp of the soldier
     *
     * @return const int - hp of the soldier
     */
    const int getHp() const;
    
    /**
     * Get current char of the soldier
     *
     * @return const char - char of the soldier
     */
    const char getCharacter() const;
    
    /**
     * Get current attack power of the soldier
     *
     * @return const unsigned int - attack power of the soldier
     */
    const unsigned int getAttack() const;
    
    /**
     * Find out, whether the soldier is alive or not
     *
     * @return const bool - true if alive, false otherwise
     */
    const bool isAlive() const;
	
    /**
     * Make soldier to die
     */
    void die();
    
    /**
     * Lower soldier's health
     *
     * @param minusHealth - how much soldier's HP should be lowered
     */
	void lowerHealth(const int minusHealth);
	
private:
	int hp = 0;
	char character = '\0';
	unsigned int attackPower = 0;
};

#endif /* Soldier_hpp */
