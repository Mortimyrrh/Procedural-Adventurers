//
//  PortalText.hpp
//  Norce
//
//  Created by Mortimer Pavlitski on 22/12/2017.
//

#ifndef PortalText_hpp
#define PortalText_hpp

#include <stdio.h>
#include "ofxTrueTypeFontUC.h"

class PortalText {
public:
    PortalText(){
        time_ = int(ofRandom(0, 20));
        
        juni.load("junicode.ttf", 50, true, true);
        //"Arial Unicode.ttf"
    };
    
    PortalText(float radius, float angle, float angleinc, float textsize, string fontname, vector<string> text) {
        time_ = int(ofRandom(0, 20));
        
        radius_ = radius;
        angle_  = angle;
        angleinc_ = angleinc;
        text_   = text;

        juni.load(fontname, textsize, true, true);
        
        
    };
    
    ~PortalText(){};
    
    void draw(float x, float y) {
        for (int i = 0; i < text_.size() ; i++){
            string s = text_[i];
            
            //Per Char
            ofSetColor(ofColor::fromHsb(int(time_+(i * 3))%255, 250, 250)); //should be a hls random
            ofPushView();
            ofTranslate(x, y);
            ofRotate(angle_ + (i * 15));
            juni.drawString(s, 0, -radius_);
            ofPopView();
        }
    
        angle_ += angleinc_; //should insre by time passed
        time_ ++; // same as above but with random variation
        
        if(angle_ == 360) { angle_ = 0; }
        if(time_ == 255) { time_ = 0; }
    };
    
private:
    ofxTrueTypeFontUC juni;
    
    float   hue      = 50; // should random ly genarate a ist and inded into it with the text
    
    vector<string>  text_    = {"ᚠ","ᚢ","ᚦ","ᚬ","ᚱ","ᚴ","ᚼ","ᚾ","ᛁ","ᛅ","ᛋ","ᛏ","ᛒ","ᛘ","ᛚ","ᛦ"};
    
    float   x_       = 100;
    float   y_       = 100;
    float   angle_   = 0;
    float   angleinc_ = 0;
    float   radius_  = 100;
    float   time_    = 0;
};



#endif /* PortalText_hpp */
