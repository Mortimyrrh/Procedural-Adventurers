#include "ofApp.h"

static int pts[] = {257,219,257,258,259,274,263,325,266,345,266,352,269,369,276,387,286,415,291,425,302,451,308,462,316,472,321,480,328,488,333,495,339,501,345,505,350,507,365,515,370,519,377,522,382,525,388,527,405,534,426,538,439,539,452,539,468,540,485,540,496,541,607,541,618,539,625,537,641,530,666,513,682,500,710,476,723,463,727,457,729,453,732,450,734,447,738,440,746,423,756,404,772,363,779,343,781,339,784,327,789,301,792,278,794,267,794,257,795,250,795,232,796,222,796,197,797,195,797,188,796,188};
static int nPts  = 61*2;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofBackgroundHex(0xfdefc2);
    ofSetLogLevel(OF_LOG_NOTICE);
    
    bMouseForce = false;
    
    box2d.init();
    box2d.setGravity(0, 10);
    box2d.createGround();
    box2d.setFPS(60.0);
    box2d.registerGrabbing();
    
    // lets add a contour to start
    for (int i=0; i<nPts; i+=2) {
        float x = pts[i];
        float y = pts[i+1];
        edgeLine.addVertex(x, y);
    }
    
    // make the shape
    edgeLine.setPhysics(0.0, 0.5, 0.5);
    edgeLine.create(box2d.getWorld());
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    box2d.update();
    
    
    if(bMouseForce) {
        float strength = 8.0f;
        float damping  = 0.7f;
        float minDis   = 100;
        for(int i=0; i<circles.size(); i++) {
            circles[i].get()->addAttractionPoint(mouseX, mouseY, strength);
            circles[i].get()->setDamping(damping, damping);
        }
        for(int i=0; i<customParticles.size(); i++) {
            customParticles[i].get()->addAttractionPoint(mouseX, mouseY, strength);
            customParticles[i].get()->setDamping(damping, damping);
        }
        
    }
    
    // remove shapes offscreen
    ofRemove(boxes, ofxBox2dBaseShape::shouldRemoveOffScreen);
    ofRemove(circles, ofxBox2dBaseShape::shouldRemoveOffScreen);
    ofRemove(customParticles, ofxBox2dBaseShape::shouldRemoveOffScreen);
    
    
}

//--------------------------------------------------------------
void ofApp::draw() {
    
    
    for(int i=0; i<circles.size(); i++) {
        ofFill();
        ofSetHexColor(0x90d4e3);
        circles[i].get()->draw();
    }
    
    for(int i=0; i<boxes.size(); i++) {
        ofFill();
        ofSetHexColor(0xe63b8b);
        boxes[i].get()->draw();
    }
    
    for(int i=0; i<customParticles.size(); i++) {
        customParticles[i].get()->draw();
    }
    
    ofNoFill();
    ofSetHexColor(0x444342);
    if(drawing.size()==0) {
        edgeLine.updateShape();
        edgeLine.draw();
    }
    else drawing.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == '32') ofToggleFullscreen();
    
    
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
    
    customParticles.push_back(shared_ptr<CustomParticle>(new CustomParticle));
    CustomParticle * p = customParticles.back().get();
    float r = ofRandom(3, 10);        // a random radius 4px - 20px
    p->setPhysics(0.4, 0.53, 0.31);
    p->setup(box2d.getWorld(), mouseX, mouseY, r);
    p->color.r = ofRandom(20, 100);
    p->color.g = 0;
    p->color.b = ofRandom(150, 255);
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
