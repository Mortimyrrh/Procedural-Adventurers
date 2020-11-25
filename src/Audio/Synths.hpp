//
//  Synths.hpp
//
//  Created by Mortimer Pavlitski on 28/03/2018.
//

#ifndef Synths_hpp
#define Synths_hpp

#include <stdio.h>

class FMSynth : public pdsp::Patchable{
public:
    FMSynth() {
        patch();
    }

    void patch() {
        addModuleInput("trig", env.in_trig());
        addModuleInput("pitch", osc.in_pitch());
        addModuleOutput("signal", amp );
        
        //patching
        env.set(0.0f, 100.0f, 350.0f) * 0.25f >> amp.in_mod();
        env * 0.10f >> osc.in_fb() >> amp;
    }
    
    void setAmpEnv(float attack, float hold, float release) {
        env.set(attack, hold, release);
    }
    
private:
    pdsp::Amp amp;
    pdsp::FMOperator osc;
    pdsp::AHR env;
};

#endif /* Synths_hpp */
