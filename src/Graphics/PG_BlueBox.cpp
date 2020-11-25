//
//  PG_BlueBox.cpp
//
//  Created by Mortimer Pavlitski on 30/04/2018.
//

#include "PG_BlueBox.hpp"

PG_BlueBox::PG_BlueBox() {
    
};

PG_BlueBox::~PG_BlueBox() {
    
};

void PG_BlueBox::draw() {
    ofSetLineWidth(4);
    ofSetColor(90, 255, 255);
    ofNoFill();
    ofDrawRectangle(0, 0, getW(), - getH());
    ofFill();
}
