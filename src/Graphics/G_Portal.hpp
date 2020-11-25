//
//  portal.hpp
//  portalTest
//
//  Created by Mortimer Pavlitski on 23/12/2017.
//

#ifndef portal_hpp
#define portal_hpp

#include <stdio.h>
#include "Fonts.hpp"
#include "Lang.hpp"
#include "ofxTrueTypeFontUC.h"

class PortalText {
public:
    PortalText(){};
    
    PortalText(string fontname, vector<string> lang, int fontSizeRange[2], float speed, int startColour) {
        maxRadius_      = ofRandom(20, 130);
        radius_         = maxRadius_;
        alpha_          = ofRandom(200, 255);
        time_           = startColour + int(ofRandom(0, 20));
        angle_          = ofRandom(0, 360);
        angleinc_       = ofRandom(0.5, 6.5);
        
        z_ = - 120 + (radius_ * 0.4);
        
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
            ofTranslate(x, y); //z_ for paralx
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
    float   z_        = 0;
    float   angle_    = 0;
    float   angleinc_ = 0;
    float   maxRadius_   = 0;
    float   radius_   = 0;
    float   time_     = 0;
};

struct PortalType {
    int             numTextRings;
    vector<string>  lang;
    string          fontname;
    int             fontSizeRange[2];
};

namespace portal {
    const PortalType test = {
        10,
        Lang::english,
        Font::arial,
        24, 24
    };
    
    const PortalType tokyo = {
        10,
        Lang::katakana,
        Font::arial,
        12, 24
    };
    
    const PortalType nordic = {
        14,
        Lang::youngerFuthark,
        Font::juni,
        14, 32
    };
    
    const PortalType egypt = {
        10,
        Lang::hieroglyph,
        Font::egypt,
        14, 28
    };
    
    const PortalType cunei = {
        13,
        Lang::english,
        Font::cunei,
        14, 32
    };
    
    const PortalType hyrule = {
        10,
        Lang::english,
        Font::hylian,
        12, 32
    };
    
    const PortalType iching = {
        10,
        Lang::iching,
        Font::applesym,
        14, 28
    };
    
    const PortalType seoul = {
        12,
        Lang::hangul,
        Font::arial,
        12, 32
    };
    
    const PortalType test2 = {
        4,
        Lang::hangul,
        Font::arial,
        20, 24
    };
}


class G_Portal {
public:
    G_Portal( PortalType portalType ) {
        isPortalActive_ = false;
        speed_ = 0;
        
        int startcolour = int(ofRandom(0, 255));
            
        for(int i = 0; i < portalType.numTextRings; i++){
            portalTexts_.push_back(new PortalText{portalType.fontname, portalType.lang, portalType.fontSizeRange, speed_, startcolour });
        }
        
        draw(0,0);
        
    }
    
    ~G_Portal(){};
    
    void update ( float timepassed, float speed) {
        speed_ = speed;
        
        for (int i = 0; i < portalTexts_.size(); i++) {
            portalTexts_[i]->calculate(timepassed, speed_);
        }
    }
    
    void draw(float x, float y) {
        for (int i = 0; i < portalTexts_.size(); i++) {
            portalTexts_[i]->draw(x, y);
        }
    }
    
    void getIsPortalActive() {
        return isPortalActive_;
    }
    
    float* getPortalSpeedPtr() {
        return &speed_;
    }
    
private:
    vector<PortalText*> portalTexts_;
    bool    isPortalActive_;
    float   speed_    = 3;
};

#endif /* portal_hpp */
