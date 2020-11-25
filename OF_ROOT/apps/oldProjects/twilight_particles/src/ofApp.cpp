#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetBackgroundColor(17,16,50);
    
    ///noise
    
    img.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR_ALPHA);
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    //calculate time passed
    timeStamp = ofGetElapsedTimef();
    timePassed = timeStamp - lastTimeStamp;
    lastTimeStamp = timeStamp;
    
    // % chance of genirating a particle up to a max
    if (EtherParticles.size() < 200 && ofRandom(100) < 5)
        EtherParticles.push_back({});

    // updates the particles
    for (EtherParticle& p : EtherParticles)
        p.update(timePassed);
    
    
    ////
    
   // int w = ofGetWidth();
   // int h = ofGetHeight();
    
   // for (int y=0; y<h; y++) {
   //     for (int x=0; x<w; x++) {
  //
   //         float a = x * .01;
  //          float b = y * .01;
  //          float c = ofGetFrameNum() / 50.0;
            
  //          float color = noise > 200 ? ofMap(noise,200,255,0,255) : 0;
            
   //         img.getPixels()[y*w+x] = color;
  //      }
 //   }
    
//    img.reloadTexture();
  //  img.getTexture();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // draw particles
    for (EtherParticle& p : EtherParticles)
        p.draw();
    
    img.draw(0,0);
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
