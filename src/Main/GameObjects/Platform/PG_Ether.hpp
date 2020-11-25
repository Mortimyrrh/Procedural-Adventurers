//
//  PG_Ether.hpp
//
//  Created by Mortimer Pavlitski on 23/04/2018.
//

#ifndef PG_Ether_hpp
#define PG_Ether_hpp

#include <stdio.h>
#include "ofMain.h"

#include "IPlatformGraphic.hpp"
#include "G_EtherWall.hpp"

class PG_Ether : public IPlatformGraphic {
public:
    PG_Ether();
    ~PG_Ether();
    
    void draw() override;
    
private:
    G_EtherWall     etherWall_;
};

#endif /* PG_Ether_hpp */
