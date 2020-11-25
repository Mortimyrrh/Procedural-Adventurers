#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);
    ofBackground(0);
    
//    Portal.push_back({});
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    float x = 200;
    float y = 400;
    
//    for (int i = 0; i << Portal.size(); i++) {
//        Portal[i].draw(x,y);
//    }
    
    pt1.draw(x, y);
    pt2.draw(x, y);
    pt3.draw(x, y);
    pt4.draw(x, y);
    pt5.draw(x, y);
    pt6.draw(x, y);
    pt7.draw(x, y);
    
    x = 600;
    y = 400;
    
    apt1.draw(x, y);
    apt2.draw(x, y);
    apt3.draw(x, y);
    apt4.draw(x, y);
    apt5.draw(x, y);
    apt6.draw(x, y);
    apt7.draw(x, y);
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
