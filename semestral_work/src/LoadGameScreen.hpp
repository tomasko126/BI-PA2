//
//  LoadGameScreen.hpp
//  TowerDefense
//
//  Created by Tomáš Taro on 30/05/2018.
//  Copyright © 2018 Tomáš Taro. All rights reserved.
//

#ifndef LoadGameScreen_hpp
#define LoadGameScreen_hpp

#include "NewGameScreen.hpp"

/**
 * LoadGameScreen class, responsible for showing up loaded game
 */
class LoadGameScreen : public NewGameScreen {
public:
	LoadGameScreen();
	
	virtual unsigned int showScreen() override;
};
#endif /* LoadGameScreen_hpp */
