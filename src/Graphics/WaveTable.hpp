//
//  WaveTable.hpp
//  MusicalFlowers
//
//  Created by Mortimer Pavlitski on 07/03/2018.
//

#ifndef WaveTable_hpp
#define WaveTable_hpp

#include "ofMain.h"
#include <stdio.h>

class WaveTable {
public:
    WaveTable(int bufferSize);
    ~WaveTable();

    void    generateWaveTable();
    
    float   getSample(float x, float z);    // z: wavetable depth
    int     getBufferSize();

private:
    float getIntupSampleFromBuffer(float i, vector <float>* buffer);

    vector <float>  buffer1_;
    vector <float>  buffer2_;
    vector <float>  buffer3_;

    int             bufferSize_;
};

#endif /* WaveTable_hpp */
