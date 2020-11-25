#pragma once

#include "ofMain.h"
#include "PortalText.hpp"

class ofApp :
public ofBaseApp{

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
		
    vector<PortalText> Portal;
    
    
    PortalText pt1{80, 0, -0.53, 28, "junicode.ttf", {"ᚢ","ᚦ","ᚬ","ᚱ","ᛦ"}};
    PortalText pt2{100, 90, 0.97, 32, "junicode.ttf", {"ᚠ","ᚢ","ᚦ","ᚬ","ᚱ","ᛦ"}};
    PortalText pt3{140, 180, -1.21, 24, "junicode.ttf", {"ᚠ","ᚢ","ᚦ","ᚬ","ᚱ","ᚴ","ᚼ","ᚾ","ᛁ","ᛅ","ᛋ","ᛏ","ᛒ","ᛘ","ᛚ","ᛦ"}};
    PortalText pt4{90, 270, 1.789, 12, "junicode.ttf", {"ᚢ","ᚦ","ᚬ","ᚱ","ᛦ"}};
    PortalText pt5{120, 45, 1.823, 26, "junicode.ttf", {"ᚢ","ᚦ","ᚬ","ᚱ","ᛦ"}};
    PortalText pt6{60, 235, 1.432, 10, "junicode.ttf", {"ᚠ","ᚢ","ᚦ","ᚬ","ᚱ","ᚴ","ᚼ","ᚾ","ᛁ","ᛅ","ᛋ","ᛏ","ᛒ","ᛘ","ᛚ","ᛦ"}};
    PortalText pt7{70, 315, -0.3, 14, "junicode.ttf", {"ᚢ","ᚦ","ᚬ","ᛦ"}};


    //{"ᚠ","ᚢ","ᚦ","ᚬ","ᚱ","ᚴ","ᚼ","ᚾ","ᛁ","ᛅ","ᛋ","ᛏ","ᛒ","ᛘ","ᛚ","ᛦ"};
    
    
    //{"ア","イ","ウ","エ","オ","カ","キ","ク","ケ","コ","サ","シ","ス","セ","ソ","タ","チ","ツ","テ","ト","ナ","ニ","ヌ","ネ","ノ","ハ","ヒ","フ","ヘ","ホ","マ","ミ","ム","メ","モ","ヤ","ユ","ヨ","ラ","リ","ル","レ","ロ","ワ","ヰ","ヱ","ヲ"}
    
        PortalText apt1{80, 0, -0.53, 28, "Arial Unicode.ttf", {"ミ","ム","メ","モ"}};
        PortalText apt2{100, 90, 0.97, 32, "Arial Unicode.ttf", {"ク","ケ","コ","サ","シ","ス","セ","ソ"}};
    PortalText apt3{140, 180, -1.21, 24, "Arial Unicode.ttf",{"ア","イ","ウ","エ","オ","カ","キ","ク","ケ","コ","サ","シ","ス","セ","ソ","タ"}};
        PortalText apt4{90, 270, 1.789, 12, "Arial Unicode.ttf", {"ノ","ハ","ヒ","フ","ヘ"}};
        PortalText apt5{120, 45, 1.823, 26, "Arial Unicode.ttf", {"ソ","タ","チ","ツ","テ","ト"}};
        PortalText apt6{60, 235, 1.432, 10, "Arial Unicode.ttf", {"ア","イ","ウ","エ","オ","カ","キ","ク","ケ","ロ","ワ","ヰ","ヱ","ヲ"}};
        PortalText apt7{70, 315, -0.3, 14, "Arial Unicode.ttf", {"エ","オ","カ","キ"}};
    
};
