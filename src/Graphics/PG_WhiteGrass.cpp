//
//  PG_WhiteGrass.cpp
//
//  Created by Mortimer Pavlitski on 01/05/2018.
//

#include "PG_WhiteGrass.hpp"

PG_WhiteGrass::PG_WhiteGrass() {
    grassColour_ = ofColor(180);
}

PG_WhiteGrass::~PG_WhiteGrass() {
    
}

void PG_WhiteGrass::draw() {
    // Ground
    ofSetColor(59, 30, 29);
    ofDrawRectangle(0, 0, getW(), -getH());
    
    // Grass
    ofSetColor(grassColour_);
    for(int i = 0; i < grass_.size(); i++) {
        ofDrawRectangle((i*2), -getH(), 4, -grass_[i]);
    }
}

void PG_WhiteGrass::makeGrass() {
    float nGrassBlades  = (getW() * 0.5) - 1;
    
    for(int i = 0; i < nGrassBlades; i++) {
        grass_.emplace_back(ofRandom(6.0, 20.0));
    }
}

void PG_WhiteGrass::sizeUpdated() {
    makeGrass();
}
