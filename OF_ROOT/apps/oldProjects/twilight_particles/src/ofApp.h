#pragma once

#include "ofMain.h"
#include "EtherParticle.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w,  int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
    
private:

    //time
    float timeStamp = 0;
    float lastTimeStamp = 0;
    float timePassed = 0;
    
    std::vector<EtherParticle> EtherParticles;     //particle vector
    
    ofImage img;
};



