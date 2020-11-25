//
//  PP_Static.hpp
//
//  Created by Mortimer Pavlitski on 23/04/2018.
//

#ifndef PP_Static_hpp
#define PP_Static_hpp

#include <stdio.h>

#include "IPlatformPhysics.hpp"

class PP_Static : public IPlatformPhysics {
public:
    PP_Static();
    ~PP_Static();
    
    Vector updatePhysics(float timePassed) override;
};

#endif /* PP_Static_hpp */
