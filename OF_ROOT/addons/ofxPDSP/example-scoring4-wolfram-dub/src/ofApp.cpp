#include "ofApp.h"

#define ZAPS_NUMBER 4
#define MAX_GENERATIONS 8
#define SIDE 16

// before looking at this check out the basics and scoring examples

// this is the most complex example in ofxPDSP, and it shows you an example of workflow
// ideally you should have your pdsp::Sequence classes, your synth and effect classes with their ofParameterGroups 
// patch them together in your app and fine tune them in the ui
// (remember you can use your mouse scroll wheel for fine tuning paramenter, point on a slider and move the wheel)
// also it is always handy to use a masterplan sequence to launch other sequences and change parameters

// the included impulse response come from:
// dubshot.blogspot.com/2008/10/free-download-60-classic-and-king-tubby.html
// Licensed under a creative commons attribution-noncommercial-share alike 3.0 Netherlands license

//--------------------------------------------------------------
void ofApp::setup(){
    
    //------------------- graphics --------------
    ofBackground(0);
    ofSetFrameRate(60);
    ofDisableAntiAliasing();
    brightColor = ofColor( 255, 95, 95);
    darkColor = ofColor( 90, 35, 35);
    ofSetWindowTitle( "wolfram dub d(-_-)b" );
    caHeight = SIDE*MAX_GENERATIONS;

    //----------------- SEQUENCING ---------------------
    // Setting up score
    //engine.score.stop();    // decomment if you want to start the app from stopped state
    engine.score.setTempo(172.0f);
    engine.score.sections.resize(2);
    
    engine.score.sections[0].setCell( 0, &masterplan );
    
    // masterplan coding
    masterplan.setLength(1.0); // 1 bar loop
    
    masterplan.code = [&] () {
        if(masterplan.counter() >= randomizeBars){
            masterplan.resetCount();
        }
        // our masterplan sequence is used to randomize wolframSeq parameters
        if(masterplan.counter()==0 && masterplanRandomize){
        
            wolframSeq.remake = true; // generate the sequence again
            wolframSeq.activeOuts = pdspDice( 2, 5 );
            wolframSeq.threshold = pdspDice(2, 6);
            wolframSeq.seedsDensity = 0.2f + pdspURan()*0.4f;
            dub.lDelayTimeControl.getOFParameterInt() = pdspDice(1,9);
            dub.rDelayTimeControl.getOFParameterInt()  = pdspDice(1,9);
            dub.lFeedbackControl.getOFParameterFloat() = 0.2f + pdspURan()*0.5f;
            dub.rFeedbackControl.getOFParameterFloat() = 0.2f + pdspURan()*0.5f;
            
            switch( pdspDice(6) ){
                case 0:
                    wolframSeq.rule = 90;
                    wolframSeq.reverse = false;
                    wolframSeq.threshold = pdspDice(0, 4);
                    break;
                case 1:
                    wolframSeq.rule = 124;
                    wolframSeq.reverse = pdspChance(0.5f);
                    break;
                case 2:
                    wolframSeq.rule = 126;
                    wolframSeq.reverse = pdspChance(0.5f);
                    break;
                case 3:
                    wolframSeq.rule = 150;
                    wolframSeq.reverse = pdspChance(0.5f);
                    break;
                case 4:
                    wolframSeq.rule = 60;
                    wolframSeq.reverse = false;
                    break;
                case 5:
                    wolframSeq.rule = 110;
                    wolframSeq.reverse = true;
                    break;
            }
        }
    }; // masterplan end

    // sets up wolfram sequence
    wolframSeq.setup( 16, ZAPS_NUMBER, 60, MAX_GENERATIONS, SIDE, 300 );      
    engine.score.sections[1].setCell( 0, &wolframSeq );
    
    engine.score.launchMultipleCells(0); // launch the 0 sequences of all the sections
    
    
    // ----------- PATCHING -----------
    
    // loads reverb impulse response
    reverb.loadIR( "data/kingtubby-fl1.wav");
    
    zaps.setup(ZAPS_NUMBER);
    scopes.resize(ZAPS_NUMBER + 2);
    
    for ( int i=0; i<ZAPS_NUMBER; ++i ) {
        engine.score.sections[1].out_trig(i) >> zaps.voices[i]; // patch the sequence outputs to the zaps
        zaps.voices[i] >> scopes[i] >> engine.blackhole();
    }
    
    zaps.fader.out_L() >> engine.audio_out(0);
    zaps.fader.out_R() >> engine.audio_out(1);   
    
    // patch the zaps to the reverb input 
    float revGain = -60.0f; // -65dB, this IRs are very loud
    zaps.fader.out_L() * dB(revGain) >> reverb.in_L(); 
    zaps.fader.out_R() * dB(revGain) >> reverb.in_R();
    
    // patch the reverb to an high pass filter and then to the engine
    // ( deactivated on rPi as the processor is too slow for IR convolution using FFT )
#ifndef __ARM_ARCH
    reverb.out_L() >> revCut.in_0(); revCut.out_0() >> engine.audio_out(0);
    reverb.out_R() >> revCut.in_1(); revCut.out_1() >> engine.audio_out(1);
    100.0f >> revCut.in_freq(); // 100hz, we cut the reverb muddy low end 
#endif

    // connect the zaps to the stereo delay
    zaps.fader.out_L() >> dub.in("0");
    zaps.fader.out_R() >> dub.in("1");
                          dub.out("0") >> engine.audio_out(0);
                          dub.out("1") >> engine.audio_out(1);
                          dub.out("0") * dB(12.0f) >> scopes[ZAPS_NUMBER]   >> engine.blackhole();
                          dub.out("1") * dB(12.0f) >> scopes[ZAPS_NUMBER+1] >> engine.blackhole();
     
     
    // ------------ GUI ------------
    gui.setup("", "wolframdub.xml", ofGetWidth()-220, 40);
    gui.setName( "WOLFRAM DUB" );
    gui.add( masterplanRandomize.set("masterplan randomize", false) );
    gui.add( randomizeBars.set("num bars", 16, 1, 32) );
    gui.add( wolframSeq.ui );
    gui.add( zaps.ui );
    gui.add( dub.ui );
    
    
    //---------------------- audio setup -------------
    engine.listDevices();
    engine.setDeviceID(1); // REMEMBER TO SET THIS AT THE RIGHT INDEX!!!!
    engine.setup( 44100, 512, 3); 

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    
    gui.draw();

    ofSetColor( brightColor ); 
    wolframSeq.draw( 20, 50 );
    
    
    // draw the scopes
    ofPushMatrix();
        ofTranslate( 20, 420 );
        ofSetColor( brightColor );
        
        for(int y=0; y<2; ++y){
            for( int x=0; x<3; ++x){
                int i = x+y*3;
                string label;
                switch (i){
                    case 0: case 1: case 2: case 3:
                        label = "zap " + ofToString(i);
                    break;
                    
                    case 4: label = "delay L"; break;
                    case 5: label = "delay R"; break;
                }
                int xpos = x*347;
                int ypos = y*120;
                ofDrawBitmapString( label, xpos, ypos);
                scopes[i].draw( xpos, ypos + 10, 330, 80);
            }
        }
    ofPopMatrix();


    ofDrawBitmapString("spacebar: stop/play", 20, ofGetHeight() - 20); 
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == ' '){
        if(engine.score.isPlaying()){
            engine.score.stop();
        }else{
            engine.score.play();
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

