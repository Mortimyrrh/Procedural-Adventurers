//
//  PG_Lines.cpp
//
//  Created by Mortimer Pavlitski on 30/04/2018.
//

#include "PG_Lines.hpp"

PG_Lines::PG_Lines() {
    
};

PG_Lines::~PG_Lines() {
    
};

void PG_Lines::draw() {
    ofSetLineWidth(4);
    
    for (int i = 0; i < getH(); i+= 8) {
        ofSetColor(90, 255 - (i * 3), 255 - (i * 3));
        ofDrawLine(0, i - getH(), getW(), i - getH());
    }
}
