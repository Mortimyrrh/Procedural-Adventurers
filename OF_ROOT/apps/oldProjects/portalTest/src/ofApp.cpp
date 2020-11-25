#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(30);
    ofSetFullscreen(true);
}

//--------------------------------------------------------------
void ofApp::update(){

    float t = ofGetLastFrameTime();
    
    p1.calculate( t );
    p2.calculate( t );
    p3.calculate( t );
    p4.calculate( t );
    
    p5.calculate( t );
    p6.calculate( t );
    p7.calculate( t );
    p8.calculate( t );
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    p1.draw(ofGetWindowWidth() * 0.15,  ofGetWindowHeight() * 0.75);
    p2.draw(ofGetWindowWidth() * 0.375, ofGetWindowHeight() * 0.75);
    p3.draw(ofGetWindowWidth() * 0.625, ofGetWindowHeight() * 0.75);
    p4.draw(ofGetWindowWidth() * 0.85,  ofGetWindowHeight() * 0.75);

    p5.draw(ofGetWindowWidth() * 0.15,  ofGetWindowHeight() * 0.25);
    p6.draw(ofGetWindowWidth() * 0.375, ofGetWindowHeight() * 0.25);
    p7.draw(ofGetWindowWidth() * 0.625, ofGetWindowHeight() * 0.25);
    p8.draw(ofGetWindowWidth() * 0.85,  ofGetWindowHeight() * 0.25);
    
    ofPolyWindingMode::OF_POLY_WINDING_NEGATIVE;

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
