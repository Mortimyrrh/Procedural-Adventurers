
// LowShelfEQ.h
// ofxPDSP
// Nicola Pisanti, MIT License, 2016

#ifndef PDSP_MODULE_LOWSHELFEQ_H_INCLUDED
#define PDSP_MODULE_LOWSHELFEQ_H_INCLUDED

#include "../../DSP/pdspCore.h"
#include "../../DSP/filters/biquads/BiquadLowShelf.h"
#include "../../DSP/resamplers/IIRUpSampler2x.h"
#include "../../DSP/resamplers/IIRDownSampler2x.h"

namespace pdsp{
    
    /*!
    @brief Low Shelf Equalizer
    */  
       
class LowShelfEQ : public Patchable {
    

public:
    LowShelfEQ(){ patch(); };
    LowShelfEQ(const LowShelfEQ& other){ patch(); };
    LowShelfEQ& operator=(const LowShelfEQ& other){ return *this; };

    
    /*!
    @brief Sets "0" as selected input and returns this module ready to be patched. This is the default input. This is the left input channel.
    */      
    Patchable& in_0();

    /*!
    @brief Sets "1" as selected input and returns this module ready to be patched. This is the right input channel.
    */     
    Patchable& in_1();

    /*!
    @brief Sets "freq" as selected input and returns this module ready to be patched. This is the frequency at which the EQ operates.
    */      
    Patchable& in_freq();
    
    /*!
    @brief Sets "Q" as selected input and returns this module ready to be patched. This is the "quality" factor of the EQ and controls the shape of the EQ at the corner frequency.
    */     
    Patchable& in_Q();
    
    /*!
    @brief Sets "gain" as selected input and returns this module ready to be patched. This is the amount of gain to add or remove at the set frequency.
    */     
    Patchable& in_gain();
    
    /*!
    @brief Sets "0" as selected output and returns this module ready to be patched. This is the default output. This is the left output channel.
    */  
    Patchable& out_0();
    
    /*!
    @brief Sets "1" as selected output and returns this module ready to be patched. This is the right output channel. If you don't patch this output the effect will behave as a mono EQ.
    */  
    Patchable& out_1();
            
            
private:
    void patch ();
    
    PatchNode   freq;
    PatchNode   Q;
    PatchNode   gain;
    PatchNode   input0;
    PatchNode   input1;
    
    BiquadLowShelf  eq0;
    BiquadLowShelf  eq1;
    
    
};

} // pdsp namespace end


#endif // PDSP_MODULE_LOWSHELFEQ_H_INCLUDED
