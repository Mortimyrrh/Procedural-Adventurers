#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update(){
    //calculate time passed
    timeStamp = ofGetElapsedTimef() * 700;
    timePassed = timeStamp - lastTimeStamp;
    lastTimeStamp = timeStamp;
    
    ofLog() << "timePassed " << timePassed;

    
    //calculate
    calculateLeon();
    
    // FPS
    //ofLog("FPS =  " + String((1/ timePassed) * 1000));
    //ofLog() << "FPS " << ofGetFrameRate();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // clear canvas
    // ctx_graphic.clearRect(0, 0, canvas.width, canvas.height);

    
    for (int i = 0; i < 3; i++) { // Need to change to be dynamic
        drawPlatform(platforms[i]);
    }
    
    drawLeon(leon.xpos, leon.ypos);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key) {
        case 119: // w
            inputControl.isUpKeyActive = true;
            break;
        case 115: // s
            inputControl.isDownKeyActive = true;
            break;
        case 97: // a
            inputControl.isLeftKeyActive = true;
            break;
        case 100: // d
            inputControl.isRightKeyActive = true;
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    switch(key) {
        case 119: // w
            inputControl.isUpKeyActive = false;
            break;
        case 115: // s
            inputControl.isDownKeyActive = false;
            break;
        case 97: // a
            inputControl.isLeftKeyActive = false;
            break;
        case 100: // d
            inputControl.isRightKeyActive = false;
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
