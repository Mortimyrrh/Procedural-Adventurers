//
//  IPlatformCollision.hpp
//  TheProceduralAdventurers
//
//  Created by Mortimer Pavlitski on 21/04/2018.
//

#ifndef IPlatformCollision_hpp
#define IPlatformCollision_hpp

#include <stdio.h>

// I was going to abstract out the colltion detection but this was a low pirorty.
// I left the code in to show how I would have done this.

class IPlatformCollision {
public:
    virtual void updateCollision() = 0;
};

#endif /* IPlatformCollision_hpp */
