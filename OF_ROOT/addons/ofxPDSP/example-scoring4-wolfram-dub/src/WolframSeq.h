
#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"
#include "1D.h"


class WolframSeq : public pdsp::Sequence {
    
public:
    WolframSeq();

    void setup( int maxSteps, int maxOutputs, int rule, int generations, int caSide, int totalHeight, bool sendGateOff=false );
    
    void draw(int x, int y);
    
    atomic<int>     actionCode; // 0 advance | 1 clear | 2 random | 3 random & fill
    
    ofParameter<int>     threshold;
    ofParameter<int>     activeOuts;
    ofParameter<int>     steps;
    ofParameter<int>     rule;
    ofParameter<int>     division;
    ofParameter<float>   seedsDensity;
    ofParameter<bool>    reverse;
    ofParameter<float>   limiting;
    ofParameter<int>     dbRange;
    ofParameter<float>   gateLen;
    ofParameter<bool>    remake;
    
    bool                 gateOff;

    vector<float>   bars;    
    Automaton1D     ca;

    ofParameterGroup ui;

private:

    ofFbo   barsFbo;

    int     cah;
    int     caSide;
    int     barHeight;
    
    float   gate;

    int     storedRule;

    int     activeOutsStored;     

    int     maxSteps; // number of steps for each output
    int     maxOutputs;
    
    int     thresholdStored;
    
    double  sequenceLength; // division * steps
    float   scaling;

    vector<float> values; // support structure for calculating linear max

    static int number;
};

