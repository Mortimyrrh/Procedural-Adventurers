#include "ofApp.h"

// before looking at this check the basics and scoring examples
// values are output to arduino PWM 5-6
// connect leds for a simple test or some solenoids for real action
// useful link for setting up solenoids :
// http://bildr.org/2011/03/high-power-control-with-arduino-and-tip120/

//--------------------------------------------------------------
void ofApp::setup(){
    
    //-------------------GRAPHIC SETUP--------------
    ofBackground(0);
    ofSetFrameRate(30);
    
    // PATCHING
    serialOut.setVerbose(true); // when compiling in debug this also activates messages to the console when sending serial data
    serialOut.listPorts();
    serialOut.openPort(0); // set the right serial port
    
    // setup as usual, check example-scoring for more info
    engine.score.setTempo(145.0);
    engine.score.sections.resize(1); // we need just one section
    engine.score.sections[0].setCell(0, &sequence, pdsp::Behavior::Self);
    engine.score.sections[0].launchCell(0);
    engine.score.play();  
    
    // sequence

    float o = -1.0f; // using 'o' as graphical aid for empty steps

    vector<float> channel1 
        = { 120.0f,  o  ,   o  ,  100.0f ,  o,    o  ,   o  ,    o,     o,    o,  120.0f ,  o,     o  ,    o,     o ,    o  };
    vector<float> channel2 
        = { 120.0f,  o  , 90.0f,   o  ,  90.0f,  o  , 120.0f,   o  ,  90.0f,  o  , 90.0f,   o  , 120.0f,   o  ,  90.0f,  o  };
    // those are the value we pass to the serial
    // all values are converted to int and scaled in the 0<-->127 range


    float duration = 0.25; // duration before a 0.0f value is sent, in steps, so this is 25% of a 1/16th
                           // set it to the right value for your tempo for having a consistent control 
                           // it useful to have a short duration to control solenoids on/off pwm
                           // so you don't have to use delay() in the arduino loop
                           // that will cause bad timing
  
    sequence.begin(16.0, 1.0);    
    sequence.trigVector( channel1, duration, 0); // this will add all the values of an std::vector<float> as messages
    sequence.trigVector( channel2, duration, 1); // and also generate trigger off signals (0.0f values)
    sequence.end();
    
    // each "channel" can trigger different actions in the arduino sketch
    engine.score.sections[0].out_message( 0 ) >> serialOut.channel(1); 
    engine.score.sections[0].out_message( 1 ) >> serialOut.channel(2); 
    // the included arduino sketch output those values multiplied per 2 to some pwm outputs
    // channel 1 goes to pwm out 5
    // channel 2 goes to pwm out 6        
    
    
    //----------------------AUDIO SETUP-------------
    engine.addSerialOut( serialOut ); // remember to add your serial output to the engine
    engine.listDevices();
    engine.setDeviceID(0); // REMEMBER TO SET THIS AT THE RIGHT INDEX!!!!
    engine.setup( 44100, 512, 3); 

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
        case '1':
            engine.score.sections[0].launchCell(0, false);
            break;
        case '2':
            engine.score.sections[0].launchCell(1, false);        
            break;
        case '3':
            engine.score.sections[0].launchCell(2, false);
            break;
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
