//
//  EtherParticle.cpp
//
//  Created by Mortimer Pavlitski on 15/03/2018.
//

#include "EtherParticle.hpp"

void EtherParticle::init(float playerXPos, float playerYPos) {
    size_ = 7;
    y_ = ofRandom(- playerYPos - 400, - playerYPos + 600);
    x_ = ofRandom(playerXPos - 1000, playerXPos + 2000);
    wMax_ = ofRandom(size_) + size_;
    w_ = wMax_;
    r_ = 0;
    rSpeed_ = ofRandom(1, 1.5);
    h_ = ofRandom(size_) + wMax_;
    speed = 30;
    speedMax = ofRandom(50, 150);
    colour_ = ofFloatColor(0.4, ofRandom(0.6, 1), ofRandom(0.7, 1), ofRandom(0.2, 0.8));
    //colour_ = ofFloatColor(x_ / ofGetWidth(), 1 - x_ / ofGetWidth(), 0, 0.5);
    //colour_ = ofFloatColor(0);
}

void EtherParticle::update(float timePassed, float playerXPos, float playerYPos) {
    y_ += speed * (timePassed);
    
    if (speed < speedMax)
        speed+= 70 * timePassed;
    
    if (y_ > ofGetHeight() + 200)
        init(playerXPos, playerYPos);
    
    animateRotation(timePassed);
}

void EtherParticle::animateRotation(float timePassed) {
    r_ += rSpeed_ * (timePassed);
    
    if (r_ > 2)
        r_ = 0;
    
    if (r_ > 0 && r_ < 1)
        rr_ = r_;
    else if (r_ > 1 && r_ < 2)
        rr_ = (2 - r_);
    
    w_ = wMax_ * rr_;
    
    colour_.setBrightness(0.5 + (rr_ * 0.5));
}

void EtherParticle::draw() {
    ofSetColor(colour_);
    ofDrawRectangle(x_ - (w_ * 0.5), -y_, w_, -h_);
}

