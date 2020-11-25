//
//  Game.cpp
//
//  Created by Mortimer Pavlitski on 14/03/2018.
//

#include "Game.hpp"

Game::Game(GameController* gcPtr) :
    audio_(&world_, &currentLevel_, &player1_),
    player1_(gcPtr, &world_, &currentLevel_, &audio_, &gameWindow_),
    gameWindow_(&player1_),
    shardCounterIcon_(0, 0, nullptr, nullptr)
{
    gcPtr_ = gcPtr;
    
    ofSetFrameRate(30);
    ofSetFullscreen(false);
    ofDisableAntiAliasing();
    
    windowWidth_  = ofGetWindowWidth();
    windowHeight_ = ofGetWindowHeight();
    
    isCurrentLevelGenerated_ = false;
    
    // Add Ether
    world_.push_back({ 0, &audio_ , windowWidth_, windowHeight_, &nShards_, &switchLevelTo_});
    
    nShards_ = 0;
    
    font.load(Font::hylia, 24);
    switchLevelTo_ = -1;
    isFaded_ = true;
}

void Game::resized() {
    windowWidth_  = ofGetWindowWidth();
    windowHeight_ = ofGetWindowHeight();
    
    gameWindow_.updateWindowSize(windowWidth_, windowHeight_);
    
    for(int i = 0; i < world_.size(); i++) {
        world_[i].updateWindowSize(windowWidth_, windowHeight_);
    }
}

void Game::update() {
    float t = ofGetLastFrameTime();

    if (t > 0.1) {
        t = 0.1;
        ofLog() << t;
    }
    
    // Has Level Generated
    if(world_.size() > 0) {
        isCurrentLevelGenerated_ = world_[currentLevel_].getIsGenerated();
    } else {
        isCurrentLevelGenerated_ = false;
    }
    
    // Update Current Level
    world_[currentLevel_].update(t, gameWindow_.getX(), windowWidth_, fadeValue_);

    // calculate playerx1
    if(switchLevelTo_ == -1) {
        player1_.update(t);
    }
    
    // Level Switching (must be affter calculate player)
    if(switchLevelTo_ == -1 && player1_.getIsPortalID() >= 0 && player1_.getIsPortalID() != world_[currentLevel_].getPortalID())
    {
        switchLevelTo_        = player1_.getIsPortalID();
        isFaded_              = false;
    }

    if (isFaded_) {
        fadeValue_ += t * 100;
    } else {
        fadeValue_ -= t * 100;
    }
    
    if(fadeValue_ > 255) {
        fadeValue_ = 255;
    } else if (fadeValue_ < 0) {
        fadeValue_ = 0;
    }
    
    if(switchLevelTo_ >= 0 && fadeValue_ == 0) {
        //switch
        bool beenherebefore = false;

        for(auto l : world_) {
            if (l.getPortalID() == switchLevelTo_){
                beenherebefore = true;
            }
        }

        // if the level doesnt exsit make it
        if (!beenherebefore){
            // Add new overworld Level with that portal ID
            world_.push_back({ switchLevelTo_, &audio_, windowWidth_, windowHeight_, &nShards_, &switchLevelTo_ });
        }

        loadLevel(switchLevelTo_);
        player1_.respawn();
        
        switchLevelTo_      = -1;
        isFaded_            = true;
    }
    
    gameWindow_.updateScreenWindow(true);

    if(currentLevel_ == 0) {
        etherParticles.update(t, gameWindow_.getX(), player1_.getX(), player1_.getY());
    }
    
    audio_.update(t, player1_.getIsInPortal());
    
    shardCounterIcon_.update(t);
}

void Game::draw() {
    if(isCurrentLevelGenerated_) {
        // graphics attached to screen window movment
        {
            ofPushView();
            
            // move window
            ofTranslate(gameWindow_.getX(), windowHeight_ - gameWindow_.getY());
            
            //draw level
            world_[currentLevel_].draw(gameWindow_.getX(), gameWindow_.getY(), windowWidth_);
            
            //draw player
            if (switchLevelTo_ == -1) {
                player1_.draw();
            }
            
            if(currentLevel_ == 0)
                etherParticles.draw();
            
            ofPopView();
            
            // Draw Shard UI
            ofPushView();
            ofTranslate(10,40);
            shardCounterIcon_.draw();
            ofSetColor(255);
            font.drawString(to_string(nShards_), 30, 0);
            ofPopView();
        }
    }
    
    // Fade
    ofSetColor(0,0,0,255 - fadeValue_);
    ofDrawRectangle(0, windowHeight_, windowWidth_, -windowHeight_);
}

void Game::loadLevel(int levelID) {
    for(int i = 0; i < world_.size(); i++) {
        if (world_[i].getPortalID() == levelID){
            currentLevel_ = i;
            isCurrentLevelGenerated_ = world_[currentLevel_].getIsGenerated();
        }
    }
    
    audio_.loadlevel();
}



