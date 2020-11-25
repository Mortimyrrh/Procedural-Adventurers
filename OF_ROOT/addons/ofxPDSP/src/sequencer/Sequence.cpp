
#include "Sequence.h"

pdsp::Sequence::Sequence( double stepDivision ){ 
    modified = false;    
    setDivision(stepDivision);
    setLength(1.0);
    nextScore.reserve(PDSP_PATTERN_MESSAGE_RESERVE_DEFAULT);
    code = []() noexcept {};
    loopCounter = 0;
    id = 1;
    atomic_meter_percent = 0.0f;
}

pdsp::Sequence::Sequence() : Sequence (16.0){}

void pdsp::Sequence::setDivision( double value ){
    this->div = value;
    divMult = 1.0 / div;
}

void pdsp::Sequence::setLength( double value ){
    this->len = value;
}

double pdsp::Sequence::length() const{
    return len;
}

double pdsp::Sequence::division() const{
    return div;
}

void pdsp::Sequence::setTiming( double division, double length ){
    setDivision(division);
    setLength(length);
}

pdsp::Sequence::Sequence(const Sequence & other) {
    this->modified = other.modified.load();
    setDivision(other.div);
    score = other.score;
    nextScore.reserve(PDSP_PATTERN_MESSAGE_RESERVE_DEFAULT);
    nextScore = other.nextScore;
    code = other.code;
}

pdsp::Sequence::Sequence(Sequence && other) {
    this->modified = other.modified.load();
    setDivision(other.div);
    score = other.score;
    nextScore.reserve(PDSP_PATTERN_MESSAGE_RESERVE_DEFAULT);
    nextScore = other.nextScore;
    code = other.code;
}

pdsp::Sequence& pdsp::Sequence::operator= (const Sequence & other) {
    this->modified = other.modified.load();
    setDivision(other.div);
    score = other.score;
    nextScore.reserve(PDSP_PATTERN_MESSAGE_RESERVE_DEFAULT);
    nextScore = other.nextScore;
    code = other.code;
    return *this;
}

pdsp::Sequence& pdsp::Sequence::operator= (Sequence && other) {
    this->modified = other.modified.load();
    setDivision(other.div);
    score = other.score;
    nextScore.reserve(PDSP_PATTERN_MESSAGE_RESERVE_DEFAULT);
    nextScore = other.nextScore;
    code = other.code;
    return *this;
}


void pdsp::Sequence::set( std::initializer_list<float> init ) noexcept {
    if(modified==true){
        std::cout<<"[pdsp] warning! you have already set this Sequence, but it hasn't been processed yet, please set it once and wait for the changes to be effective before setting it again to avoid race conditions!\n";
        pdsp_trace();
    }
    
    nextScore.clear();
    
    double time=0.0;
    for (const float & value : init){
        if( value >= 0.0f){
            nextScore.push_back(  pdsp::ScoreMessage( time , value, 0) );            
        }
        time += divMult;
    }
    
    modified = true;
}


void pdsp::Sequence::set( std::initializer_list<std::initializer_list<float> >  init ) noexcept {
    if(modified==true){
        std::cout<<"[pdsp] warning! you have already set this Sequence, but it hasn't been processed yet, please set it once and wait for the changes to be effective before setting it again to avoid race conditions!\n";
        pdsp_trace();
    }

    nextScore.clear();

    int out = 0;
    for(const std::initializer_list<float> & list : init){
        double time = 0.0;
        for ( const float & value : list){
            if( value >= 0.0f){
                nextScore.push_back(  pdsp::ScoreMessage( time , value, out) );            
            }
           time += divMult;     
        }
        out++;
    }
    
    modified = true;
}

void pdsp::Sequence::set( std::initializer_list<float> init, double division, double length ) noexcept{
    setDivision(division);
    setLength(length);
    set(init);
}

void pdsp::Sequence::set(  std::initializer_list<std::initializer_list<float> >  init , double division, double length ) noexcept{
    setDivision(division);
    setLength(length);
    set(init);
}


void pdsp::Sequence::begin() noexcept{
    nextScore.clear();
}

void pdsp::Sequence::begin( double division, double length ) noexcept{
    setDivision(division);
    setLength(length);
    nextScore.clear();
}

void pdsp::Sequence::message(double step, float value, int outputIndex) noexcept {
    nextScore.push_back( pdsp::ScoreMessage( step * divMult, value, outputIndex) );
}

void pdsp::Sequence::end() noexcept{
    modified = true;
}

void pdsp::Sequence::messageVector( std::vector<float> vect, int outputIndex) {
    
    double time=0.0;
    for (const float & value : vect){
        if( value >= 0.0f){
            nextScore.push_back(  pdsp::ScoreMessage( time , value, outputIndex) );            
        }
        time += divMult;
    }
        
}

void pdsp::Sequence::trigVector( std::vector<float> vect, double gateLength, int outputIndex) {
    
    double time=0.0;
    double offTime = gateLength * divMult;
    for (const float & value : vect){
        if( value > 0.0f){
            nextScore.push_back(  pdsp::ScoreMessage( time,    value, outputIndex) );            
            nextScore.push_back(  pdsp::ScoreMessage( offTime , 0.0f, outputIndex) );            
        }
        time    += divMult;
        offTime += divMult;
    }
        
}

void pdsp::Sequence::trigVector( std::vector<float> vect, double gateLength, int outputIndex, float multiply) {
    
    double time=0.0;
    double offTime = gateLength * divMult;
    for (const float & value : vect){
        if( value > 0.0f){
            nextScore.push_back(  pdsp::ScoreMessage( time,    value*multiply, outputIndex) );            
            nextScore.push_back(  pdsp::ScoreMessage( offTime , 0.0f,          outputIndex) );            
        }
        time    += divMult;
        offTime += divMult;
    }
        
}


void pdsp::Sequence::line( double stepStart, float valueStart, double stepStopExclusive, float valueStopExclusive, int output, int granularity ){
    
    float value = valueStart;
    
    double steps = (stepStopExclusive - stepStart ) * granularity;
   
    double stepAdd = 1.0 / granularity;  
    float  valueAdd = ( valueStopExclusive - valueStart ) / steps;

    for( double s = stepStart; s< (double) stepStopExclusive; s += stepAdd ) {
        message( s, value, output);
        value += valueAdd;
    }

}



const std::vector<pdsp::ScoreMessage> & pdsp::Sequence::getScore() const{
    return score;
}

void pdsp::Sequence::executeGenerateScore() noexcept {
    code();
    if(modified){
        score.swap( nextScore ); // swap score in a thread-safe section
        std::sort (score.begin(), score.end(), messageSort); //sort the messages
        id = (id == 1) ? 2 : 1;
        modified = false;
    }
    loopCounter++;
}

int pdsp::Sequence::getChangeID() const {
    return id;
}


int pdsp::Sequence::counter() const {
    return loopCounter;
}

void pdsp::Sequence::resetCount() {
    loopCounter = 0;
}

float pdsp::Sequence::meter_percent() const {
    return atomic_meter_percent;
}

pdsp::SeqChange::SeqChange(){
    code = [&]() noexcept { return self; };
}

int pdsp::SeqChange::getNextPattern( int currentPattern, int size ) noexcept {
    self = currentPattern;
    return code();
}
