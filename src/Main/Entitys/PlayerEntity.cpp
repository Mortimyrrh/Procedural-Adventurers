//
//  PlayerEntity.cpp
//  PhysicsGameEngineTesting
//
//  Created by Mortimer Pavlitski on 24/01/2018.
//

#include "PlayerEntity.hpp"
#include "GameWindow.hpp"

PlayerEntity::PlayerEntity(GameController* gameControllerPtr,
                                   std::vector<Level>* worldPtr,
                                   int* currentLevelPtr,
                                   Audio* audioPtr,
                                   GameWindow* gameWindowPtr)
{
    gcPtr_                  = gameControllerPtr;
    worldPtr_               = worldPtr;
    currentLevelPtr_        = currentLevelPtr;
    audioPtr_               = audioPtr;
    gameWindowPtr_          = gameWindowPtr;
    
    jumpTimeMax_    = 3;
    width_          = 50;
    height_         = 100;
    isFacingRight_  = false;
    
    hatSize_        = 0.8;
    lastHatState_   = false;
    randHatColour();

    respawn();
}

void PlayerEntity::respawn() {
    setPlayerPosition(50,50);
    
    xAcc_       = 0;
    yAcc_       = 0;
    xVel_       = 0;
    yVel_       = 0;
    lastXVel_   = 0;
    lastYVel_   = 0;
    
    isJumping_      = false;
    isOnPlatform_   = false;
    isFacingDown_   = true;
    
    gameWindowPtr_->updateScreenWindow(false);
}


void PlayerEntity::update(float timeElapsed) {
    // Random hat colour
    if(gcPtr_->getIsSpacePressed() && !lastHatState_) {
        randHatColour();
    }
    
    lastHatState_ = gcPtr_->getIsSpacePressed();
    
    // Calculate Acceleration
    xAcc_ = 0;
    yAcc_ = 0;
    
    xVel_ = 0;
    yVel_ = 0;
    
    // Input Control
    if (gcPtr_->getIsUpPressed() && isOnPlatform_ && isFacingDown_){
        //startJump
        isJumping_ = true;
        jumpTimer_ = 0;
        audioPtr_->playJumpSound();
    }
    
    //Jumping
    if (isJumping_) {
        jumpTimer_ ++;
    }
    
    if (jumpTimer_ >= jumpTimeMax_) {
        jumpTimer_ = 0;
        isJumping_ = false;
    }
    
    if (jumpTimer_ < jumpTimeMax_ && isJumping_) {
        yVel_ += 18;
    } else {
        isJumping_ = false;
    }
    
    if (gcPtr_->getIsLeftPressed())
        xAcc_ += -150; //120
    
    if (gcPtr_->getIsRightPressed())
        xAcc_ += 150; //120
    
    
    // Gravity
    if (currentPlatform_ == nullptr)
        yAcc_ += -80;
    
    
    // Calculate Velocity
    if(currentPlatform_ != nullptr){
        xVel_ += lastXVel_ * 0.83; //83
        yVel_ += 0;
    } else {
        xVel_ += lastXVel_ * 0.86; //86
        yVel_ += lastYVel_ * 0.99;
        
    }
    
    // V = U + (T * A)
    xVel_ += timeElapsed * xAcc_;
    yVel_ += timeElapsed * yAcc_;
    
    if (xVel_ > 90)
        xVel_ = 90;
    
    if (xVel_ < -90)
        xVel_ = -90;
    
    if (yVel_ > 100)
        yVel_ = 100;
    
    if (yVel_ < -100)
        yVel_ = -100;
    
    // Set position
    xPos_ += xVel_;
    yPos_ += yVel_;
    
    // account for moving platforms
    if(currentPlatform_ != nullptr) {
        xPos_ += currentPlatform_->getVelocity().x;
        yPos_ += currentPlatform_->getVelocity().y;
    }
    
    /// Colition detection
    
    isOnPlatform_       = false;
    isInPortal_         = false;
    currentPlatform_    = nullptr;
    isPortalID_         = -1;
    
    for(int i = 0; i < ((*worldPtr_)[*currentLevelPtr_].getGameObjectsPtr())->size(); i++)
       
    {
        GameObjectBase* gameObjPtr = ((*worldPtr_)[*currentLevelPtr_].getGameObjectsPtr())->operator[](i);
        
        CollisionState collisionState = gameObjPtr->getCollisionState(xPos_, yPos_, lastXPos_, lastYPos_, width_, height_);
        
        switch (collisionState) {
            case CollisionState::UpperEdge:
                isOnPlatform_       = true;
                yPos_               = gameObjPtr->getY()+gameObjPtr->getH();
                yVel_               = 0;
                currentPlatform_    = gameObjPtr;
                break;
                
            case CollisionState::LowerEdge:
                yPos_               = gameObjPtr->getY()-height_;
                yVel_               = -1;
                isJumping_          = false;
                break;
                
            case CollisionState::LeftEdge:
                xPos_               = gameObjPtr->getX()-width_;
                xVel_               = 0;
                break;
                
            case CollisionState::RightEdge:
                xPos_               = gameObjPtr->getX()+gameObjPtr->getW();
                xVel_               = 0;
                break;
                
            case CollisionState::InPortal:
                if (dynamic_cast<GO_Portal*>(gameObjPtr)->getIsPortalActive()) {
                    isPortalID_ = dynamic_cast<GO_Portal*>(gameObjPtr)->getPortalID();
                }
                isInPortal_     = true;
                break;

            default:
                break;
        }
    }

    // fall from level respawn
    if (yPos_ < -2000) {
        respawn();
        audioPtr_->playFallSound();
    }
    
    // Save Direction of travel
    if(yVel_ > 0 )
        isFacingDown_  = false;
    
    if(yVel_ < 0 )
        isFacingDown_  = true;
    
    if(xVel_ > 0 )
        isFacingRight_  = true;
    
    if(xVel_ < 0 )
        isFacingRight_  = false;
    
    // save old pos and vel
    lastXPos_ = xPos_;
    lastYPos_ = yPos_;
    
    lastXVel_ = xVel_;
    lastYVel_ = yVel_;
}

