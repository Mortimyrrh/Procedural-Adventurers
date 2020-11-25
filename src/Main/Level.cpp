//
//  Level.cpp
//
//  Created by Mortimer Pavlitski on 11/03/2018.
//

#include "Level.hpp"

Level::Level(int portalID, Audio* audioPtr, float windowWidth, float windowHeight, int* nShardsPtr, int* switchLevelToPtr) {
    updateWindowSize(windowWidth, windowHeight);
    
    //  Default states
    portalID_               = portalID;
    isGenerated_            = false;
    isLevelAudioGenerated_  = false;
    nShardsPtr_             = nShardsPtr;
    audioPtr_               = audioPtr;
    switchLevelToPtr_       = switchLevelToPtr;
    difficulty_             = portalID;
    
    genirateMusic();
}

Level::~Level(){
    gameObjects_.clear();
}

void Level::buildEther(){
    /// Objects
    gameObjects_.emplace_back(new GO_PlatformBase(new PP_Static, new PG_Ether, 0, 0, 8000, 40));
    
    for(int i=0; i < 11; i++){
        gameObjects_.emplace_back(new GO_Portal(float(500 + (i*700)), 40, i + 1, i * 3, nShardsPtr_, switchLevelToPtr_, audioPtr_));
    }
}

void Level::buildOverworld(){
    /// Graphics
    background_.resized(windowWidth_, windowHeight_);
    background_.generate();
    
    /// Objects
    int     nPlatforms = 10 + floor(difficulty_ * 5);
    
    // curent platform
    float   x = 0;
    float   y = 0;
    float   w = 0;
    float   h = 0;
    
    int     nShards = 0;
    int     maxShards = 5;

    int     yNoiseInc = 0;
    bool    isPhase = false;
    
    // Golden rules of level geniration
    // 1. must be playable
    // 2. must have at least 3 collectables
    
    for(int i = 0; i <= nPlatforms || nShards < 3; i++) {
        isPhase = !isPhase;
        
        // Genirate Platform
        if(i == 0) {
            // Landing platform
            w = 250;
            h = 40;
            gameObjects_.emplace_back(new GO_PlatformBase(new PP_Static, new PG_MudWithGrass(background_.getColour()), x, y, w, h));
        } else if(i == nPlatforms) {
            w = 300;
            x += 100;
            // Portal Platform
            gameObjects_.emplace_back(new GO_PlatformBase(new PP_Static, new PG_WhiteGrass, x, y, w, h));
            gameObjects_.emplace_back(new GO_Portal(x, y + 30, 0, 0, nShardsPtr_, switchLevelToPtr_, audioPtr_));
        } else {
            // Mid level Platforms
    
            // Random width
            w = ofRandom(300 - ((difficulty_) * 25), 600 - ((difficulty_) * 30));
            
            // Gap
            float m = ofRandom(100 + (5 * difficulty_), 200);
            float a = ofRandom(-PI/2, PI/2);
    
            x += 50 + cos(a) * m * 2;
            y += sin(a) * m * 0.5;
            
            if(y > 400) {
                y = 400;
            } else if (y < -400) {
                y = -400;
            }
            
            // if plat is above
            bool isAbove = false;
            if (a > -PI/4) {
                // enable jump though on next platform
                isAbove = true;
            }
            
            // platform
            if(ofRandom(20) > 15 + ((10 - difficulty_) * 0.5)) {
                bool isUp = ofRandom(2);
                
                // vertical
                if (isPhase) {
                    if (isUp) {
                        y += 200;
                    } else {
                        y -= 200;
                    }
                }
                
                gameObjects_.emplace_back(new GO_PlatformBase(new PP_VerticalMoving(isPhase, isUp), new PG_BlueBox, x, y, w, h));
            
                if (!isPhase) {
                    if (isUp) {
                        y += 200;
                    } else {
                        y -= 200;
                    }
                }
                            
            } else if (ofRandom(20) > 15 + ((10 - difficulty_) * 0.5)) {
                
                if (isPhase) {
                    x += 300;
                }
                
                gameObjects_.emplace_back(new GO_PlatformBase(new PP_HorizontalMoving(isPhase), new PG_BlueBox, x, y, w, h));
                
                if (!isPhase) {
                    x += 300;
                }
                
            } else {
                //static
                if(ofRandom(10) > 0.7) {
                    gameObjects_.emplace_back(new GO_PlatformBase(new PP_Static, new PG_MudWithGrass(background_.getColour()), x, y, w, h));
                } else {
                    gameObjects_.emplace_back(new GO_PlatformBase(new PP_Static, new PG_GrassWithFlower(background_.getColour()), x, y, w, h));
                }
            }
            
            
            // chance of collatable
            if (nShards < maxShards && nShards < i / maxShards) {
                // place shard
                if(ofRandom(0, 5 + 10 + difficulty_) > 4) {
                    // higher
                    gameObjects_.emplace_back(new GO_Shard(x + (w * 0.5), y + 230, nShardsPtr_, audioPtr_));
                } else {
                    // on platform
                    gameObjects_.emplace_back(new GO_Shard(x + (w * 0.5), y + 80, nShardsPtr_, audioPtr_));
                }
                nShards++;
            }
        }
        
        // Next platform start pos
        x += w;
    }
};

