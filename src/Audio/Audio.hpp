//
//  Audio.hpp
//
//  Created by Mortimer Pavlitski on 07/04/2018.
//

#ifndef Audio_hpp
#define Audio_hpp

#include <stdio.h>
#include "ofxPDSP.h"

#include "Scales.hpp"
#include "Synths.hpp"

class PlayerEntity;
class GO_Shard;
class Level;

class Audio {
public:
    Audio(std::vector <Level>* worldPtr, int* currentLevelPtr, PlayerEntity* player1Ptr);
    ~Audio();
    
    void update(float timeElapsed, bool isPlayerInPortal);
    void loadlevel();
    
    void playJumpSound();
    void playFallSound();
    void playShardSound();
    void playPortalSound();

private:
    // Game Pointers
    std::vector <Level>*    worldPtr_;
    int*                    currentLevelPtr_;
    PlayerEntity*           player1Ptr_;
    
    // Audio Engine
    ofxPDSPEngine           engine_;
    bool                    quantize_;
    float                   quantime_;
    
    // Mixing
    pdsp::Amp               masterMixL_;
    pdsp::Amp               masterMixR_;
    ofxPDSPValue            masterMixCtrl_;

    pdsp::Amp               etherMixL_;
    pdsp::Amp               etherMixR_;
    ofxPDSPValue            etherMixCtrl_;
    
    pdsp::Amp               overWolrdMixL_;
    pdsp::Amp               overWolrdMixR_;
    ofxPDSPValue            overWolrdMixCtrl_;
    
    pdsp::Amp               soundEffectsMixL_;
    pdsp::Amp               soundEffectsMixR_;
    ofxPDSPValue            soundEffectsMixCtrl_;

    // Ether
    const int               nOsc_ = 14;
    pdsp::VAOscillator      osc_[14];
    pdsp::Amp               oscAmp_[14];
    pdsp::Panner            oscPan_[14];
    pdsp::LFOPhazor         lfoPitch_[14];
    pdsp::LFOPhazor         lfoAmp_[14];
    
    ofxPDSPValue            pitchCtrl_[14];
    ofxPDSPValue            ampCtrl_[14];
    ofxPDSPValue            panCtrl_[14];
    
    float etherPhase_;
    float phaseTime_;
    float freqWidth_;
    float centerFreq_;
    
    float freqWidthMin_;
    float freqWidthMax_;
    
    // OverWolrd
    FMSynth                 fmSynth_;

    vector<pdsp::Sequence>  melodySeqs_;
    int                     melodySeqsPart_;

    pdsp::SampleBuffer      kickSample_;
    pdsp::Sampler           kickPlayer_;
    pdsp::TriggerControl    kickTriger_;
    vector<pdsp::Sequence>  kickSeqs_;
    
    // Sound Effects
    // Jump
    pdsp::SampleBuffer      jumpSample_;
    pdsp::Sampler           jumpPlayer_;
    pdsp::TriggerControl    jumpTriger_;
    
    // Jump
    pdsp::SampleBuffer      fallSample_;
    pdsp::Sampler           fallPlayer_;
    pdsp::TriggerControl    fallTriger_;
    
    // Shard
    pdsp::SampleBuffer      shardSample_;
    pdsp::Sampler           shardPlayer_;
    pdsp::TriggerControl    shardTriger_;
    
    // Shuffle
    pdsp::GrainCloud        shuffleCloud_;
    pdsp::SampleBuffer      shuffleSample_;
    pdsp::Amp               shuffleMixL_;
    pdsp::Amp               shuffleMixR_;
    ofxPDSPValue            shuffleCtrl_;
    pdsp::PatchNode         shuffleBufferXPos_;
    pdsp::PatchNode         shuffleJitter_;

    // Portal
    pdsp::SampleBuffer      portalSample_;
    pdsp::Sampler           portalPlayer_;
    pdsp::TriggerControl    portalTriger_;
    
};

#endif /* Audio_hpp */
