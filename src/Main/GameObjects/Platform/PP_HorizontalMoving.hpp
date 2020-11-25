//
//  PP_HorizontalMoving.hpp
//
//  Created by Mortimer Pavlitski on 21/04/2018.
//

#ifndef PP_HorizontalMoving_hpp
#define PP_HorizontalMoving_hpp

#include <stdio.h>

#include "IPlatformPhysics.hpp"

class PP_HorizontalMoving : public IPlatformPhysics {
public:
    PP_HorizontalMoving(bool isPhase);
    ~PP_HorizontalMoving();
    
    Vector updatePhysics(float timePassed) override;
    
    float   xPosOffset_;
    float   xPosOffsetMax_;
    bool    isMovingLeft_;
};


#endif /* PP_HorizontalMoving_hpp */
