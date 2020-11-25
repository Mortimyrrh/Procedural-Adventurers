//
//  G_EtherWall.cpp
//
//  Created by Mortimer Pavlitski on 02/05/2018.
//

#include "G_EtherWall.hpp"

G_EtherWall::G_EtherWall() {
    ofSeedRandom();
    
    float r = + ofRandom(1000);
    for (int i = 0; i < 10000; i++){
        etherWall_.push_back(ofNoise((i * 0.05) + r) - 0.3);
    }
    
    ofSeedRandom();
    
    for (int i = 0; i < 10000; i++) {
        vector<ofColor> newColum;
        for (int j = 0; j < 10; j++) {
            //Ether Brick looking
            newColum.push_back(ofColor(127 + (ofSignedNoise(i * 0.01 + 100) * 100) + (ofSignedNoise(j * 0.01 + 100) * 50) + ofRandom(10),
                                       21  + ofRandom(10, 20),
                                       133 + (ofSignedNoise(i * 0.01 + 400) * 50) + (ofSignedNoise(j * 0.01 + 400) * 100) + ofRandom(3)));
        }
        etherWallColor_.push_back(newColum);
    }
}

G_EtherWall::~G_EtherWall() {
    
}

void G_EtherWall::draw(float screenOffset, float wallLength) {
    wallLength_ = wallLength;
    screenOffset_ = screenOffset;
    
    ofPushView();
    ofTranslate(screenOffset, 0);
    
    halfBrickSize = brickSize * 0.5;
    ofSetLineWidth(4);
    
    int brickindex = 0;
    
    bool isOdd;
    bool isDisplaced;
    
    int jinit = 0;
    
    for (int i = 0; i < etherWall_.size(); i++)
    {
        if(wallLength_ >= i * brickWidth * 0.5 + brickWidth)
        {
            numBricks = floor(wallHeight * etherWall_[i] / brickHeight);
            
            if (i % 2 == 1) {
                isOdd = true;
                jinit = 1;
            } else {
                isOdd = false;
                jinit = 0;
            }
            
            for(int j = jinit; j < numBricks; j+= 2) {
                if (j % 2 == 1)
                    brickdysplacement = - brickWidth * 0.25;
                else
                    brickdysplacement = + brickWidth * 0.25;
                
                if (isOdd) {
                    //is odd
                    ofSetColor(etherWallColor_[i][j]);
                    drawBrick((i * brickWidth * 0.5) + brickdysplacement - screenOffset_ , floorOffset - (j * brickHeight), brickWidth, - brickHeight);
                } else {
                    //is even
                    ofSetColor(etherWallColor_[i][j]);
                    drawBrick((i * brickWidth * 0.5) - (brickWidth * 0.5) + brickdysplacement - screenOffset_ , floorOffset - (j * brickHeight), brickWidth, - brickHeight);
                }
                
            }
        }
    }
    
    ofFill();
    ofPopView();
}

void G_EtherWall::drawBrick (float x, float y, float w, float h) {
    ofDrawRectangle(x , y , w * brickSize, h  * brickSize);
}


