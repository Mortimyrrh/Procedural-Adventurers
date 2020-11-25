#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);
    buttonState[0] = 0;
    buttonState[1] = 0;
    buttonState[2] = 0;
    buttonState[3] = 0;
    buttonState[4] = 0;
    buttonState[5] = 0;
    buttonState[6] = 0;
    buttonState[7] = 0;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case "a":
            buttonState[0] = 1;
            break;
            
        case "s":
            buttonState[1] = 1;
            break;
            
        case "d":
            buttonState[2] = 1;
            break;
            
        case "f":
            buttonState[3] = 1;
            break;
            
        case "g":
            buttonState[4] = 1;
            break;
            
        case "h":
            buttonState[5] = 1;
            break;
            
        case "j":
            buttonState[6] = 1;
            break;
            
        case "k":
            buttonState[7] = 1;
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    switch (key) {
        case "a":
            buttonState[0] = 0;
            break;
            
        case "s":
            buttonState[1] = 0;
            break;
            
        case "d":
            buttonState[2] = 0;
            break;
            
        case "f":
            buttonState[3] = 0;
            break;
            
        case "g":
            buttonState[4] = 0;
            break;
            
        case "h":
            buttonState[5] = 0;
            break;
            
        case "j":
            buttonState[6] = 0;
            break;
            
        case "k":
            buttonState[7] = 0;
            break;
            
        default:
            break;
    }
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
