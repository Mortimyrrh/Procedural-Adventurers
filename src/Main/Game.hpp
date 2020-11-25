//
//  Game.hpp
//
//  Created by Mortimer Pavlitski on 14/03/2018.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include "ofMain.h"

#include "PlayerEntity.hpp"
#include "Level.hpp"
#include "GameController.hpp"
#include "GameWindow.hpp"

#include "EtherParticle.hpp"
#include "Fonts.hpp"

#include "Audio.hpp"

class Game {
public:
    Game(GameController* gcPtr);
    ~Game(){};
    
    void resized();
    void update();
    void draw();
    void loadLevel(int levelID);
    
private:
    bool                    isCurrentLevelGenerated_;
    std::vector <Level>     world_;
    int                     currentLevel_;
    int                     switchLevelTo_; // -1 if no switch needed
    GameController*         gcPtr_;
    GameWindow              gameWindow_;
    PlayerEntity            player1_;
    
    float windowWidth_   = 0;
    float windowHeight_  = 0;
    
    int   nShards_; // Score Counter
    
    // Graphics
    EtherParticles      etherParticles;
    
    ofxTrueTypeFontUC   font;
    GO_Shard            shardCounterIcon_;
    
    // Fading
    bool                isFaded_;
    float               fadeValue_;     // 0 -> 255 fade state

    // Audio
    Audio   audio_;
};


#endif /* Game_hpp */
