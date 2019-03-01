//
//  Screen.hpp
//  TowerDefense
//
//  Created by Tomáš Taro on 05/05/2018.
//  Copyright © 2018 Tomáš Taro. All rights reserved.
//

#ifndef Screen_hpp
#define Screen_hpp

#include <ncurses.h>
#include <string>

/*
 * Screen class is an abstract class responsible for showing up different screens, such as New Game screen...
 */
class Screen {
public:
    /**
     * Screen constructor
     */
	Screen();
    
    /**
     * Screen's virtual destructor
     */
	virtual ~Screen();
	
    /**
     * Method, which renders any sub-child's screen
     *
     * @return unsigned int
     */
	virtual unsigned int showScreen() = 0;
    
    void showFailedIOMessage(const unsigned int idxOfMessage) const;
	
protected:
	WINDOW * window;
	int maxY = 0;
	int maxX = 0;
};

#endif /* Screen_hpp */
