//
//  GO_PlatformBase.cpp
//
//  Created by Mortimer Pavlitski on 21/04/2018.
//

#include "GO_PlatformBase.hpp"

GO_PlatformBase::GO_PlatformBase(IPlatformPhysics* physicsPtr, IPlatformGraphic* graphicPtr, float xPos, float yPos, float width, float height)
{
    physicsPtr_ = physicsPtr;
    graphicPtr_ = graphicPtr;
    
    graphicPtr_->setSize(width, height);
    setBounds(xPos, yPos, width, height);
}

GO_PlatformBase::~GO_PlatformBase() {
    physicsPtr_->IPlatformPhysics::~IPlatformPhysics();
    graphicPtr_->IPlatformGraphic::~IPlatformGraphic();
}

CollisionState GO_PlatformBase::getCollisionState(float xPos1, float yPos1, float xPos2, float yPos2, float width, float height) {

    // Collision pirortiy
    // Lower upper Left Right
    
    if(yPos1 + height >= getY() && yPos2 + height - 5 <= getY() &&
       xPos1 + width  >= getX() && xPos1 <= getX() + getW()) {
        return CollisionState::LowerEdge;
        
    } else if (yPos1 <= getY() + getH() && yPos2 + 5 >= lastYPos_ + getH() &&
               xPos1 + width >= getX() && xPos1 <= getX() + getW()) {
        return CollisionState::UpperEdge;
        
    } else if (xPos1 + width >= getX() && xPos2 + width - 5 <= getX() &&
               yPos1 + height >= getY() && yPos1 <= getY() + getH()) {
        return CollisionState::LeftEdge;

    } else if (xPos1 <= getX() + getW() && xPos2 + 5 >= getX() + getW() &&
               yPos1 + height >= getY() && yPos1 <= getY() + getH()) {
        return CollisionState::RightEdge;
        
    } else {
        return CollisionState::Nothing;
    }
}

void GO_PlatformBase::update(float timePassed) {
    graphicPtr_->update(timePassed);
    
    setVelocity(physicsPtr_->updatePhysics(timePassed));
    
    lastXPos_ = getX();
    lastYPos_ = getY();
}

void GO_PlatformBase::draw() {
    graphicPtr_->draw();
}
