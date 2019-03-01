//
//  Wall.hpp
//  
//
//  Created by Tomáš Taro on 05/05/2018.
//

#ifndef Wall_hpp
#define Wall_hpp

#include "Cell.hpp"

/**
 * Wall class, which represents wall in map
 */
class Wall : public Cell {
public:
    /**
     * Wall constructor
     *
     * @param X X-coordination in the map
     * @param Y Y-coordination in the map
     */
	Wall(const unsigned int X, const unsigned int Y);
};

#endif /* Wall_hpp */
