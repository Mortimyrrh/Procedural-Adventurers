//
//  IPlatformGraphic.hpp
//
//  Created by Mortimer Pavlitski on 21/04/2018.
//

#ifndef IPlatformGraphic_hpp
#define IPlatformGraphic_hpp

#include "ofMain.h"
#include <stdio.h>

#include "Colours.hpp"

class IPlatformGraphic {
public:
    virtual void draw() = 0;
    
    virtual void sizeUpdated(){};
    
    virtual void update(float timeElapsed){};
    
    void setSize(float width, float height) {
        width_ = width;
        height_ = height;
        sizeUpdated();
    }
    
    float getW() {
        return width_;
    }
    
    float getH() {
        return height_;
    }

private:
    float width_;
    float height_;
};

#endif /* IPlatformGraphic_hpp */
