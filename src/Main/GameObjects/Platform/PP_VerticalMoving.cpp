//
//  PP_VerticalMoving.cpp
//
//  Created by Mortimer Pavlitski on 23/04/2018.
//

#include "PP_VerticalMoving.hpp"

PP_VerticalMoving::PP_VerticalMoving(bool isPhase, bool isUp) {
    speed_              = 100;
    
    if (isUp) {
        yPosOffsetMax_  = 200;
    } else {
        yPosOffsetMax_  = -200;
    }
    
    yPosOffset_         = yPosOffsetMax_ * isPhase;
    isMovingUp_         = false;
}

PP_VerticalMoving::~PP_VerticalMoving() {
    
}

Vector PP_VerticalMoving::updatePhysics(float timePassed) {
    
    if (isMovingUp_) {
        vel_.y        = -timePassed * speed_;
    } else {
        vel_.y        = timePassed * speed_;
    }
    
    yPosOffset_ += vel_.y;
    
    if (yPosOffset_ >= yPosOffsetMax_)
        isMovingUp_ = true;
    else if (yPosOffset_ <= 0)
        isMovingUp_ = false;

    return vel_;
}
