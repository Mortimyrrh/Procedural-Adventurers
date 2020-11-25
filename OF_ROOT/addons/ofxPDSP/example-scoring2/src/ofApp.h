#pragma once

#include "ofMain.h"
#include "ofxSIMDFloats.h"
#include "ofxPDSP.h"
#include "bpattern.h"
#include "synths.h"

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
        
        ofxPDSPEngine   engine;
        
        SineBleep       bleep;
        BassSynth       bass;
        
        bool            oneShot;
        
        BassPattern     bassPattern;
    
        pdsp::Sequence    bleep1;
        pdsp::Sequence    bleep2;
        pdsp::Sequence    bleep3;
        pdsp::Sequence    bleep4;
            
        ofxScoreSectionPlotter  bassPatternGraphics;
        ofxScoreSectionPlotter  bleepPatternGraphics;

        float masterX;
};
