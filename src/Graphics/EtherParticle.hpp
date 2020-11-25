//
//  EtherParticle.hpp
//
//  Created by Mortimer Pavlitski on 19/11/2017.
//

#ifndef EtherParticle_hpp
#define EtherParticle_hpp

#include <stdio.h>
#include "ofMain.h"

#include "PlayerEntity.hpp"
#include "ofxPDSP.h"

class EtherParticle {
public:
    
    EtherParticle(float playerXPos, float playerYPos){
        init(playerXPos, playerYPos);
    };
    
    ~EtherParticle(){};
    
    // sets initial state
    void init(float playerXPos, float playerYPos);
    
    //updates the rotation
    void update(float timePassed, float playerXPos, float playerYPos);
    
    // changes shade and width to make it look like rotation
    void animateRotation(float timePassed);
    
    // Draws Paritcle
    void draw();
    
private:
    float size_;            // size of particle
    float x_;               // horizontal position
    float y_ = 0.0;         // virtical position
    float w_;               // curent width
    float wMax_;            // maximun width when rotating
    float r_;               // curent rotation amount
    float rSpeed_;          // speed of rotation
    float rr_;              // rotation value as ramp from 0 -> 1 then 1 -> 0
    float h_;               // height of particle
    float speed;            // curent virtical speed
    float speedMax;         // max vertical speed
    ofFloatColor colour_;   // particle colour
};

class EtherParticles {
public:
    void update(float timePassed, float screenOffset, float playerXPos, float playerYPos){
        
        // chance of genirating a particle up to a max
        if (etherParticles.size() < 60 && ofRandom(100) < 20)
            etherParticles.push_back({playerXPos, playerYPos});
        
        //Update particle
        for (EtherParticle& p : etherParticles)
            p.update(timePassed, playerXPos, playerYPos);
    };
    
    void draw(){
        for (EtherParticle& p : etherParticles)
            p.draw();
    }
    
    int getSize(){
        return etherParticles.size();
    }
    
private:
    std::vector<EtherParticle> etherParticles;
    
};

#endif /* EtherParticle_hpp */

