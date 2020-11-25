//
//  GameWindow.hpp
//
//  Created by Mortimer Pavlitski on 25/04/2018.
//

#ifndef GameWindow_hpp
#define GameWindow_hpp

#include <stdio.h>
#include "PlayerEntity.hpp"

class GameWindow {
public:
    GameWindow(PlayerEntity* playerPtr);
    ~GameWindow();
    
    void updateScreenWindow(bool isSmoothing);
    void updateWindowSize(float windowWidth, float height);
    
    float getX();
    float getY();
    
private:
    float xPos_;
    float yPos_;
    float LastXPos_;
    float LastYPos_;
    
    float windowWidth_;
    float windowHeight_;
    
    PlayerEntity* playerPtr_;
};

#endif /* GameWindow_hpp */
