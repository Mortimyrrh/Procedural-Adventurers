//
//  PG_WhiteGrass.hpp
//
//  Created by Mortimer Pavlitski on 01/05/2018.
//

#ifndef PG_WhiteGrass_hpp
#define PG_WhiteGrass_hpp

#include <stdio.h>
#include "ofMain.h"

#include "IPlatformGraphic.hpp"

class PG_WhiteGrass : public IPlatformGraphic {
public:
    PG_WhiteGrass();
    ~PG_WhiteGrass();
    
    void sizeUpdated() override;
    void makeGrass();
    void draw() override;
    
private:
    std::vector<float> grass_;
    ofColor grassColour_;
    
};

#endif // PG_WhiteGrass_hpp
