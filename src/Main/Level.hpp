//
//  Level.hpp
//
//  Created by Mortimer Pavlitski on 11/03/2018.
//

#ifndef Level_hpp
#define Level_hpp

#include <stdio.h>
#include "ofMain.h"

#include "GameObjectBase.hpp"
#include "GameObjects.hpp"

#include "G_Background.hpp"
#include "G_EtherWall.hpp"

#include "Scales.hpp"
#include "ofxPDSP.h"

class Audio;

class Level {
public:    
    Level(int portalID, Audio* audioPtr, float windowWidth, float windowHeight, int* nShardsPtr, int* switchLevelToPtr);
    ~Level();
    
    void    genirateLevel();
    void    genirateMusic();

    void    update(float t, float screenX, float windowWidth, float fadeValue);
    void    draw(float xOffset, float yOffset, float windowWidth);

    void    updateWindowSize(float windowWidth, float windowHeight);
    
    bool    getIsGenerated();
    int     getPortalID();
    std::vector<GameObjectBase*>*   getGameObjectsPtr();
    
    vector<pdsp::Sequence>          getMelodySeqs();
    vector<pdsp::Sequence>          getKickSeqs();
    float   getAttack();
    float   getHold();
    float   getRelease();
    bool    getIsLevelAudioGenerated();
    float   getTempo();
    

    
private:
    // Functions
    void    buildEther();
    void    buildOverworld();
    
    // States
    int     portalID_;
    bool    isGenerated_;
    int*    nShardsPtr_;
    float   fadeValue_;
    int*    switchLevelToPtr_;
    
    // Data
    float   difficulty_;  // 0 -> 10;
    std::vector <GameObjectBase*> gameObjects_;

    // Audio
    Audio*                  audioPtr_;
    vector<pdsp::Sequence>  melody_seqs_;
    vector<pdsp::Sequence>  kick_seqs_;
    float                   attack_;
    float                   hold_;
    float                   release_;
    
    bool                    isLevelAudioGenerated_;
    int                     key_;
    int                     scale_;
    float                   tempo_;
    
    // Background
    G_Background            background_;
    
    // WindowSize
    float  windowWidth_;
    float  windowHeight_;
};


#endif /* Level_hpp */
