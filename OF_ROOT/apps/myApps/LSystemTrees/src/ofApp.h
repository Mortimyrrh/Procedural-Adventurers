#pragma once

#include "ofMain.h"
#include "ofxLSystemGrammar.h"
#include <string>
#include "LSystemTree.hpp"

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
    
private:
    
    float       floor;
    LSystemTree t1 { treeType::simpleL01 };
    LSystemTree t2 { treeType::simpleL02 };
    LSystemTree t3 { treeType::simpleL03 };

};
