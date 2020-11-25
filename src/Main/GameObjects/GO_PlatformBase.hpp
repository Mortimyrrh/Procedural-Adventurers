//
//  GO_PlatformBase.hpp
//
//  Created by Mortimer Pavlitski on 21/04/2018.
//

#ifndef GO_PlatformBase_hpp
#define GO_PlatformBase_hpp

#include <stdio.h>

#include "ofMain.h"
#include "GameObjectBase.hpp"

#include "PlatformComponents.hpp"

class GO_PlatformBase : public GameObjectBase {
public:
    GO_PlatformBase(IPlatformPhysics* physicsPtr, IPlatformGraphic* graphicPtr, float xPos, float yPos, float width, float height);
    ~GO_PlatformBase();
    
    CollisionState getCollisionState(float xPos1, float yPos1, float xPos2, float yPos2, float width, float height) override;
    
    void update(float timePassed) override;
    void draw() override;
    
private:
    float lastXPos_;
    float lastYPos_;
    
    IPlatformGraphic*   graphicPtr_;
    IPlatformPhysics*   physicsPtr_;
};

#endif /* GO_PlatformBase_hpp */
