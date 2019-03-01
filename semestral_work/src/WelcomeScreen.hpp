//
//  WelcomeScreen.hpp
//  TowerDefense
//
//  Created by Tomáš Taro on 05/05/2018.
//  Copyright © 2018 Tomáš Taro. All rights reserved.
//

#ifndef WelcomeScreen_hpp
#define WelcomeScreen_hpp

#include "Screen.hpp"

using namespace std;

/**
 * WelcomeScreen class responsible for showing up the first game screen
 */
class WelcomeScreen : public Screen {
public:
	WelcomeScreen() : Screen() {}
	
	virtual unsigned int showScreen() override;
};

#endif /* WelcomeScreen_hpp */
