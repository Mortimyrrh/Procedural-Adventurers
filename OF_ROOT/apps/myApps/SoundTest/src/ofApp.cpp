#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
//    mySound.load("/Users/mortimer/Documents/U Y2/U Y2/ISD/Test Audio/Imogen Heap - Hide And Seek.mp3");
    mySound.load("audio/background/Cat In the Hat.wav");
    mySound.setMultiPlay(true);
}

//--------------------------------------------------------------
void ofApp::update(){
    // update the sound playing system:
    ofSoundUpdate();
}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    mySound.setPositionMS(2000);
    
    switch (key) {
        case 'a':
            mySound.setSpeed(1.f);
            mySound.play();
            break;
            
        case 's':
            mySound.setSpeed(1.6f);
            mySound.play();
            break;
            
        case 'd':
            mySound.setSpeed(1.4f);
            mySound.play();
            break;
            
        case 'm':
            mySound.setSpeed( 0.1f + ((float)(ofGetHeight() - ofGetMouseY()) / (float)ofGetHeight())*10);
            mySound.setPan(((1 - ((float)(ofGetWidth() - ofGetMouseX()) / (float)ofGetWidth())) *2 ) -1);

            mySound.play();
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
