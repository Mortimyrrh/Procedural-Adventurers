//
//  Scales.hpp
//
//  Created by Mortimer Pavlitski on 28/03/2018.
//

#ifndef Scales_hpp
#define Scales_hpp

#include <stdio.h>

static float minorPentaScale[8] { 72.0f, 75.0f, 77.0f, 79.0f, 82.0f, 84.0f, 87.0f, 89.0f }; // minor pentatonic scale

static float majorScale[8] { 72.0f, 74.0f, 76.0f, 77.0f, 79.0f, 81.0f, 83.0f, 84.0f }; // major scale

static float akebonoScale[8] { 72.0f, 74.0f, 75.0f, 79.0f, 80.0f, 84.0f, 86.0f, 87.0f }; // akebono scale

// Get random note from key and scale
static float getRandNote(int key_, int scale) {
    
    float note = - 28.0f + key_;
    
    switch (scale) {
        case 0:
            note += minorPentaScale[int(ofRandom(7))];
            break;
            
        case 1:
            note += majorScale[int(ofRandom(7))];
            break;
            
        case 2:
            note += akebonoScale[int(ofRandom(7))];
            break;
            
        default:
            break;
    }
    
    return note;
}

// Get random audio triger value from probablity
static float getRandomTrig(float percent) {
    if(ofRandom(1.0) < percent){
        return ofRandom(0.6, 1.0);
    } else {
        return 0.0f;
    }
}

#endif /* Scales_hpp */
