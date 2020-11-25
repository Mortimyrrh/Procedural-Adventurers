//
//  IPlatformPhysics.hpp
//
//  Created by Mortimer Pavlitski on 21/04/2018.
//

#ifndef IPlatformPhysics_hpp
#define IPlatformPhysics_hpp

#include <stdio.h>
#include "ofMain.h"

struct Vector {
    float x;
    float y;
};

class IPlatformPhysics {
public:
    IPlatformPhysics()
    {
        speed_ = 0;
        vel_.x = 0;
        vel_.y = 0;
    };
    
    virtual Vector updatePhysics(float timePassed) = 0;
    
    Vector  vel_;
    float   speed_;
};

#endif /* IPlatformPhysics_hpp */
