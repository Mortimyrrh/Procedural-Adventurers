//
//  Audio.cpp
//
//  Created by Mortimer Pavlitski on 07/04/2018.
//

#include "Audio.hpp"

#include "PlayerEntity.hpp"
#include "GO_Shard.hpp"
#include "Level.hpp"

Audio::Audio(std::vector <Level>* worldPtr, int* currentLevelPtr, PlayerEntity* player1Ptr) {
    worldPtr_           = worldPtr;
    currentLevelPtr_    = currentLevelPtr;
    player1Ptr_         = player1Ptr;
    
    // Audio engine setup
    engine_.score.setTempo(120.0f);
    engine_.score.sections.resize(2);
    
    engine_.listDevices();
    engine_.setOutputDeviceID(1);  // AUDIO OUTPUT DEVICE!!!!!
    engine_.setup(44100, 512, 3);
    
    quantize_ = true;
    quantime_ = 1.0/4.0;
    
    // Mixer
    // Master
    masterMixCtrl_.setv(1.0f);
    masterMixCtrl_ >> masterMixL_.in_mod();
    masterMixCtrl_ >> masterMixR_.in_mod();
    masterMixL_.out_signal() >> engine_.audio_out(0);
    masterMixR_.out_signal() >> engine_.audio_out(1);

    // Ether
    etherMixCtrl_.setv(1.0f);
    etherMixCtrl_.enableSmoothing(500.0f);
    etherMixCtrl_ >> etherMixL_.in_mod();
    etherMixCtrl_ >> etherMixR_.in_mod();
    etherMixL_.out_signal() >> masterMixL_.in_signal();
    etherMixR_.out_signal() >> masterMixR_.in_signal();

    // OverWorld
    overWolrdMixCtrl_.setv(1.0f);
    overWolrdMixCtrl_.enableSmoothing(500.0f);
    overWolrdMixCtrl_ >> overWolrdMixL_.in_mod();
    overWolrdMixCtrl_ >> overWolrdMixR_.in_mod();
    overWolrdMixL_.out_signal() >> masterMixL_.in_signal();
    overWolrdMixR_.out_signal() >> masterMixR_.in_signal();

    // Sound Effects
    soundEffectsMixCtrl_.setv(0.25f);
    soundEffectsMixCtrl_ >> soundEffectsMixL_.in_mod();
    soundEffectsMixCtrl_ >> soundEffectsMixR_.in_mod();
    soundEffectsMixL_.out_signal() >> masterMixL_.in_signal();
    soundEffectsMixR_.out_signal() >> masterMixR_.in_signal();
    
    // Ether setup
    etherPhase_     = 0;
    phaseTime_      = 60.0f;
    
    freqWidthMin_   = 0.1f;
    freqWidthMax_   = 48.0f;
    
    freqWidth_      = freqWidthMax_;
    centerFreq_     = 58.0f;
    
    for (int i = 0; i < nOsc_; i++) {
        pitchCtrl_[i].setv(0.0f);
        pitchCtrl_[i].enableSmoothing(30);
        pitchCtrl_[i] >> osc_[i].in_pitch();
        
        ampCtrl_[i].setv(0.0f);
        ampCtrl_[i].enableSmoothing(50);
        ampCtrl_[i] >> oscAmp_[i].in_mod();
        
        panCtrl_[i].setv(0.0f);
        panCtrl_[i].enableSmoothing(20);
        panCtrl_[i] >> oscPan_[i].in_pan();
        
        osc_[i].out_sine() * 0.1f >> oscAmp_[i].in_signal();
        oscAmp_[i].out_signal() >> oscPan_[i].out_0() >> etherMixL_.in_signal();
        
        osc_[i].out_sine() * 0.1f >> oscAmp_[i].in_signal();
        oscAmp_[i].out_signal() >> oscPan_[i].out_0() >> etherMixR_.in_signal();
    }
    
    
    // OverWorld setup
    // SineSynth
    engine_.score.sections[0].out_trig(0)  >> fmSynth_.in("trig");
    engine_.score.sections[0].out_value(1) >> fmSynth_.in("pitch");
    engine_.score.sections[0].out_value(1).enableSmoothing(100.0f);
    fmSynth_ * dB(-6.0f) >> overWolrdMixL_.in_signal();
    fmSynth_ * dB(-6.0f) >> overWolrdMixR_.in_signal();
    
    // SineSynth Seqencer
    melodySeqs_.resize(5);
    
    // Kick
    kickSample_.setVerbose(true);
    kickSample_.load(ofToDataPath( "samples/dsp808Kick.wav" ));
    kickSample_.normalize();
    kickPlayer_.addSample(&kickSample_, 0);
    kickPlayer_.out_signal() * dB(-16.0f) >> overWolrdMixL_.in_signal();
    kickPlayer_.out_signal() * dB(-16.0f) >> overWolrdMixR_.in_signal();
    kickTriger_.out_trig() >> kickPlayer_.in_trig();
    kickTriger_.off();

    // Kick Seqencer
    engine_.score.sections[1].out_trig(0)  >> kickPlayer_.in_trig();
    kickSeqs_.resize(1);
    kickSeqs_[0].set( { 1.0f,
                        getRandomTrig(0.25),
                        getRandomTrig(0.5),
                        getRandomTrig(0.25),
                        getRandomTrig(0.95),
                        getRandomTrig(0.25),
                        getRandomTrig(0.35),
                        getRandomTrig(0.7) }, 8.0f, 1.0f );
    
    
    // Assigning sequences to sections
    engine_.score.sections[0].clearOnChange(true);
    
    for(int i = 0; i < 1; ++i) {
        engine_.score.sections[0].setCell(i, &melodySeqs_[i], pdsp::Behavior::Loop );
        engine_.score.sections[1].setCell(i, &kickSeqs_[i], pdsp::Behavior::Loop );
    }
    
    // Sound Effects
    // Jump
    jumpSample_.setVerbose(true);
    jumpSample_.load(ofToDataPath( "samples/Jump3.wav" ));
    jumpSample_.normalize();
    
    jumpPlayer_.addSample(&jumpSample_, 0);
    jumpPlayer_.out_signal() * dB(-20.0f) >> soundEffectsMixL_.in_signal();
    jumpPlayer_.out_signal() * dB(-20.0f) >> soundEffectsMixR_.in_signal();
    
    jumpTriger_.out_trig() >> jumpPlayer_.in_trig();
    jumpTriger_.off();

    // Fall
    fallSample_.setVerbose(true);
    fallSample_.load(ofToDataPath( "samples/FallSound.wav" ));
    fallSample_.normalize();
    
    fallPlayer_.addSample(&fallSample_, 0);
    fallPlayer_.out_signal() * dB(-2.0f) >> soundEffectsMixL_.in_signal();
    fallPlayer_.out_signal() * dB(-2.0f) >> soundEffectsMixR_.in_signal();
    
    fallTriger_.out_trig() >> fallPlayer_.in_trig();
    fallTriger_.off();
    
    // Shard
    shardSample_.setVerbose(true);
    shardSample_.load( ofToDataPath( "samples/get.wav" ));
    shardSample_.normalize();
    
    shardPlayer_.addSample(&shardSample_, 0);
    shardPlayer_.out_signal() >> soundEffectsMixL_.in_signal();
    shardPlayer_.out_signal() >> soundEffectsMixR_.in_signal();
    
    shardTriger_.out_trig() >> shardPlayer_.in_trig();
    shardTriger_.off();

    // Portal
    portalSample_.setVerbose(true);
    portalSample_.load(ofToDataPath( "samples/Portal.wav" ));
    portalSample_.normalize();
    
    portalPlayer_.addSample(&portalSample_, 0);
    portalPlayer_.out_signal() >> soundEffectsMixL_.in_signal();
    portalPlayer_.out_signal() >> soundEffectsMixR_.in_signal();
    
    portalTriger_.out_trig() >> portalPlayer_.in_trig();
    portalTriger_.off();

    
    // Shuffle
    shuffleSample_.setVerbose(true);
    shuffleSample_.load(ofToDataPath( "samples/WalkingConga2.wav" ));
    shuffleSample_.normalize();

    shuffleCloud_.addSample(&shuffleSample_);
    shuffleCloud_.setWindowType(pdsp::Hann);
    
    0.0f   >> shuffleBufferXPos_ >> shuffleCloud_.in_position();
    0.0f   >> shuffleJitter_     >> shuffleCloud_.in_position_jitter();
    
    200.0f >> shuffleCloud_.in_length();
    0.70f  >> shuffleCloud_.in_density();
    30.0f  >> shuffleCloud_.in_distance_jitter();
    0.1f   >> shuffleCloud_.in_pitch_jitter();
    0.0f   >> shuffleCloud_.in_pitch();
    
    shuffleCtrl_.enableSmoothing(30);
    shuffleCtrl_ >> shuffleMixL_.in_mod();
    shuffleCtrl_ >> shuffleMixR_.in_mod();
    shuffleCloud_.out_L() >> shuffleMixL_.in_signal();
                             shuffleMixL_.out_signal() >> soundEffectsMixL_.in_signal();
    shuffleCloud_.out_R() >> shuffleMixR_.in_signal();
                             shuffleMixR_.out_signal() >> soundEffectsMixR_.in_signal();
}

