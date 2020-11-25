//
//  PP_VerticalMoving.hpp
//
//  Created by Mortimer Pavlitski on 23/04/2018.
//

#ifndef PP_VerticalMoving_hpp
#define PP_VerticalMoving_hpp

#include <stdio.h>

#include "IPlatformPhysics.hpp"

class PP_VerticalMoving : public IPlatformPhysics {
public:
    PP_VerticalMoving(bool isPhase, bool isUp);
    ~PP_VerticalMoving();
    
    Vector updatePhysics(float timePassed) override;
    
    float   yPosOffset_;
    float   yPosOffsetMax_;
    bool    isMovingUp_;
};

#endif /* PP_VerticalMoving_hpp */
