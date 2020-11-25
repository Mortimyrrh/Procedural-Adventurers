#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        
        void controlOn(int x, int y);
        
        void loadRoutine();
        
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
        
        ofxPDSPEngine           engine;
       
        ofxSampleBufferPlotter  waveformGraphics;
       
        int                         grainVoices;
        pdsp::SampleBuffer          sampleData;
        pdsp::GrainCloud            cloud;
      
        pdsp::ADSR              ampEnv;
        pdsp::Amp               voiceAmpL;
        pdsp::Amp               voiceAmpR;
        ofxPDSPValue            ampControl;
        pdsp::PatchNode         posX;
        pdsp::PatchNode         jitY;
        
        
        bool    drawGrains;
  
        int     uiWidth;
        int     uiHeigth;
        int     uiX;
        int     uiY;
        int     uiMaxX;
        int     uiMaxY;
        int     controlX;
        int     controlY;
      
};
