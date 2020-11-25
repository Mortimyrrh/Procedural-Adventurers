//
//  WaveTable.cpp
//  MusicalFlowers
//
//  Created by Mortimer Pavlitski on 07/03/2018.
//

#include "WaveTable.hpp"

WaveTable::WaveTable(int bufferSize) {
    bufferSize_ = bufferSize;
    generateWaveTable();
}

WaveTable::~WaveTable() {
    
}

void WaveTable::generateWaveTable() {
    float stepSize = TWO_PI / bufferSize_;
    
    // Sine
    for(int i = 0; i < bufferSize_; i ++) {
        float x = sin(stepSize * i);
        buffer1_.push_back(x);
    }
    
    // Sqare
    for(int i = 0; i < bufferSize_; i ++) {
        if (buffer1_[i] > 0) {
            buffer2_.push_back(1);
        } else if (buffer1_[i] < 0) {
            buffer2_.push_back(-1);
        } else {
            buffer2_.push_back(0);
        }
    }
    
    // Noise
    for(int i = 0; i < bufferSize_; i ++) {
        buffer3_.push_back(ofRandom(-1, 1));
    }
}

float WaveTable::getSample(float x, float z) {
    if (z < 0 || z > 2) {
        ofLog() << "WaveTable out of range";
        ofLog() << z;
    }
    
    if(z <= 1) {
        return  (getIntupSampleFromBuffer(x, &buffer1_) * (1 - z)) +
                (getIntupSampleFromBuffer(x, &buffer2_) * (z));
    } else if(z <= 2) {
        return  (getIntupSampleFromBuffer(x, &buffer2_) * (2 - z)) +
                (getIntupSampleFromBuffer(x, &buffer3_) * (1 - z));
    }
};

//

int WaveTable::getBufferSize() {
    return bufferSize_;
};

//

float WaveTable::getIntupSampleFromBuffer(float i, vector <float>* buffer) {
    float   index       = fmod(i, bufferSize_);
    int     indexLow    = floor(index);
    int     indexHigh   = indexLow + 1;
    float   offset      = index - indexLow;
    
    float   dataLow     = buffer->operator[](indexLow);
    float   dataHigh    = buffer->operator[](indexHigh);
    
    return (dataLow  * (1 - offset)) + (dataHigh * offset);
};
