//
//  GO_Shard.hpp
//
//  Created by Mortimer Pavlitski on 07/04/2018.
//

#ifndef GO_Shard_hpp
#define GO_Shard_hpp

#include <stdio.h>
#include "ofMain.h"

#include "GameObjectBase.hpp"

class GO_Shard : public GameObjectBase {
public:
    GO_Shard(float x, float y, int* nShardsPtr, Audio* audioPtr);
    ~GO_Shard(){};
    
    void draw() override;
    void update(float timePassed) override;
    CollisionState getCollisionState(float xPos1, float yPos1, float xPos2, float yPos2, float width, float height) override;
    
    // changes shade and width to make it look like rotation
    void animateRotation(float timePassed);
    
private:
    bool isColleted_;       // Has been collected by the player?
    
    int*    nShardsPtr_;    // Score Counter
    //Graphic
    float size_;            // size of particle
    float wMax_;            // maximun width when rotating
    float r_;               // curent rotation amount
    float rSpeed_;          // speed of rotation
    float rr_;              // rotation value as ramp from 0 -> 1 then 1 -> 0
    ofFloatColor colour_;   // particle colour
    float hue_;             // changing hue
    
    // Audio
    Audio* audioPtr_;
};

#endif /* GO_Shard_hpp */
