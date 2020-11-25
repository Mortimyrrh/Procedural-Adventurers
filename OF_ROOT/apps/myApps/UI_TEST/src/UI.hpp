//
//  UI.hpp
//  UI_TEST
//
//  Created by Mortimer Pavlitski on 25/12/2017.  ;)
//

#ifndef UI_hpp
#define UI_hpp

#include <stdio.h>

class Item {
public:
    Item( string leter ) {
        leter_      = leter;
        font_.load(font::arial, 28);
        colour_     = ofColor::fromHsb(ofRandom(0, 255), 255, 255);
    }
    
    ~Item(){};
    
    void draw (float x, float y, float itemBoxRadius) {
        ofSetColor(40,40,40,150);
        ofDrawCircle(x, y, itemBoxRadius);
        ofSetColor(200,200,200,255);
        //float w = font_.getGlyphBBox(letter_);// getFontTexture() / 100 * 0.5;
        //ofLog() << w;
        float w = 10;
        font_.drawString(leter_, x - w, y + w); // should use font cariter width to compensate
    }
    
private:
    string          leter_;
    ofColor         colour_;
    ofTrueTypeFont  font_;
};

class UI {
public:
    UI(){
        itemBoxRadius_  = 30;
        width_          = 600;

        for ( int i =0; i < 26; i++) {
            items_.push_back({ lang::english[i] });
        }
    };
    
    ~UI(){};
    
    void drawItems (float x, float y) {
        float r = width_ * 0.5;
        
        //Items
        for (int i = 0; i < items_.size(); i++) {
            float a = -1.5707963268 + (6.2831853072 / items_.size()) * i;
            float xii = r * cos(a);
            float yii = r * sin(a);
            
            items_[i].draw(x + xii, y + yii, itemBoxRadius_ );
        }
    }
    
private:
    float           width_;
    float           itemBoxRadius_;
    vector<Item>    items_;
    
};

#endif /* UI_hpp */
