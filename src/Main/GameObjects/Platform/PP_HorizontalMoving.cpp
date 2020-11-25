//
//  PP_HorizontalMoving.cpp
//
//  Created by Mortimer Pavlitski on 21/04/2018.
//

#include "PP_HorizontalMoving.hpp"

PP_HorizontalMoving::PP_HorizontalMoving(bool isPhase) {
    speed_          = 100;
    xPosOffsetMax_  = 300;
    xPosOffset_     = xPosOffsetMax_ * isPhase;
    isMovingLeft_   = false;
}

PP_HorizontalMoving::~PP_HorizontalMoving() {
    
}

Vector PP_HorizontalMoving::updatePhysics(float timePassed) {

    if (isMovingLeft_) {
        vel_.x        = -timePassed * speed_;
    } else {
        vel_.x        = timePassed * speed_;
    }
    
    xPosOffset_ += vel_.x;

    if (xPosOffset_ >= xPosOffsetMax_)
        isMovingLeft_ = true;
    else if (xPosOffset_ <= 0)
        isMovingLeft_ = false;
    
    return vel_;
}
