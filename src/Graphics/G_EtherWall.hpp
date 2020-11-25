//
//  G_EtherWall.hpp
//
//  Created by Mortimer Pavlitski on 29/11/2017.
//

#ifndef G_EtherWall_hpp
#define G_EtherWall_hpp

#include <stdio.h>
#include "ofMain.h"

class G_EtherWall {
public:
    G_EtherWall();
    ~G_EtherWall();
    
    void draw(float screenOffset, float wallLength);
    void drawBrick (float x, float y, float w, float h);
    
private:
    float screenOffset_ = 0;
    
    vector<float> etherWall_;
    vector<vector<ofColor>> etherWallColor_;
    
    int     glowFor = 0;
    float   wallHeight = 300;
    float   wallLength_ = 0;
    float   brickWidth = 34.2;
    int     brickHeight = 16.3;
    int     numBricks = 0;
    float   floorOffset = -44;
    float   brickdysplacement = 0;
    
    int     bricksperscren = floor(ofGetScreenWidth() / brickWidth * 2) + 3;
    float   screenOffset = 0;
    float   screenWidth = ofGetScreenWidth();
    
    
    float   brickSize = 0.7;
    float   halfBrickSize = 0;
};

#endif /* G_EtherWall_hpp */