void Level::genirateLevel() {
    // Level and graphics
    if (portalID_ > 0)
        buildOverworld();   // Normal Level
    else if (portalID_ == 0)
        buildEther();       // Ether Portals to overworld
    
    for(GameObjectBase* p : gameObjects_){
        // update all
        p->update(0.001);
    }
    
    isGenerated_ = true;
}

void Level::update(float t, float xOffset, float windowWidth, float fadeValue) {
    fadeValue_ = fadeValue;
    
    // Has Level Generated
    if (isGenerated_) {
        // Update GameObjects
        for(GameObjectBase* p : gameObjects_){
            // if on screen update
            if (p->getX() + p->getW() >= -xOffset - 100 && p->getX() <= -xOffset + windowWidth + p->getW()) {
                p->update(t);
            }
        }
    } else {
        genirateLevel();
    }
}

void Level::draw(float xOffset, float yOffset, float windowWidth) {
    ofPushView();

    if(portalID_ != 0) {
        if(portalID_ != 11) {
            ofBackground(background_.getSkyColour());
        }
        background_.draw(xOffset, yOffset, windowWidth);
    } else {
        ofBackground(EtherColourPallet::DarkPurple);
    }
    
    for(GameObjectBase* p : gameObjects_){
        
        // if on screen draw
        if (p->getX() + p->getW() >= -xOffset - 100 && p->getX() <= -xOffset + windowWidth + p->getW())
        {
            ofPushView();
                ofTranslate(p->getX(), -p->getY());
                p->draw();
            ofPopView();
        }
    }
    
    ofPopView();
}

void Level::genirateMusic() {
    // Audio
    key_    = ofRandom(24);
    scale_  = floor(ofRandom(0, 3.3));
    tempo_  = ofRandom(80.0f + difficulty_ * 6, 160.0f + difficulty_ * 3);
    
    attack_ = ofRandom(0, 300);
    hold_   = ofRandom(0, 300);
    release_= ofRandom(0, 500);

    // Melody Seqencer
    melody_seqs_.resize(5); //2?
    for(int i = 0; i < 5; i++) {
        melody_seqs_[i].set( {
            {   getRandomTrig(0.9),
                getRandomTrig(0.9),
                getRandomTrig(0.9),
                getRandomTrig(0.9),
                getRandomTrig(0.9),
                getRandomTrig(0.9),
                getRandomTrig(0.9),
                getRandomTrig(0.9), }, // triggers
            {   getRandNote(key_, scale_),
                getRandNote(key_, scale_),
                getRandNote(key_, scale_),
                getRandNote(key_, scale_),
                getRandNote(key_, scale_),
                getRandNote(key_, scale_),
                getRandNote(key_, scale_),
                getRandNote(key_, scale_) } },   // pitch values
                            floor(ofRandom(4, 9)), 1.0 );          // time division (1/8th), sequence length in bars (1 bar)
    }
    
    // Kick Seqencer
    kick_seqs_.resize(1);
    kick_seqs_[0].set( { 1.0f,
        getRandomTrig(0.25),
        getRandomTrig(0.5),
        getRandomTrig(0.25),
        getRandomTrig(0.95),
        getRandomTrig(0.25),
        getRandomTrig(0.35),
        getRandomTrig(0.7) }, 8.0f, 1.0f );
    
    isLevelAudioGenerated_ = true;
}

void Level::updateWindowSize(float windowWidth, float windowHeight) {
    windowWidth_  = windowWidth;
    windowHeight_ = windowHeight;
}

//

bool Level::getIsGenerated() {
    return isGenerated_;
}

int  Level::getPortalID() {
    return portalID_;
}

std::vector<GameObjectBase*>* Level::getGameObjectsPtr() {
    return &gameObjects_;
}

vector<pdsp::Sequence> Level::getMelodySeqs() {
    return melody_seqs_;
}

vector<pdsp::Sequence> Level::getKickSeqs() {
    return kick_seqs_;
}

float Level::getAttack() {
    return attack_;
}

float Level::getHold() {
    return hold_;
}

float Level::getRelease() {
    return release_;
}

bool Level::getIsLevelAudioGenerated() {
    return isLevelAudioGenerated_;
}

float Level::getTempo() {
    return tempo_;
}
