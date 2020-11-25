//
//  PG_Ether.cpp
//
//  Created by Mortimer Pavlitski on 23/04/2018.
//

#include "PG_Ether.hpp"

PG_Ether::PG_Ether() {
    
};

PG_Ether::~PG_Ether() {
    
};

void PG_Ether::draw() {
    ofSetColor(EtherColourPallet::Pinkish);
    ofDrawRectangle(0, 0, getW(), -getH());
    etherWall_.draw(-getW(), getW());
}
