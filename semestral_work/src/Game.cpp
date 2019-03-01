//
//  Game.cpp
//  TowerDefense
//
//  Created by Tomáš Taro on 05/05/2018.
//  Copyright © 2018 Tomáš Taro. All rights reserved.
//

#include "Game.hpp"

#include <queue>

using namespace std;

Game::Game() {
	mapa = Map(0,0);
}

unsigned int Game::startNewGame() {
	
	// Load template file
	ifstream newGameTemplate;
	newGameTemplate.open("src/data/template_new.txt", ios::in);
	
	if (!newGameTemplate.is_open()) {
		return 1;
	}
    
    if (newGameTemplate.fail()) {
        return 1;
    }
	
	unsigned int noOfTowers = 0;
	
	newGameTemplate >> noOfTowers;
    
    if (newGameTemplate.fail()) {
        return 1;
    }
	
	for (unsigned int i = 0; i<noOfTowers; i++) {
		char towerName;
		unsigned int health, cost, range, attack;
		
		newGameTemplate >> towerName >> health >> cost >> range >> attack;
        
        if (newGameTemplate.fail()) {
            return 1;
        }
		
		StoredTower newTower(health, cost, range, attack, towerName);
		defaultTowers[towerName] = newTower;
	}
	
	
	unsigned int noOfWarriors = 0;
	
	newGameTemplate >> noOfWarriors;
    
    if (newGameTemplate.fail()) {
        return 1;
    }
	
	for (unsigned int i = 0; i<noOfWarriors; i++) {
		char warriorName;
		unsigned int health, attack;
		
		newGameTemplate >> warriorName >> health >> attack;
        
        if (newGameTemplate.fail()) {
            return 1;
        }
		
		defaultSoldiers.push_back(Soldier(health, warriorName, attack));
	}
	
	// Velkost mapy
	unsigned int X = 0, Y = 0;
	
	newGameTemplate >> X >> Y;
    
    if (newGameTemplate.fail()) {
        return 1;
    }
	
	mapa = Map(X,Y);
	
	string line = "";
	getline(newGameTemplate, line);
    
    if (newGameTemplate.fail()) {
        return 1;
    }
    
    bool hasStart = false;
    bool hasEnd = false;
	
	for (unsigned int i = 0; i<Y; i++) {
		getline(newGameTemplate, line);
        
        if (newGameTemplate.fail()) {
            return 1;
        }
        
		for (unsigned int j = 0; j<X; j++) {
			char charInFile = line.at(j);
			
			if (charInFile == ' ') {
				mapa.map.at(i).at(j) = new Road(j, i);
			} else if (charInFile == '#') {
				mapa.map.at(i).at(j) = new Wall(j, i);
			} else if (charInFile == '<') {
				mapa.setEnd(j, i);
                hasEnd = true;
				mapa.map.at(i).at(j) = new Road(j, i);
				mapa.map.at(i).at(j)->setChar('<');
			} else if (charInFile == '>') {
				mapa.setStart(j, i);
                hasStart = true;
				mapa.map.at(i).at(j) = new Road(j, i);
				mapa.map.at(i).at(j)->setChar('>');
			}
		}
	}
    
    if (!hasStart || !hasEnd) {
        return 1;
    }
    
    return 0;
}

unsigned int Game::saveGame() {
	ofstream saveFile;
	saveFile.open("src/data/save.txt", ios::out);
    
    if (!saveFile.is_open() || saveFile.fail()) {
        return 1;
    }
	
	saveFile << defaultTowers.size() << endl;
    
    if (saveFile.fail()) {
        return 1;
    }
	
	for (auto & tower : defaultTowers) {
		saveFile << tower.first << " " << tower.second.getHealth() << " " << tower.second.getCost() << " " << tower.second.getRange() << " " << tower.second.getAttack() << endl;
        
        if (saveFile.fail()) {
            return 1;
        }
	}
	
	saveFile << "" << endl;
    
    if (saveFile.fail()) {
        return 1;
    }
	
	saveFile << defaultSoldiers.size() << endl;
    
    if (saveFile.fail()) {
        return 1;
    }
	
	for (auto & soldier : defaultSoldiers) {
		saveFile << soldier.getCharacter() << " " << soldier.getHp() << " " << soldier.getAttack() << endl;
        
        if (saveFile.fail()) {
            return 1;
        }
	}
	
	saveFile << "" << endl;
    
    if (saveFile.fail()) {
        return 1;
    }
	
	saveFile << mapa.map.at(0).size() << " " << mapa.map.size() << endl;
    
    if (saveFile.fail()) {
        return 1;
    }
	
	for (unsigned int i = 0; i<mapa.map.size(); i++) {
		for (unsigned int j = 0; j<mapa.map.at(i).size(); j++) {
			if (mapa.map.at(i).at(j)->getChar() == '#' ||
				mapa.map.at(i).at(j)->getChar() == '>' || mapa.map.at(i).at(j)->getChar() == '<') {
				saveFile << mapa.map.at(i).at(j)->getChar();
                
                if (saveFile.fail()) {
                    return 1;
                }
			} else {
				saveFile << ' ';
                
                if (saveFile.fail()) {
                    return 1;
                }
			}
		}
		saveFile << endl;
        
        if (saveFile.fail()) {
            return 1;
        }
	}
	
	saveFile << "" << endl;
    
    if (saveFile.fail()) {
        return 1;
    }
	
	unsigned int noOfTowers = 0;
	
	for (unsigned int i = 0; i<towers.size(); i++) {
		if (towers[i]) {
			noOfTowers++;
		}
	}
	
	saveFile << noOfTowers << endl;
    
    if (saveFile.fail()) {
        return 1;
    }
	
	for (unsigned int i = 0; i<towers.size(); i++) {
		if (towers[i]) {
			saveFile << towers[i].get()->getCharacter() << " " << towers[i].get()->getTowerCoordinates().first << " " << towers[i].get()->getTowerCoordinates().second << endl;
            
            if (saveFile.fail()) {
                return 1;
            }
		}
	}
	
	saveFile << "" << endl;
    
    if (saveFile.fail()) {
        return 1;
    }
	
	saveFile << round << " " << moneyAvailable << " " << noOfEachSoldierOnMap << endl;
    
    if (saveFile.fail()) {
        return 1;
    }
	
	saveFile.close();
    
    return 0;
}

