//
//  Road.cpp
//  TowerDefense
//
//  Created by Tomáš Taro on 18/05/2018.
//  Copyright © 2018 Tomáš Taro. All rights reserved.
//

#include "Road.hpp"

Road::Road(const unsigned int X, const unsigned int Y) : Cell(' ', X, Y) {}

Road::Road(const char character, const unsigned int X, const unsigned int Y) : Cell(character, X, Y) {}

void Road::addSoldier(const Soldier & newSoldier) {
	soldier = newSoldier;
}

Soldier & Road::getSoldier() {
	return soldier;
}

void Road::removeSoldier() {
	soldier.die();
}

pair<bool, bool> Road::attackSoldier(StoredTower * tower) {
	// Tower attacks soldier
	if (tower->isAlive()) {
		soldier.lowerHealth(tower->getAttack());
		
		// Soldier attacks tower
		if (soldier.isAlive()) {
			tower->lowerHealth(soldier.getAttack());
		}
		
		return make_pair(soldier.isAlive(), tower->isAlive());
	}
	
	return make_pair(true, true);
}
