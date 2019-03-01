//
//  Tower.cpp
//  
//
//  Created by Tomáš Taro on 05/05/2018.
//

#include "Tower.hpp"

using namespace std;

Tower::Tower(const char towerType, const unsigned int X, const unsigned int Y) : Road(towerType, X, Y) {}

void Tower::storeTower(const weak_ptr<StoredTower> & newTower) {
	tower = newTower;
}

weak_ptr<StoredTower> & Tower::getStoredTower() {
	return tower;
}
