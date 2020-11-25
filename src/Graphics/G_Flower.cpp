//
//  G_Flower.cpp
//  MusicalFlowers
//
//  Created by Mortimer Pavlitski on 01/05/2018.
//

#include "G_Flower.hpp"

G_Flower::G_Flower(ofColor colour) : waveTable_(32) {
    z_ = 0;
    isZAscending_ = true;
    
    width_      = ofRandom(4, 10);
    height_     = (width_ * 8) + ofRandom(0, 35);
    radius_     = (width_ * 1.8) + ofRandom(0, 15);
    
    nPetals_    = ofRandom(3,7);
    angle_      = ofRandom(0);
    speed_      = floor(ofRandom(40, 80));
    
    flowerHead_.setColor(ofColor::fromHsb(
                fmod(colour.getHue() + ofRandom(0, 40), 255),
                colour.getSaturation(),
                colour.getBrightness()));
    
    stemColour_     = ofColor(30, ofRandom(100, 255), 70);
    
    nPoints =   waveTable_.getBufferSize() * nPetals_;
    nWave   =   waveTable_.getBufferSize();
}

G_Flower::~G_Flower() {
    
}

void G_Flower::update(float timeElapsed) {
    screenHeight_ = ofGetWindowHeight();
    
    angle_ = fmod(float(angle_ + (timeElapsed * speed_)), 360);
    
    float petalAngle = fmod(angle_ + 90, (360 /nPetals_));
    
    if(oldPetalAngle_ > petalAngle){
        // play flower sounds?
    }
    
    oldPetalAngle_ = petalAngle;
    
    // modulate buffer interpolation depth
    if(isZAscending_) {
        z_ += timeElapsed * 0.3;
    } else {
        z_ -= timeElapsed * 0.3;
    }
    
    // wrap z_
    if(z_ > 2) {
        isZAscending_ = false;
        z_ = 2;
    } else if (z_ < 0) {
        isZAscending_ = true;
        z_ = 0;
    }
}

void G_Flower::draw() {
    ofPushView();
    
    // Draw Stem
    ofSetColor(stemColour_);
    ofDrawRectangle(0 - (width_ * 0.5), 0, width_, -height_);
    
    // Draw Head
    ofTranslate(0, -height_);
    ofRotateZ(angle_);
    
    flowerHead_.clear();
    
    for(int i = 0; i < nPoints + 1; i++){
        float x = cos(2*PI/nPoints * i) * radius_ * (1 + (waveTable_.getSample(i % nWave, z_) * 0.3));
        float y = sin(2*PI/nPoints * i) * radius_ * (1 + (waveTable_.getSample(i % nWave, z_) * 0.3));
        
        if(i == 0) {
            flowerHead_.moveTo(x, -y, 0.5);
        }
        flowerHead_.lineTo(x, -y, 0.5);
    }
    
    flowerHead_.close();
    flowerHead_.draw();
    
    ofPopView();
}

