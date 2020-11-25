//
//  GO_Shard.cpp
//
//  Created by Mortimer Pavlitski on 07/04/2018.
//

#include "GO_Shard.hpp"

GO_Shard::GO_Shard(float x, float y, int* nShardsPtr, Audio* audioPtr) {
    size_       = 10;
    wMax_       = size_ * 2;
    width_      = wMax_;
    r_          = 0;
    rSpeed_     = ofRandom(1, 1.5);
    height_     = size_ + wMax_;
    hue_        = ofRandom(0, 255);
    colour_     = ofColor::fromHsb(hue_, 255, 255);
    isColleted_ = false;
    nShardsPtr_ = nShardsPtr;
    
    setBounds(x, y, wMax_, height_);

    audioPtr_ = audioPtr;
};


void GO_Shard::draw() {
    ofSetColor(colour_);
    if (!isColleted_) {
        ofDrawRectangle((wMax_ * 0.5) - (getW() * 0.5), 0, getW(), -getH());
    }
}

void GO_Shard::update(float timePassed) {
    
    if(!isColleted_) {
        animateRotation(timePassed);
    }
}

void GO_Shard::animateRotation(float timePassed) {
    r_ += rSpeed_ * (timePassed);
    
    if (r_ > 2)
        r_ = 0;
    
    if (r_ > 0 && r_ < 1)
        rr_ = r_;
    else if (r_ > 1 && r_ < 2)
        rr_ = (2 - r_);
    
    setW(wMax_ * rr_);
    
    hue_     = fmod(hue_ + (timePassed * 10), 255);
    colour_  = ofColor::fromHsb(hue_, 255, 255);
    colour_.setBrightness(0.5 + (rr_ * 0.5));
}

CollisionState GO_Shard::getCollisionState(float xPos1, float yPos1, float xPos2, float yPos2, float width, float height) {
    
    if(xPos1 + width  >= getX() && xPos1 <= getX() + getW() &&
       yPos1 + height >= getY() && yPos1 <= getY() + getH() &&
       !isColleted_) {
        isColleted_ = true;
        (*nShardsPtr_)++;
        audioPtr_->playShardSound();
    }
    
    return CollisionState::Nothing;
}

