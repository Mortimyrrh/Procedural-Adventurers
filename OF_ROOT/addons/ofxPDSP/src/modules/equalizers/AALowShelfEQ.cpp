
#include "AALowShelfEQ.h"

void pdsp::AALowShelfEQ::patch(){

    addModuleInput("0", upsampler0);
    addModuleInput("1", upsampler1);
    addModuleOutput("0", downsampler0);
    addModuleOutput("1", downsampler1);
    
    addModuleInput("freq", freq);
    addModuleInput("Q", Q);
    addModuleInput("gain", gain);   
    
    eq0.setOversampleLevel(2);
    eq1.setOversampleLevel(2);
    upsampler0 >> eq0 >> downsampler0;
    upsampler1 >> eq1 >> downsampler1;   
     
    freq >> eq0.in_freq();
    freq >> eq1.in_freq();
    Q >> eq0.in_Q();
    Q >> eq1.in_Q();
    gain >> eq0.in_gain();
    gain >> eq1.in_gain();
    
    freq.set(10000.0f);
    Q.set(0.707f);
    gain.set(0.0f);   
}

pdsp::Patchable& pdsp::AALowShelfEQ::in_0(){
    return in("0");
}
    
pdsp::Patchable& pdsp::AALowShelfEQ::in_1(){
    return in("1");
}

pdsp::Patchable& pdsp::AALowShelfEQ::in_freq(){
    return in("freq");
}

pdsp::Patchable& pdsp::AALowShelfEQ::in_Q(){
    return in("Q");
}

pdsp::Patchable& pdsp::AALowShelfEQ::in_gain(){
    return in("gain");
}

pdsp::Patchable& pdsp::AALowShelfEQ::out_0(){
    return out("0");
}

pdsp::Patchable& pdsp::AALowShelfEQ::out_1(){
    return out("1");
}
