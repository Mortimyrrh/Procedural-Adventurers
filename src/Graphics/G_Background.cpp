//
//  G_Background.cpp
//  noiseWall
//
//  Created by Mortimer Pavlitski on 17/04/2018.
//

#include "G_Background.hpp"

G_BackgroundLayer::G_BackgroundLayer(float windowWidth, float windowHeight, ofColor colour, int layerNumber)
{
    windowWidth_       = windowWidth;
    windowHeight_      = windowHeight;
    colour_            = colour;
    layerNumber_       = layerNumber;
    paralaxSpeed_      = -0.15;
    
    generate();
}

G_BackgroundLayer::~G_BackgroundLayer() {
    
}

void G_BackgroundLayer::generate() {
    // genirate values
    ofSeedRandom();
    float r     = ofRandom(1000);
    float r2    = ofRandom(1000);
    
    int treeGap = 0;
    
    for (int i = 0; i < 100000; i++)
    {
        float y = (((windowHeight_) * 0.05) * layerNumber_)
        + (ofNoise(r + (i * 0.0015)) * ((windowHeight_) * 0.5));
        
        layerHeights_.emplace_back(y);

        if (ofRandom(100.0) <= (layerNumber_ + 1) * (layerNumber_ + 1) * 0.0127) {
            // make in to clusters
            if (ofNoise(r2 + (i * 0.0015)) > 0.15 && treeGap > 60) {
                trees_.push_back({ treeType::vexiloEdit, static_cast<float>(i), -y, colour_, static_cast<float>((7 - layerNumber_) * 0.3), layerNumber_});
                treeGap = 0;
            }
        }
        treeGap++;
    }
}

void G_BackgroundLayer::createPath(float paralaxXOffSet, float paralaxYOffSet) {
    layerPath_.clear();
    layerPath_.newSubPath();
    
    int i;
    
    for (i = paralaxXOffSet; i < paralaxXOffSet + (windowWidth_) + 30; i+= 30){ //30
        layerPath_.lineTo(i - paralaxXOffSet, - paralaxYOffSet -layerHeights_[i]);
    }

    layerPath_.lineTo(windowWidth_, -layerHeights_[i]);
    layerPath_.lineTo(windowWidth_, 0);
    layerPath_.lineTo(0, 0);
    layerPath_.lineTo(0, -layerHeights_[paralaxXOffSet]);
    
    layerPath_.setFilled(true);
    layerPath_.setColor(colour_);
}

void G_BackgroundLayer::draw(float xOffset, float yOffset, float windowWidth) {
    windowWidth_ = windowWidth;
    
    float paralaxXOffSet = 50000 + ((xOffset) * (7 - layerNumber_) * paralaxSpeed_);
    
    float paralaxYOffSet = 150 + ((-yOffset + 200) * (7 - layerNumber_) * paralaxSpeed_);
    
    //draw path
    createPath(paralaxXOffSet, paralaxYOffSet);
    
    ofPushView();
    
    layerPath_.draw();
    
    for(int i = 0; i < trees_.size(); i++) {
        if(trees_[i].getXPos() + 300 > paralaxXOffSet && trees_[i].getXPos() - 300 < paralaxXOffSet + (windowWidth_)) {
            ofPushView();
            ofTranslate(-paralaxXOffSet, -paralaxYOffSet);
            trees_[i].draw();
            ofPopView();
        }
    }

    ofPopView();
}

//

G_Background::G_Background()
{
    nLayers = 6;
}

void G_Background::generate() {
    float hue = ofRandom(255);
    
    for (int i = 0; i < nLayers; i++){
        layers.emplace_back(windowWidth_, windowHeight_,
            ofColor::fromHsb(fmod(hue + ((nLayers + 1 - i) * 7), 255),
                             150 + (i * (85 / nLayers)),
                             30 + ((200 / nLayers) * (nLayers - i))),
                             nLayers - i
                            );
    }
    
    colour_     = ofColor::fromHsb(hue, 200, 180);
    skyColour_  = ofColor::fromHsb(hue, 70, 255);    
}

void G_Background::draw(float xOffset, float yOffset, float windowWidth) {
    
    ofPushView();
    ofTranslate(-xOffset, yOffset);
    
    xOffset_ = xOffset;
    yOffset_ = yOffset;
    
    for (int i = 0; i < layers.size(); i++) {
        layers[i].draw(xOffset_, yOffset_, windowWidth);
    }
    
    ofPopView();
}

void G_Background::update() {

}


void G_Background::resized(float windowWidth, float windowHeight) {
        windowWidth_  = windowWidth;
        windowHeight_ = windowHeight;
}

ofColor G_Background::getColour() {
    return colour_;
}

ofColor G_Background::getSkyColour() {
    return skyColour_;
}