Audio::~Audio(){
    
}

void Audio::update(float timeElapsed, bool isPlayerInPortal) {
    //ShuffleSound
    float speed = fabs(player1Ptr_->getXVel()) / 50;
    shuffleCtrl_.setv(speed * 4);
    speed           >> shuffleBufferXPos_;
    speed * 0.75    >> shuffleJitter_;
    
    // OverWorld
    if(*currentLevelPtr_ > 0){
        // Play
        overWolrdMixCtrl_.setv(1.0f);
        if(!engine_.score.isPlaying()) {
            engine_.score.play();
            engine_.score.sections[0].launchCell( 0, quantize_, quantime_);
            engine_.score.sections[1].launchCell( 0, quantize_, quantime_);
        }
    } else {
        // Stop
        overWolrdMixCtrl_.setv(0.0f);
        if(engine_.score.isPlaying())
        {
            engine_.score.stop();
        }
    }
    
    // Ether
    if(isPlayerInPortal || *currentLevelPtr_ == 0) {
        etherMixCtrl_.setv(1.0f);
    } else {
        etherMixCtrl_.setv(0.0f);
    }
    
    if(isPlayerInPortal){
        if(freqWidth_ >= freqWidthMin_)
            freqWidth_ -= 0.4f * timeElapsed * 60;
    } else {
        if(freqWidth_ < freqWidthMax_)
            freqWidth_ += 0.4f * timeElapsed * 150;
    }
    
    // Shepard Tone Generator
    etherPhase_ = fmod(etherPhase_ + timeElapsed, phaseTime_);
    
    for (int i = 0; i < nOsc_; i++) {
        float offset = (1.0f / nOsc_) * i;
        float offsetEtherPhase = fmod(etherPhase_ + (offset * phaseTime_), phaseTime_) / phaseTime_;
        
        pitchCtrl_[i].setv(centerFreq_ + ( (offsetEtherPhase * freqWidth_) - (freqWidth_ * 0.5) ));
        
        float offsetEtherPhaseAmp = fmod(etherPhase_ + (((1.0f / nOsc_) * i) * phaseTime_), phaseTime_);
        float hann = 0.5*(1-cos((2*PI*offsetEtherPhaseAmp)/(phaseTime_ - 1)));
        
        if(hann > 1.0f)
            hann = 0.0f;
        
        if(hann < 0.0f)
            hann = 0.0f;
        
        ampCtrl_[i].setv(hann);
    }
}