unsigned int Game::loadSavedGame() {
	ifstream saveFile;
	saveFile.open("src/data/save.txt", ios::in);
    
    if (!saveFile.is_open() || saveFile.fail()) {
        return 1;
    }
	
	unsigned int defaultTowersSize = 0;
	
	saveFile >> defaultTowersSize;
    
    if (saveFile.fail()) {
        return 1;
    }
	
	for (unsigned int i = 0; i<defaultTowersSize; i++) {
		char towerName;
		unsigned int health, cost, range, attack;
		
		saveFile >> towerName >> health >> cost >> range >> attack;
        
        if (saveFile.fail()) {
            return 1;
        }
		
		StoredTower newTower(health, cost, range, attack, towerName);
		
		defaultTowers[towerName] = newTower;
	}
	
	unsigned int defaultSoldiersSize = 0;
	
	saveFile >> defaultSoldiersSize;
    
    if (saveFile.fail()) {
        return 1;
    }
	
	for (unsigned int i = 0; i<defaultSoldiersSize; i++) {
		char soldierName;
		unsigned int health, attack;
		
		saveFile >> soldierName >> health >> attack;
        
        if (saveFile.fail()) {
            return 1;
        }
		
		Soldier newSoldier(health, soldierName, attack);
		defaultSoldiers.push_back(newSoldier);
	}
	
	unsigned int X = 0, Y = 0;
	
	saveFile >> X >> Y;
    
    if (saveFile.fail()) {
        return 1;
    }
	
	mapa = Map(X,Y);
	
	string line = "";
	getline(saveFile, line);
    
    if (saveFile.fail()) {
        return 1;
    }
    
    bool hasStart = false;
    bool hasEnd = false;
	
	for (unsigned int i = 0; i<Y; i++) {
		getline(saveFile, line);
        
        if (saveFile.fail()) {
            return 1;
        }
		for (unsigned int j = 0; j<X; j++) {
			char charInFile = line.at(j);
			
			if (charInFile == ' ') {
				mapa.map.at(i).at(j) = new Road(j, i);
			} else if (charInFile == '#') {
				mapa.map.at(i).at(j) = new Wall(j, i);
			} else if (charInFile == '<') {
				mapa.setEnd(j, i);
                hasEnd = true;
				mapa.map.at(i).at(j) = new Road(j, i);
				mapa.map.at(i).at(j)->setChar('<');
			} else if (charInFile == '>') {
				mapa.setStart(j, i);
                hasStart = true;
				mapa.map.at(i).at(j) = new Road(j, i);
				mapa.map.at(i).at(j)->setChar('>');
			}
		}
	}
    
    if (!hasStart || !hasEnd) {
        return 1;
    }
	
	unsigned int noOfLiveTowers = 0;
	saveFile >> noOfLiveTowers;
    
    if (saveFile.fail()) {
        return 1;
    }
	
	for (unsigned int i = 0; i<noOfLiveTowers; i++) {
		char towerName;
		unsigned int X, Y;
		
		saveFile >> towerName >> X >> Y;
        
        if (saveFile.fail()) {
            return 1;
        }
		
		placeNewTower(towerName, X, Y);
	}
	
	saveFile >> round >> moneyAvailable >> noOfEachSoldierOnMap;
    
    if (saveFile.fail()) {
        return 1;
    }
    
    return 0;
}

void Game::destroyGame() {
	for (unsigned int i = 0; i<mapa.map.size(); i++) {
		for (unsigned int j = 0; j<mapa.map.at(i).size(); j++) {
			delete mapa.map.at(i).at(j);
			mapa.map.at(i).at(j) = nullptr;
		}
	}
	
	defaultTowers.clear();
}

unsigned int Game::getRound() const {
    return round;
}

unsigned int Game::getMoneyAvailable() const {
    return moneyAvailable;
}

