//
//  ScreenWindow.cpp
//
//  Created by Mortimer Pavlitski on 25/04/2018.
//

#include "GameWindow.hpp"

GameWindow::GameWindow(PlayerEntity* playerPtr) {
    playerPtr_ = playerPtr;
    updateScreenWindow(false);
    
    xPos_        = 0;
    yPos_        = 0;
    LastXPos_    = 0;
    LastYPos_    = 0;
    
    windowWidth_    = 0;
    windowHeight_   = 0;
}

GameWindow::~GameWindow(){
    
}

void GameWindow::updateScreenWindow(bool isSmoothing) {
    bool intertiaEffect = isSmoothing;
    
    // save old positions
    LastXPos_  = xPos_;
    LastYPos_  = yPos_;
    
    // set new positions
    float x = 0;
    float y = windowHeight_ * 0.3 - playerPtr_->getY();
    
    if (intertiaEffect) {
        if (playerPtr_->getIsFacingRight()) {
            // Right
            x = -playerPtr_->getX() + windowWidth_ * 0.40;
        } else {
            // Left
            x = -playerPtr_->getX() + windowWidth_ * 0.60;
        }
        
        // Intertia effect
        xPos_ = x - ((x - LastXPos_) * 0.91);
        yPos_ = y - ((y - LastYPos_) * 0.85);
        
    } else {
        // no Intertia effect
        x = -playerPtr_->getX() + 400;
        xPos_ = x;
        yPos_ = y;
    }
}

void GameWindow::updateWindowSize(float windowWidth, float windowHeight) {
    windowWidth_  = windowWidth;
    windowHeight_ = windowHeight;
    updateScreenWindow(true);
}

float GameWindow::getX() {
    return xPos_;
}

float GameWindow::getY() {
    return yPos_;
}
