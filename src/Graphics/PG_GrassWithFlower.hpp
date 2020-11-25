//
//  PG_GrassWithFlower.hpp
//
//  Created by Mortimer Pavlitski on 01/05/2018.
//

#ifndef PG_GrassWithFlower_hpp
#define PG_GrassWithFlower_hpp

#include <stdio.h>
#include "ofMain.h"
#include "G_Flower.hpp"

#include "IPlatformGraphic.hpp"

class PG_GrassWithFlower : public IPlatformGraphic {
public:
    PG_GrassWithFlower(ofColor grassColour);
    ~PG_GrassWithFlower();
    
    void sizeUpdated() override;
    void makeGrass();
    void update(float timeElapsed) override;
    void draw() override;
    
private:
    std::vector<float>  grass_;
    ofColor             grassColour_;
    G_Flower            flower_;
    float               flowerXPos_;
};

#endif /* PG_GrassWithFlower_hpp */
