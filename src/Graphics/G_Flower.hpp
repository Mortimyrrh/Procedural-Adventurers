//
//  G_Flower.hpp
//  MusicalFlowers
//
//  Created by Mortimer Pavlitski on 01/05/2018.
//

#ifndef G_Flower_hpp
#define G_Flower_hpp

#include <stdio.h>
#include "WaveTable.hpp"

class G_Flower {
public:
    G_Flower(ofColor colour);
    ~G_Flower();
    
    void update(float timeElapsed);
    void draw();
    
private:
    float       height_;
    float       width_;
    float       radius_;
    
    int         nPetals_;
    float       angle_;
    float       speed_;
    float       z_;                 // buffer interpolation depth
    bool        isZAscending_;
    
    int nPoints;
    int nWave;
    
    ofPath      flowerHead_;
    WaveTable   waveTable_;
    
    ofColor     headColour_;
    ofColor     stemColour_;
    
    float       screenHeight_;
    float       oldPetalAngle_;
};

#endif /* G_Flower_hpp */
