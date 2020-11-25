//
//  EtherParticle.hpp
//  twilight_particles
//
//  Created by Mortimer Pavlitski on 19/11/2017.
//

#ifndef EtherParticle_hpp
#define EtherParticle_hpp

#include <stdio.h>

// todo
// gradent texture?

/*
// how to use
 
// create ether particle vector
std::vector<EtherParticle> EtherParticles;
 
// % chance of genirating a particle up to a max
if (EtherParticles.size() < 200 && ofRandom(100) < 5)
    EtherParticles.push_back({});

// updates the particles
for (EtherParticle& p : EtherParticles)
    p.update(timePassed);

// draw particles
for (EtherParticle& p : EtherParticles)
    p.draw();
 */

class EtherParticle {
public:
    
    EtherParticle(){
        init();
    };
    
    ~EtherParticle(){};
    
    // sets initial state
    void init() {
        size_ = 7;
        y_ = -20;
        x_ = ofRandomWidth();
        wMax_ = ofRandom(size_) + size_;
        w_ = wMax_;
        r_ = 0;
        rSpeed_ = ofRandom(1) + 0.5;
        h_ = ofRandom(size_) + wMax_;
        speed = 30;
        speedMax = ofRandom(100) + 50;
        //colour_ = ofFloatColor(0.5 + ofRandom(0.5), 0.5 + ofRandom(0.5), 0, 0.5);
        //colour_ = ofFloatColor(x_ / ofGetWidth(), 1 - x_ / ofGetWidth(), 0, 0.5);
        colour_ = ofFloatColor(0);
    }
    
    //updates the position and rotation
    void update(float timePassed) {
        y_ += speed * (timePassed);
        
        if (speed < speedMax)
            speed+= 70 * timePassed;
        
        if (y_ > ofGetHeight())
            init();
        
        animateRotation(timePassed);
    }
    
    // changes shade and width to make it look like rotation
    void animateRotation(float timePassed) {
        r_ += rSpeed_ * (timePassed);
        
        if (r_ > 2)
            r_ = 0;
        
        if (r_ > 0 && r_ < 1)
            rr_ = r_;
        else if (r_ > 1 && r_ < 2)
            rr_ = (2 - r_);
        
        w_ = wMax_ * rr_;
        
        colour_.setBrightness(0.5 + (rr_ * 0.5));
    }
    
    // Draws Paritcle
    void draw() {
        ofSetColor(colour_);
        ofDrawRectangle(x_ - (w_ * 0.5), ofGetHeight()-y_, w_, -h_);
    }
    
private:
    float size_;            // size of particle
    float x_;               // horizontal position
    float y_;               // virtical position
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

#endif /* EtherParticle_hpp */
