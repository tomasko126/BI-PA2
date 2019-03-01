//
//  StoredTower.cpp
//  
//
//  Created by Tomáš Taro on 05/05/2018.
//

#include "StoredTower.hpp"

StoredTower::StoredTower() = default;

StoredTower::StoredTower(const int health, const unsigned int cost, const unsigned int range, const unsigned int attack, const char character) : character(character), health(health), cost(cost), range(range), attack(attack) {}

bool StoredTower::lowerHealth(const unsigned int minusHealth) {
	health -= minusHealth;
	
	if (isAlive()) {
		return false;
	}
	
	return true;
}

const char StoredTower::getCharacter() const {
	return character;
}

const int StoredTower::getHealth() const {
	return health;
}

const unsigned int StoredTower::getCost() const {
	return cost;
}

const unsigned int StoredTower::getAttack() const {
	return attack;
}

const unsigned int StoredTower::getRange() const {
	return range;
}

void StoredTower::setAttack(const unsigned int newAttack) {
	attack = newAttack;
}

pair<unsigned int, unsigned int> StoredTower::getTowerCoordinates() const {
	return make_pair(this->X, this->Y);
}

void StoredTower::setTowerCoordinates(const unsigned int newX, const unsigned int newY) {
	X = newX;
	Y = newY;
}

bool StoredTower::isAlive() const {
	return health > 0;
}
