//
//  PG_MudWithGrass.cpp
//
//  Created by Mortimer Pavlitski on 21/04/2018.
//

#include "PG_MudWithGrass.hpp"

PG_MudWithGrass::PG_MudWithGrass(ofColor grassColour) {
    grassColour_ = grassColour;
}

PG_MudWithGrass::~PG_MudWithGrass() {
    
}

void PG_MudWithGrass::draw() {
    // Ground
    ofSetColor(59, 30, 29);
    ofDrawRectangle(0, 0, getW(), -getH());
    
    // Grass
    ofSetColor(grassColour_);
    for(int i = 0; i < grass_.size(); i++) {
        ofDrawRectangle((i*2), -getH(), 4, -grass_[i]);
    }
}

void PG_MudWithGrass::makeGrass() {
    float nGrassBlades  = (getW() * 0.5) - 1;
    
    for(int i = 0; i < nGrassBlades; i++) {
        grass_.emplace_back(ofRandom(6.0, 20.0));
    }
}

void PG_MudWithGrass::sizeUpdated() {
    makeGrass();
}
