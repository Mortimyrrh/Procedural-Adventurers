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
    PortalText(){};

    PortalText(string fontname, vector<string> lang, int fontSizeRange[2], float speed, int startColour){
        maxRadius_      = ofRandom(20, 150);
        radius_         = maxRadius_;
        alpha_          = ofRandom(200, 255);
        time_           = startColour + int(ofRandom(0, 20));
        angle_          = ofRandom(0, 360);
        angleinc_       = ofRandom(0.5, 6.5);
        
        if(angleinc_ > 3.5){ angleinc_ += -7; }
    
        int stringLength = round(ofRandom(4, 6 + int(radius_ * 0.5 / 10)));
        
        for (int i = 0; i < stringLength; i++) {
            string text = lang[round(ofRandom(lang.size() - 1))];
            text_.push_back( {text} );
        }
                
        juni.load(fontname, ofRandom(fontSizeRange[0] * (radius_ + 50) / 200, fontSizeRange[1] * (radius_ + 50) / 200), true, true);
    };
    
    ~PortalText(){};
    
    void calculate ( float timepassed, float speed) {
        radius_ = maxRadius_ - maxRadius_ * (speed / 1000);
        
        if (radius_ > maxRadius_) {
            radius_ = maxRadius_;
        }
        
        angle_ += angleinc_ * (timepassed * speed);
        time_  += 1 * (timepassed * speed);
        
        if(angle_ == 360) { angle_ = 0; }
        if(time_ == 255) { time_ = 0; }
    }
    
    void draw(float x, float y) {
        for (int i = 0; i < text_.size() ; i++){
            string s = text_[i];
            
            //Per Char
            ofSetColor(ofColor::fromHsb(int(time_+(i * 3))%255, 250, alpha_ * ((radius_ + 50) / 200)));
            ofPushView();
            ofTranslate(x, y);
            ofRotate(angle_ + (i * 15));
            juni.drawString(s, 0, -radius_);
            ofPopView();
        }
    };
    
private:
    ofxTrueTypeFontUC juni;
    vector<string>  text_;
    
    float   hue       = 0;
    float   alpha_    = 0;
    float   x_        = 0;
    float   y_        = 0;
    float   angle_    = 0;
    float   angleinc_ = 0;
    float   maxRadius_   = 0;
    float   radius_   = 0;
    float   time_     = 0;
};



#endif /* PortalText_hpp */
