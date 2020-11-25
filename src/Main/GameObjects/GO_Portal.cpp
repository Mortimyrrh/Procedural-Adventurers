//
//  GO_Portal.cpp
//  TheProceduralAdventurers
//
//  Created by Mortimer Pavlitski on 23/04/2018.
//

#include "GO_Portal.hpp"

GO_Portal::GO_Portal(float xPos, float yPos, int portalID, int lockLevel, int* nShardsPtr, int* switchLevelToPtr, Audio* audioPtr) {
    setBounds(xPos, yPos, 300, 300);
    speed_              = 3;
    portalID_           = portalID;
    isPortalUnlocked_   = false;
    lockLevel_          = lockLevel;
    nShardsPtr_         = nShardsPtr;
    switchLevelToPtr_   = switchLevelToPtr;
    audioPtr_           = audioPtr;
    
    font.load(Font::hylia, 24);
}

GO_Portal::~GO_Portal() {
    
}

void GO_Portal::update(float timePassed) {
    if((*nShardsPtr_) >= lockLevel_) {
        isPortalUnlocked_ = true;
    }
    
    updateSpeed(timePassed);
    
    portalGraphic.update(timePassed, speed_);
}

void GO_Portal::draw() {
    
    if (lockLevel_ != 0) {
        ofSetColor(255);
        font.drawString(to_string(lockLevel_), 145, -350);
    }
    
    if((*switchLevelToPtr_) == -1 || !isPlayerInPortal_)
        portalGraphic.draw(+150, -150);
}

CollisionState GO_Portal::getCollisionState(float xPos1, float yPos1, float xPos2, float yPos2, float width, float height) {

    if (xPos1 + width  >= getX() && xPos1 <= getX() + getW() &&
        yPos1 + height >= getY() && yPos1 <= getY() + getH() &&
        isPortalUnlocked_) {
        isPlayerInPortal_ = true;
        return CollisionState::InPortal;
    
    } else {
        isPlayerInPortal_ = false;
        return CollisionState::Nothing;
    }
}

int GO_Portal::getPortalID() {
    return portalID_;
}


void GO_Portal::updateSpeed(float timePassed) {
    
    if (isPlayerInPortal_){
        speed_ *= timePassed * 34;
    } else if (speed_ > 3) {
        speed_ -= timePassed * 400;
    }

    isPortalActive_ = false;
    
    if (speed_ > 1000) {
        isPortalActive_ = true;
        speed_ = 3;
        audioPtr_->playPortalSound();
        
    } else if (speed_ < 3){
        speed_ = 3;
    }
}

bool GO_Portal::getIsPortalActive() {
    return isPortalActive_;
}
