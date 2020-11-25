//
//  PG_GrassWithFlower.cpp
//
//  Created by Mortimer Pavlitski on 01/05/2018.
//

#include "PG_GrassWithFlower.hpp"

PG_GrassWithFlower::PG_GrassWithFlower(ofColor grassColour)
: flower_(grassColour)
{
    grassColour_ = grassColour;
}

PG_GrassWithFlower::~PG_GrassWithFlower() {
    
}

void PG_GrassWithFlower::draw() {
    // Ground
    ofSetColor(59, 30, 29);
    ofDrawRectangle(0, 0, getW(), -getH());
    
    // Flower
    ofPushView();
    ofTranslate(flowerXPos_, -getH());
    flower_.draw();
    ofPopView();
    
    // Grass
    ofSetColor(grassColour_);
    for(int i = 0; i < grass_.size(); i++) {
        ofDrawRectangle((i*2), -getH(), 4, -grass_[i]);
    }
}

void PG_GrassWithFlower::update(float timeElapsed) {
    flower_.update(timeElapsed);
}

void PG_GrassWithFlower::makeGrass() {
    float nGrassBlades  = (getW() * 0.5) - 1;
    
    for(int i = 0; i < nGrassBlades; i++) {
        grass_.emplace_back(ofRandom(6.0, 20.0));
    }
    
    flowerXPos_ = getW() * ofRandom(0.2, 0.8);
}

void PG_GrassWithFlower::sizeUpdated() {
    makeGrass();
}
