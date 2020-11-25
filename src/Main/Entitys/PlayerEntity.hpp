//
//  PlayerEntity.hpp
//  PhysicsGameEngineTesting
//
//  Created by Mortimer Pavlitski on 24/01/2018.
//

#ifndef PlayerEntity_hpp
#define PlayerEntity_hpp

#include "ofMain.h"

#include <stdio.h>
#include <vector>

#include "GameController.hpp"
#include "Level.hpp"
#include "Audio.hpp"

class GameWindow;

class PlayerEntity {
public:
    PlayerEntity(GameController* gameControllerPtr,
                     std::vector<Level>* worldPtr,
                     int* currentLevelPtr,
                     Audio* audioPtr,
                     GameWindow* gameWindowPtr);
    
    ~PlayerEntity(){}
    
    void    respawn();
    void    update(float timeElapsed);
    void    draw();

    void    setPlayerPosition(float x, float y);
    
    float   getX();
    float   getY();
    float   getW();
    float   getH();
    
    float   getXVel();
    bool    getIsFacingRight();
    
    int     getIsPortalID();
    void    setIsPortalID(int id);
    bool    getIsInPortal();
    
    void    randHatColour();
    
private:
    /// Physics
    float   xPos_;
    float   yPos_;
    float   lastXPos_;
    float   lastYPos_;
    float   xVel_;
    float   yVel_;
    float   lastXVel_;
    float   lastYVel_;
    float   xAcc_;
    float   yAcc_;
    
    float   width_;
    float   height_;

    int     jumpTimeMax_;   // frames
    int     jumpTimer_;
    bool    isJumping_;
    
    bool    isOnPlatform_;
    bool    isFacingDown_;
    bool    isFacingRight_;
    
    /// Portal State
    int     isPortalID_;    // -1 if not in a portal
    bool    isInPortal_;
    
    /// Ptrs
    GameController*         gcPtr_;
    std::vector<Level>*     worldPtr_;
    int*                    currentLevelPtr_;
    GameObjectBase*         currentPlatform_;
    GameWindow*             gameWindowPtr_;
    Audio*                  audioPtr_;

    /// Graphics
    float                   hatSize_;
    ofColor                 hatColour_;
    bool                    lastHatState_;
};

#endif /* PlayerEntity_hpp */