void PlayerEntity::draw() {
    ofPushView();
    ofTranslate(xPos_, -yPos_);
    
    float bodyCenter = width_ * 0.5;
    
    //body
    ofSetColor(60);
    ofDrawRectangle(0, 0, width_, -height_);
    
    //hat
    ofSetColor(hatColour_);
    ofDrawTriangle(bodyCenter, - (height_ * 1.15 ), bodyCenter + (width_ * hatSize_), -((height_*0.9)), (bodyCenter - (width_ * hatSize_)), -((height_*0.9)));
    
    //midle
    ofSetColor(190);
    float padding = 8;
    ofDrawRectRounded(padding, -padding, width_ - (padding*2), - (height_*0.5) + (padding * 2), 8);
    
    ofSetColor(30);
    
    //eyes
    ofDrawLine(bodyCenter-(width_*0.15), -((height_*0.75)), bodyCenter-(width_*0.35), -((height_*0.85)));
    ofDrawLine(bodyCenter+(width_*0.15), -((height_*0.75)), bodyCenter+(width_*0.35), -((height_*0.85)));
    
    
    ofSetColor(30);
    
    float offset;
    if(lastYVel_ >= 0.2) {
        offset = 0.2f;
    } else {
        offset = 0.0f;
    }
    
    // normal feature
    ofDrawBezier(bodyCenter-(width_*0.0), -(height_*0.7),
                 bodyCenter-(width_*0.2), -(height_*0.55),
                 bodyCenter-(width_*0.0), -(height_*0.62),
                 bodyCenter-(width_*0.2), -(height_*0.58));

    ofDrawBezier(bodyCenter+(width_*0.0), -(height_*0.7),
                 bodyCenter+(width_*0.2), -(height_*0.55),
                 bodyCenter+(width_*0.0), -(height_*0.62),
                 bodyCenter+(width_*0.2), -(height_*0.58));
    
    ofPopView();
}

//

void PlayerEntity::setPlayerPosition(float x, float y) {
    xPos_ = x - (width_ * 0.5);
    yPos_ = y;
    
    lastXPos_ = xPos_;
    lastYPos_ = yPos_;
}

float PlayerEntity::getX() {
    return xPos_;
}

float PlayerEntity::getY() {
    return yPos_;
}

float PlayerEntity::getW() {
    return width_;
}

float PlayerEntity::getH() {
    return height_;
}

float PlayerEntity::getXVel() {
    return xVel_;
}

bool PlayerEntity::getIsFacingRight() {
    return isFacingRight_;
}

int PlayerEntity::getIsPortalID() {
    return isPortalID_;
}

void PlayerEntity::setIsPortalID(int id) {
    isPortalID_ = id;
}

bool PlayerEntity::getIsInPortal() {
    return isInPortal_;
}

void PlayerEntity::randHatColour() {
    hatColour_ = ofColor::fromHsb(ofRandom(255), ofRandom(255), ofRandom(100, 255));
}
