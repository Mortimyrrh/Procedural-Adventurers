//
//  G_LSystemTree.hpp
//  noiseWall
//
//  Created by Mortimer Pavlitski on 25/04/2018.
//

#ifndef G_LSystemTree_hpp
#define G_LSystemTree_hpp

#include <stdio.h>
#include "ofxLSystemGrammar.h"

struct LSystemTreeType {
    int             genirationOrder;
    float           length;
    float           angle;
    vector<string>  algorithm;
    string          axiom;
};

namespace treeType {
    // unused tree algorithms
    // devloped from algorithmic beauty of plants book
    
    const LSystemTreeType simpleL01 = {
        4,
        120,
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
    
    const LSystemTreeType littleStrange = {
        3,
        70,
        60,
        {
            "0.33 -> F -> F[+F]F[‚-F]F",
            "0.33 -> F -> F[+F]F",
            "0.34 -> F -> F[‚-F]F",
        },
        "F"
    };
    
    const LSystemTreeType littleStrange2 = {
        3,
        70,
        50,
        {
            "0.33 -> F -> F[[+F]F[‚-F]F]-F",
            "0.33 -> F -> F[[+F]+F]F",
            "0.34 -> F -> F[[‚-F]F]-F"
        },
        "F"
    };
    
    const LSystemTreeType littleStrange3 = {
        3,
        70,
        50,
        { "F -> FF","X -> F-[[X]+X]+F[+FX]-X" },
        "FX"
    };

    // vexiloEdit Tree algorithm developed from
    // https://www.vexlio.com/blog/drawing-simple-organics-with-l-systems/
    
    const LSystemTreeType vexiloEdit = {
        4,
        150,
        30,
        {   "0.58 -> X -> F+[-F-XF-X][+FF][--XF[+X]][++F-X]",
            "0.27 -> X -> F-[+F+X][-FF][++XFF[-X]][--F+X]",
            "0.06 -> X -> FX[--X[+X]]",
            "0.05 -> X -> FX[+XF[-X]]" },
        "FFFFX"
    };
}

class G_LSystemTree {
public:
    G_LSystemTree( LSystemTreeType treeType, float x, float y, ofColor colour_, float lineWidth, int layerNum);
    ~G_LSystemTree();
    
    void genirate();
    void draw();
    float getXPos();
    
private:
    float           xPos_;
    float           yPos_;
    
    int             layerNum_;

    int             genirationOrder_;
    float           length_;
    float           angle_;
    vector<string>  algorithm_;
    string          axiom_;
    string          text_;
    
    ofColor         colour_;
    float           lineWidth_;
    ofPath          path_;
};

#endif /* G_LSystemTree_hpp */
