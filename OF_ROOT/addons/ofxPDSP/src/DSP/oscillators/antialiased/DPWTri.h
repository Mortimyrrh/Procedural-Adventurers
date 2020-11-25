
// DPWTri.h
// ofxPDSP
// Nicola Pisanti, MIT License, 2016


#ifndef PDSP_OSC_DPWTRIANGLE_H_INCLUDED
#define PDSP_OSC_DPWTRIANGLE_H_INCLUDED

#include "../base/Oscillator.h"

namespace pdsp {
    /*!
    @brief Antialiased Triangle Oscillator
    
    This is an oscillator that generates a differential parabolic triangle waveform, a special kind of antialiased triangle. Anyway in most cases CheapTriangle is a valid alternative as triangle waveform have really few aliased harmonics.
    */

class DPWTri : public Oscillator{
public:
    DPWTri();
    
    /*!
    @brief Sets "inc" as selected input and returns this Unit ready to be patched. It is mandatory to patch an "inc" output to this input for the DSP algorithm to function. Usually PMPhazor have the required out_inc().
    */   
    Patchable& in_inc();

private:
    void prepareOscillator( double sampleRate) override;
    void releaseOscillator() override;
    void oscillate( float* outputBuffer, const float* phaseBuffer, int bufferSize) noexcept override ;

    InputNode input_inc;
    float z_1;
};

}


#endif  // PDSP_OSC_DPWTRIANGLE_H_INCLUDED
