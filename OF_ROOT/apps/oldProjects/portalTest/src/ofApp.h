#pragma once

#include "ofMain.h"
#include "meta.hpp" // needs to be above other code

#include "portal.hpp"

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

    
    Portal p1{ portal::test };
    Portal p2{ portal::tokyo };
    Portal p3{ portal::nordic };
    Portal p4{ portal::egypt };
    
    Portal p5{ portal::cunei };
    Portal p6{ portal::hyrule };
    Portal p7{ portal::iching };
    Portal p8{ portal::seoul };
    
//    Portal portalToNoricForest{"junicode.ttf", Portals::youngerFuthark, 12};

    
    
		
};
