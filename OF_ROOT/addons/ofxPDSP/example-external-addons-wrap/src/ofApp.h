#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"


class AddonWrapper : public ofxPDSPWrapper {

public:
    void setup( int bufferSize );

    vector <float> left;
    vector <float> right;

    atomic<int> 	bufferCounter;
    atomic<float>   smoothedVol;


private:
    void audioProcess(float *input, int bufferSize, int nChannels);

};

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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        // pdsp modules
        ofxPDSPEngine   engine;
        
        AddonWrapper wrapper;
        
        int 	drawCounter;
        
        vector <float> volHistory;
        float scaledVol;
};
