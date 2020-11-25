//
//  portal.hpp
//  portalTest
//
//  Created by Mortimer Pavlitski on 23/12/2017.
//

#ifndef portal_hpp
#define portal_hpp

#include <stdio.h>
#include "PortalText.hpp"

struct PortalType {
    int             numTextRings;
    vector<string>  lang;
    string          fontname;
    int             fontSizeRange[2];
};

namespace portal {
    const PortalType test = {
        10,
        lang::english,
        font::arial,
        24, 24
    };
    
    const PortalType tokyo = {
        10,
        lang::katakana,
        font::arial,
        12, 24
    };
    
    const PortalType nordic = {
        14,
        lang::youngerFuthark,
        font::juni,
        14, 32
    };
    
    const PortalType egypt = {
        10,
        lang::hieroglyph,
        font::egypt,
        14, 28
    };
    
    const PortalType cunei = {
        13,
        lang::english,
        font::cunei,
        14, 32
    };
    
    const PortalType hyrule = {
        10,
        lang::english,
        font::hylian,
        12, 32
    };
    
    const PortalType iching = {
        10,
        lang::iching,
        font::applesym,
        14, 28
    };
    
    const PortalType seoul = {
        12,
        lang::hangul,
        font::arial,
        12, 32
    };
    
    const PortalType test2 = {
        4,
        lang::hangul,
        font::arial,
        20, 24
    };
}


class Portal {
public:
    Portal( PortalType portalType ) {
        speed_ = ofRandom(0.1, 0.3);
        // speed_ = ofRandom(1, 50);
        
        int startcolour = int(ofRandom(0, 255));
            
        for(int i = 0; i < portalType.numTextRings; i++){
            portalTexts_.push_back(new PortalText{portalType.fontname, portalType.lang, portalType.fontSizeRange, speed_, startcolour });
        }
    }
    
    ~Portal(){};
    
    void calculate ( float timepassed ) {
        speed_ *= 1.07;
        ofLog() << speed_;
        
        if (speed_ > 1000) {
            speed_ = 1;
        }
        
        for (int i = 0; i < portalTexts_.size(); i++) {
            portalTexts_[i]->calculate(timepassed, speed_);
        }
    }
    
    void draw(float x, float y) {
        for (int i = 0; i < portalTexts_.size(); i++) {
            portalTexts_[i]->draw(x, y);
        }
    }
    
private:
    vector<PortalText*> portalTexts_;
    
    float   speed_    = 1;
};

/*
 old way
 PortalText pt1{80, 0, -0.53, 28, "junicode.ttf", {"ᚢ","ᚦ","ᚬ","ᚱ","ᛦ"}};
 PortalText pt2{100, 90, 0.97, 32, "junicode.ttf", {"ᚠ","ᚢ","ᚦ","ᚬ","ᚱ","ᛦ"}};
 PortalText pt3{140, 180, -1.21, 24, "junicode.ttf", {"ᚠ","ᚢ","ᚦ","ᚬ","ᚱ","ᚴ","ᚼ","ᚾ","ᛁ","ᛅ","ᛋ","ᛏ","ᛒ","ᛘ","ᛚ","ᛦ"}};
 PortalText pt4{90, 270, 1.789, 12, "junicode.ttf", {"ᚢ","ᚦ","ᚬ","ᚱ","ᛦ"}};
 PortalText pt5{120, 45, 1.823, 26, "junicode.ttf", {"ᚢ","ᚦ","ᚬ","ᚱ","ᛦ"}};
 PortalText pt6{60, 235, 1.432, 10, "junicode.ttf", {"ᚠ","ᚢ","ᚦ","ᚬ","ᚱ","ᚴ","ᚼ","ᚾ","ᛁ","ᛅ","ᛋ","ᛏ","ᛒ","ᛘ","ᛚ","ᛦ"}};
 PortalText pt7{70, 315, -0.3, 14, "junicode.ttf", {"ᚢ","ᚦ","ᚬ","ᛦ"}};
*/

#endif /* portal_hpp */
