//
//  LSystemTree.hpp
//  LSystemTrees
//
//  Created by Mortimer Pavlitski on 29/11/2017.
//

#ifndef LSystemTree_hpp
#define LSystemTree_hpp

#include <stdio.h>

struct LSystemTreeType {
    int             genirationOrder;
    float           length;
    float           angle;
    vector<string>  algorithm;
    string          axiom;
};

namespace treeType {
    const LSystemTreeType simpleL01 = {
        4,
        200,
        20,
        { "F-> FF+[+F-F-F]-[-F+F+F]" },
        "F"
    };
    
    const LSystemTreeType simpleL02 = {
        2,
        200,
        20,
        { "F-> FF+[+F-F-F]-[-F+F+F]" },
        "F"
    };
    
    const LSystemTreeType simpleL03 = {
        4,
        200,
        45,
        { "F -> FF","X -> F-[[X]+X]+F[+FX]-X" },
        "FX"
    };
    
    const LSystemTreeType stickThing01 = {
        5,
        200,
        60,
        { "0.33 -> F -> F[+F]F[‚-F]F",
          "0.33 -> F -> F[+F]F",
          "0.34 -> F -> F[‚-F]F" },
        "F"
    };
    
    const LSystemTreeType squareThing01 = {
        3,
        20,
        90,
        {"F -> F+f-FF+F+FF+Ff+FF-f+FF-F-FF-Ff-FFF", "f -> ffffff" },
        "F"
    };
    
    const LSystemTreeType ballThing01 = {
        3,
        200,
        60,
        { "F-> F+[+F-F]-[-F+F+F]" },
        "F"
    };
    
    const LSystemTreeType ballThing02 = {
        3,
        200,
        60,
        { "F->FF+[+F-F-F]-[-F+F+F]" },
        "F"
    };
}

class LSystemTree {
public:
    // LSystemTree
    LSystemTree( LSystemTreeType treeType ){
        genirationOrder_    = treeType.genirationOrder;
        length_             = treeType.length;
        angle_              = treeType.angle;
        algorithm_          = treeType.algorithm;
        axiom_              = treeType.axiom;
        
        for(int i = 0; i < genirationOrder_; i++){ length_ *= 0.5; }

        vector<string> ls_output = ofxLSystemGrammar::buildSentences(algorithm_, genirationOrder_, axiom_);
        text = ls_output[genirationOrder_];
    };
    
    ~LSystemTree(){};
    
    //draw
    void draw(float x, float y) {
        ofPushMatrix();
        {
            ofSetColor(255, 255, 255, 60);
            ofSetLineWidth(5);
            ofTranslate(x, y);
            for (char c : text) {
                switch (c) {
                    case 'F':
                        ofDrawLine(0, 0, 0, -length_);
                        ofTranslate(0, -length_);
                        break;
                    case 'f':
                        ofTranslate(0, -length_);
                        break;
                    case 'G':
                        ofDrawLine(0, 0, 0, -length_);
                        ofTranslate(0, -length_);
                        break;
                    case '+':
                        ofRotate(angle_ + ofSignedNoise(-1, 1));
                        break;
                    case '-':
                        ofRotate(-angle_ + ofSignedNoise(-1, 1));
                        break;
                    case '[':
                        ofPushView();
                        break;
                    case ']':
                        ofPopView();
                        break;
                }
            }
        }
        ofPopMatrix();
    }
    
private:
    int             genirationOrder_;
    float           length_;
    float           angle_;
    vector<string>  algorithm_;
    string          axiom_;
    
    string          text;
};

#endif /* LSystemTree_hpp */
