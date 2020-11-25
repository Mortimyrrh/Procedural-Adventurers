//
//  PP_Static.cpp
//
//  Created by Mortimer Pavlitski on 23/04/2018.
//

#include "PP_Static.hpp"

PP_Static::PP_Static() {
    vel_.x = 0;
    vel_.y = 0;
}

PP_Static::~PP_Static() {
}

Vector PP_Static::updatePhysics(float timePassed) {
    return vel_;
}
