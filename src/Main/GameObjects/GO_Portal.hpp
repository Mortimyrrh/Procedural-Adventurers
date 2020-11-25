//
//  GO_Portal.hpp
//  TheProceduralAdventurers
//
//  Created by Mortimer Pavlitski on 23/04/2018.
//

#ifndef GO_Portal_hpp
#define GO_Portal_hpp

#include <stdio.h>

#include "ofMain.h"
#include "GameObjectBase.hpp"
#include "G_Portal.hpp"
#include "Audio.hpp"

#include "ofxTrueTypeFontUC.h"

class GO_Portal : public GameObjectBase {
public:
    GO_Portal(float xPos, float yPos, int portalID, int lockLevel, int* nShardsPtr, int* switchLevelToPtr, Audio* audioPtr);
    ~GO_Portal();
    
    CollisionState getCollisionState(float xPos1, float yPos1, float xPos2, float yPos2, float width, float height) override;
    void    update(float timePassed) override;
    void    draw() override;

    void    updateSpeed(float timePassed);

    int     getPortalID();
    bool    getIsPortalActive();
    
    
private:
    int     portalID_;
    bool    isPortalActive_;
    bool    isPortalUnlocked_;
    int     lockLevel_;         // score reqired to go though portal
    int*    nShardsPtr_;        // Score Counter

    float   speed_;
    float   portalSpeedMin_;
    
    bool    isPlayerInPortal_;
    int*    switchLevelToPtr_;
    
    Audio*  audioPtr_;
    
    /// Graphics
    ofxTrueTypeFontUC   font;
    G_Portal            portalGraphic { portal::iching };
};
    
#endif /* GO_Portal_hpp */
