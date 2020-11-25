//
//  G_LSystemTree.cpp
//  noiseWall
//
//  Created by Mortimer Pavlitski on 25/04/2018.
//

#include "G_LSystemTree.hpp"

G_LSystemTree::G_LSystemTree( LSystemTreeType treeType, float xPos, float yPos, ofColor colour, float lineWidth, int layerNum) {
    xPos_       = xPos;
    yPos_       = yPos;
    layerNum_   = layerNum;
    colour_     = colour;
    lineWidth_  = lineWidth;
    
    genirationOrder_    = treeType.genirationOrder;
    length_             = treeType.length;
    angle_              = treeType.angle + ofRandom(-5, 5);
    algorithm_          = treeType.algorithm;
    axiom_              = treeType.axiom;
    
    length_ *= 0.1;
    
    length_ *= (0.5 + ( 0.2 * (6 - layerNum)));

    if (layerNum > 3) {
        genirationOrder_    = 3;
    } else {
        genirationOrder_    = 4;
    }
    
    vector<string> ls_output = ofxLSystemGrammar::buildSentences(algorithm_, genirationOrder_, axiom_);
    text_       = ls_output[genirationOrder_];
    
    genirate();
    
};

G_LSystemTree::~G_LSystemTree() {
    
};

void G_LSystemTree::genirate() {
    class Vec3D {
    public:
        Vec3D(float x, float y, float a) { x_ = x; y_ = y; a_ = a; };
        float x_;
        float y_;
        float a_;
    };
    
    path_.clear();
    path_.newSubPath();
    path_.POLYLINES;
    
    float drawingAngle  = ofDegToRad(270);
    float drawingXPos   = 0;
    float drawingYPos   = 0;
    std::vector <Vec3D> pointStack;

    path_.moveTo(drawingXPos, drawingYPos);

    for (char c : text_) {
        switch (c) {
            case 'F':
                drawingXPos += cos(drawingAngle) * length_;
                drawingYPos += sin(drawingAngle) * length_;
                path_.lineTo(drawingXPos, drawingYPos);
                break;
            case 'f':
                drawingXPos += cos(drawingAngle) * length_;
                drawingYPos += sin(drawingAngle) * length_;
                path_.moveTo(drawingXPos, drawingYPos);
                break;
            case '+':
                drawingAngle += ofDegToRad(angle_ + ofSignedNoise(-2, 2));
                break;
            case '-':
                drawingAngle -= ofDegToRad(angle_ + ofSignedNoise(-2, 2));
                break;
            case '[':
                // Push Drawing Context
                pointStack.push_back(Vec3D(drawingXPos, drawingYPos, drawingAngle));
                break;
            case ']':
                // Pop Drawing Context
                drawingXPos     = pointStack.back().x_;
                drawingYPos     = pointStack.back().y_;
                drawingAngle    = pointStack.back().a_;
                path_.moveTo(drawingXPos, drawingYPos);
                pointStack.pop_back();
                break;
        }
    }
    
    path_.setColor(colour_);
    path_.setStrokeWidth(lineWidth_);
    path_.setFilled(false);
}

void G_LSystemTree::draw() {
    ofPushView();

    ofTranslate(xPos_, yPos_);
    
    path_.draw();
    
    ofPopView();
}

float G_LSystemTree::getXPos()
{
    return xPos_;
}
