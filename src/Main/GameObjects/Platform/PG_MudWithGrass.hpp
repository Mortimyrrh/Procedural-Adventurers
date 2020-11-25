//
//  PG_MudWithGrass.hpp
//
//  Created by Mortimer Pavlitski on 21/04/2018.
//

#ifndef PG_MudWithGrass_hpp
#define PG_MudWithGrass_hpp

#include <stdio.h>
#include "ofMain.h"

#include "IPlatformGraphic.hpp"

class PG_MudWithGrass : public IPlatformGraphic {
public:
    PG_MudWithGrass(ofColor grassColour);
    ~PG_MudWithGrass();
    
    void sizeUpdated() override;
    void makeGrass();
    void draw() override;
    
private:
    std::vector<float> grass_;
    ofColor grassColour_;
    
};

#endif /* PG_MudWithGrass_hpp */