unsigned int Game::placeNewTower(const char towerName, const unsigned int X, const unsigned int Y) {
	map<char, StoredTower>::iterator it = defaultTowers.find(towerName);
	if (it == defaultTowers.end()) {
		return 1;
	}
	
	if (it->second.getCost() > moneyAvailable) {
		return 2;
	}
	
	if (!mapa.canPlaceTower(X, Y)) {
		return 3;
	}
	
	// Set tower coordinates
	it->second.setTowerCoordinates(X, Y);
	
	// Push the newly created shared pointer of tower to towers vector
	towers.push_back(make_shared<StoredTower>(it->second));
	
	// Create weak pointer pointing to the last added tower
	weak_ptr<StoredTower> weakPtr = towers.back();
	
	mapa.placeNewTower(weakPtr, it->first, X, Y);
	
	// Change available money and number of towers
	moneyAvailable = moneyAvailable - it->second.getCost();
	
	noOfLiveTowers++;
	
	return 0;
}

void Game::prepareRound() {
	
	// Load soldiers
	for (unsigned int i = 0; i<defaultSoldiers.size(); i++) {
		for (unsigned int j = 0; j<noOfEachSoldierOnMap; j++) {
			soldiers.push_back(defaultSoldiers[i]);
		}
	}
	
	noOfEachSoldierOnMap++;
    
    round++;
}

void Game::findPath() {
    mapa.findPath();
}

unsigned int Game::moveSoldiers() {
	
	// If we've got some soldier available, put him at the start coordinates of the map
	if (!soldiers.empty()) {
		unsigned int X = mapa.cesta.at(mapa.cesta.size() - 2)->getX();
		unsigned int Y = mapa.cesta.at(mapa.cesta.size() - 2)->getY();
		
		Road * cell = dynamic_cast<Road *> (mapa.map.at(Y).at(X));
		cell->addSoldier(soldiers.back());
		
		soldiers.pop_back();
		
		noOfLiveSoldiers++;
	}
	
	// Ide od ciela cesty
	for (unsigned int i = 0; i<mapa.cesta.size() - 1; i++) {
		
		Road * now = dynamic_cast<Road *>(mapa.cesta.at(i));
		Road * next = dynamic_cast<Road *>(mapa.cesta.at(i+1));
		
        if (!now) {
            Tower * tow = dynamic_cast<Tower *>(mapa.cesta.at(i));
            if (!tow) {
                continue;
            }
            
            if (tow->getStoredTower().expired()) {
                continue;
            }
            
            if (tow->getStoredTower().lock().get()->isAlive()) {
                continue;
            }
        }
		
		// Soldier has reached end
		if (i == 0 && next->getSoldier().isAlive()) {
			return 1;
		}
		
		Soldier soldierToMove = next->getSoldier();
		
		if (soldierToMove.isAlive()) {
			now->addSoldier(soldierToMove);
			now->setChar(soldierToMove.getCharacter());
			next->setChar(' ');
			next->removeSoldier();
			
			for (unsigned int j = 0; j<now->getTowersInRange().size(); j++) {
				// Soldier is in range of some tower
				// Attack soldier with a given tower; soldiers attacks back
				// Returns pair: first - is soldier alive
				//				 second - is Tower alive
				
				// If tower in range has been destroyed, remove weak pointer
				if (now->getTowersInRange().at(j).expired()) {
					now->getTowersInRange().at(j).reset();
					continue;
				}
				
				pair<bool, bool> results = now->attackSoldier(now->getTowersInRange().at(j).lock().get());
				
				// Soldier is dead
				if (!results.first) {
					now->removeSoldier();
					now->setChar(' ');
					
					noOfLiveSoldiers--;
					
					moneyAvailable += 75;
					
					if (noOfLiveSoldiers == 0) {
						return 2;
					}
					
					break;
				}
				
				// Tower is dead
				if (!results.second) {
					pair<unsigned int, unsigned int> towerCoordinates = now->getTowersInRange().at(j).lock().get()->getTowerCoordinates();
					
					mapa.map.at(towerCoordinates.second).at(towerCoordinates.first)->setChar('X');
					
					Tower * tow = dynamic_cast<Tower *>(mapa.map.at(towerCoordinates.second).at(towerCoordinates.first));
					
					for (unsigned int k = 0; k<towers.size(); k++) {
						if (towers[k].get() == tow->getStoredTower().lock().get()) {
							towers[k].reset();
							
							// Remove weak pointer, since tower has been destroyed
							now->getTowersInRange().at(j).reset();
							
						}
					}
					
					tow->getStoredTower().reset();
					
					noOfLiveTowers--;
				}
				
				if (noOfLiveTowers == 0) {
					return 3;
				}
			}
		}
		
	}
	
	return 0;
}

void Game::cleanUpMap() {
	for (unsigned int i = 0; i<mapa.map.size(); i++) {
		for (unsigned int j = 0; j<mapa.map.at(i).size(); j++) {
			mapa.map.at(i).at(j)->setStatus(-1);
			mapa.map.at(i).at(j)->setBefore(nullptr);
		}
	}
}