void Audio::loadlevel() {
    if((*worldPtr_)[*currentLevelPtr_].getIsLevelAudioGenerated()){
        // Get level sequence
        melodySeqsPart_ = 0;
        melodySeqs_[melodySeqsPart_] = (*worldPtr_)[*currentLevelPtr_].getMelodySeqs()[melodySeqsPart_];
        
        kickSeqs_[0] = (*worldPtr_)[*currentLevelPtr_].getKickSeqs()[0];
        
        fmSynth_.setAmpEnv((*worldPtr_)[*currentLevelPtr_].getAttack(),
                           (*worldPtr_)[*currentLevelPtr_].getHold(),
                           (*worldPtr_)[*currentLevelPtr_].getRelease());
        
        // Set level sequence
        engine_.score.sections[0].setCell(0, &melodySeqs_[melodySeqsPart_], pdsp::Behavior::Loop );
        
        engine_.score.sections[1].setCell(0, &kickSeqs_[0], pdsp::Behavior::Loop );
        
        // Set level tempo
        engine_.score.setTempo((*worldPtr_)[*currentLevelPtr_].getTempo());
    }
}

void Audio::playJumpSound() {
    jumpTriger_.trigger(1);
}

void Audio::playFallSound() {
    fallTriger_.trigger(1);
}

void Audio::playShardSound() {
    shardTriger_.trigger(1);
    
    // advance seqeunce
    melodySeqsPart_ += 1;
    
    if(melodySeqsPart_ >= 4) {
        melodySeqsPart_ = 0;
    }
    
    melodySeqs_[melodySeqsPart_] = (*worldPtr_)[*currentLevelPtr_].getMelodySeqs()[melodySeqsPart_];
    
    engine_.score.sections[0].setCell(0, &melodySeqs_[melodySeqsPart_], pdsp::Behavior::Loop );
    
}

void Audio::playPortalSound() {
    if(portalPlayer_.meter_position() > 0.99f)
        portalTriger_.trigger(1);
}


