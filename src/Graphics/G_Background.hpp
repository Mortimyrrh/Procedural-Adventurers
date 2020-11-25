//
//  G_Background.hpp
//  noiseWall
//
//  Created by Mortimer Pavlitski on 17/04/2018.
//

#ifndef G_Background_hpp
#define G_Background_hpp

#include <stdio.h>
#include "ofMain.h"

#include "G_LSystemTree.hpp"

class G_BackgroundLayer {
public:
    G_BackgroundLayer(float windowWidth, float windowHeight, ofColor colour, int layerNumber);
    ~G_BackgroundLayer();
    
    void draw(float xOffset, float yOffset, float windowWidth);
    void createPath(float paralaxXOffSet, float paralaxYOffSet);
    
private:
    void generate();

    float  windowWidth_;
    float  windowHeight_;

    int             layerNumber_;
    float           depth_;
    vector<float>   layerHeights_;
    ofPath          layerPath_;
    ofColor         colour_;
    float           paralaxSpeed_;
    
    vector<G_LSystemTree>  trees_;
};


class G_Background {
public:
    G_Background();
    
    void    setWindowPtr(float* windowWidth, float* windowHeight, float* xOffsetPtr);
    void    generate();
    void    update();
    void    draw(float xOffset, float yOffset, float windowWidth);
    
    void    resized(float windowWidth, float windowHeight);
    
    ofColor getColour();
    ofColor getSkyColour();
    
private:
    float   windowWidth_;
    float   windowHeight_;
    float   xOffset_;
    float   yOffset_;
    
    int     nLayers; // number of layers
    vector<G_BackgroundLayer> layers;
    
    ofColor         skyColour_;
    ofColor         colour_;

};


#endif /* G_Background_hpp */
