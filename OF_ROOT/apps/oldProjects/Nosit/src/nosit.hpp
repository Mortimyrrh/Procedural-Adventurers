//
//  nosit.hpp
//  Nosit
//
//  Created by Mortimer Pavlitski on 12/03/2018.
//

#ifndef nosit_hpp
#define nosit_hpp

#include <stdio.h>
#include "ofMain.h"

class Nosit {
public:
    void draw() {
        ofTranslate(500, ofGetWindowHeight() - 300);
        
        float x = 50;
        float y = 0;
        float w = 100;
        float h = 200;

        float hatsize = 0.8;
        //body
        ofSetColor(180,100,20);
        ofDrawRectangle(x - (w*0.5), -y, w, -h);
        
        //hat
        ofSetColor(0);
        ofDrawTriangle(x, -(y+(h*1.15)), x + (w * hatsize), -(y+(h*0.9)), (x - (w * hatsize)), -(y+(h*0.9)));
        
        //midle
        ofSetColor(100);
        float padding = 16;
        ofDrawRectRounded(x - (w*0.5) + padding, -y -padding, w - (padding*2), - (h*0.5) + (padding * 2), 8);

        ofSetColor(0);

        //eyes
        ofDrawLine(x-(w*0.15), -(y+(h*0.75)), x-(w*0.35), -(y+(h*0.85)));
        ofDrawLine(x+(w*0.15), -(y+(h*0.75)), x+(w*0.35), -(y+(h*0.85)));
        
        //mouth
        //line
//        ofDrawLine(x-(w*0.25), -(y+(h*0.6)), x+(w*0.25), -(y+(h*0.6)));
        //circle
//        ofDrawL(x-(w*0.25), -(y+(h*0.6)), x+(w*0.25), -(y+(h*0.6)));

        //normal
        ofDrawBezier(x-(w*0.0), -(y+(h*0.7)), x-(w*0.2), -(y+(h*0.55)),
                     x-(w*0.0), -(y+(h*0.62)), x-(w*0.2), -(y+(h*0.58)));
        
        ofDrawBezier(x+(w*0.0), -(y+(h*0.7)), x+(w*0.2), -(y+(h*0.55)),
                    x+(w*0.0), -(y+(h*0.62)), x+(w*0.2), -(y+(h*0.58)));
        
    }
};
#endif /* nosit_hpp */
