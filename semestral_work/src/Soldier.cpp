//
//  Soldier.cpp
//  TowerDefense
//
//  Created by Tomáš Taro on 10/05/2018.
//  Copyright © 2018 Tomáš Taro. All rights reserved.
//

#include "Soldier.hpp"

Soldier::Soldier() = default;

Soldier::Soldier(const int hp, const char character, const unsigned int attackPower) : hp(hp), character(character), attackPower(attackPower) {};

const int Soldier::getHp() const {
	return hp;
}

const unsigned int Soldier::getAttack() const {
	return attackPower;
}

const char Soldier::getCharacter() const {
	return character;
}

const bool Soldier::isAlive() const {
	if (hp != 0 && character != '\0') {
		return true;
	}
	return false;
}

void Soldier::die() {
	character = '\0';
	hp = 0;
	attackPower = 0;
}

void Soldier::lowerHealth(const int lowerHealth) {
	hp -= lowerHealth;
	
	if (hp < 0) {
		die();
	}
}
