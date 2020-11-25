//
//  GameObjectBase.hpp
//
//  Created by Mortimer Pavlitski on 15/04/2018.
//

#ifndef GameObjectBase_hpp
#define GameObjectBase_hpp

#include <stdio.h>
#include "ofMain.h"
#include "IPlatformPhysics.hpp"
#include "Audio.hpp"

enum class CollisionState {
    Nothing,
    UpperEdge,
    LowerEdge,
    LeftEdge,
    RightEdge,
    InPortal
};

class GameObjectBase {
public:
    GameObjectBase();
    ~GameObjectBase();
    
    virtual void update(float timePassed) = 0;
    virtual void draw() = 0;
    virtual CollisionState getCollisionState(float xPos1, float yPos1, float xPos2, float yPos2, float width, float height) = 0;
    
    void    setBounds(float x, float y, float w, float h);
    void    setVelocity(Vector vel);
    Vector  getVelocity();
    void    updatePosition();
    
    virtual float getX();
    virtual float getY();
    virtual float getW();
    virtual float getH();
    
    void setX(float xPos);
    void setY(float yPos);
    void setW(float width);
    void setH(float height);
    
protected:
    float   xPos_;          // current x position
    float   yPos_;          // current y position
    float   width_;         // current width
    float   height_;        // current height
    
    Vector  vel_;           // velocity
};

#endif /* GameObjectBase_hpp */
