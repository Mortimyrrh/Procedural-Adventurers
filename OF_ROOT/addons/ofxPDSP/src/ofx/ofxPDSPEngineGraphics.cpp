
#include "ofxPDSPEngineGraphics.h"

void ofxPDSPEngineGraphics::setParent ( pdsp::ScoreProcessor & score ){
    this->score = &score;
    posX = 0;
    posY = 0;
}

void ofxPDSPEngineGraphics::setup( int w, int hFold, std::initializer_list<int> sectionsH, std::initializer_list<int> sectionsOuts ) {
    
    // init plotters
    sectionsHeights.resize( score->sections.size() );
    
    int s = 0;
    for ( const int & h : sectionsH){
        sectionsHeights[s] = h;
        s++;
    }
    for( ; s<(int)sectionsHeights.size(); ++s){
        sectionsHeights[s] = 0;
    }
    
    
    plotters.resize ( score->sections.size()  );
    
    s = 0;
    for ( const int & outs : sectionsOuts){
        if( s<(int)sectionsHeights.size() ){
            sectionsHeights[s] *= outs;
            plotters[s].setup( w, sectionsHeights[s], outs, score->sections[s] );
        }
        s++;
    }    
    for( ; s<(int)sectionsHeights.size(); ++s){
        plotters[s].setup( w, sectionsHeights[s], 0, score->sections[s] );
    }
     
    // finished plotters init
    
    this->hFold = hFold;
    this->width = w;
    
    // keys init
    assignedKeys.resize( score->sections.size() );
    for (int i=0; i< (int)assignedKeys.size(); ++i){
        assignedKeys[i].resize( score->sections[i].getCellsNumber() );
        for (int k = 0; k<(int)assignedKeys[i].size(); ++k){
            assignedKeys[i][k] = 1024; // out of range
        }
    }
    
    playStopKey = 1024;
    blink = 0;
    
    // for robustness set color again
    setColor ( this->color );
}


void ofxPDSPEngineGraphics::setColor( ofColor color ){
    this->color = color;
    for (auto & plotter : plotters) {
        plotter.setColor(color);
    }
}

void ofxPDSPEngineGraphics::setRange(int section, int index, float min, float max ){
    if(section < 0) section = 0;
    if(section >= (int)plotters.size()) section = plotters.size() -1;
    plotters[section].setRange( index, min, max );
}


void ofxPDSPEngineGraphics::drawGraphics() {
    
    ofPushStyle();
    
    int y = 0;
    int spacing = 5;
    int offsetX = 0;
    

    
    for(int i=0; i<(int)plotters.size(); ++i){
        
        plotters[i].update();
        

        ofPushMatrix();
            ofTranslate( offsetX, y );
            plotters[i].draw();
            // now draw lables
               
            ofSetColor( color );
            int numCells = plotters[i].getCellsNumber();
            float cellW = plotters[i].getCellWidth();
            for (int k=0; k<numCells; ++k){
                string label = "(";
                label += (char) assignedKeys[i][k];
                label += ") ";
                label += score->sections[i].getLabel(k);
                if( score->sections[i].meter_current() == k || score->sections[i].meter_next() != k || blink > 4 ){
                    ofDrawBitmapString ( label, cellW*k + 5.0f, 14.0f );
                } 
        
            }
        ofPopMatrix();

        y += ( sectionsHeights[i] + 20 + spacing );
        
        if(y > hFold ){
            y = 0; 
            offsetX += (width + spacing );
        }
    }
    
    ofPopStyle();

    blink++;
    if (blink == 8) blink = 0;
}

void ofxPDSPEngineGraphics::setPosition( int x, int y ) {
    posX = x;
    posY = y;
}

void ofxPDSPEngineGraphics::draw( int x, int y ) {
    ofPushMatrix();
    ofTranslate( x, y );
    drawGraphics();
    ofPopMatrix();
}

void ofxPDSPEngineGraphics::draw( ) {
    ofPushMatrix();
    ofTranslate( posX, posY );
    drawGraphics();
    ofPopMatrix();
}


void ofxPDSPEngineGraphics::keys( std::initializer_list<std::initializer_list<char>> initArray, int stopAndPlayKey, bool quantize, double quantizeTime ) {
    
    int s = 0;
    for(const std::initializer_list<char> & list : initArray){
        int k = 0;
        for ( const char & key : list){
            if( k < score->sections[s].getCellsNumber() ){
                assignedKeys[s][k] = key;
            }
            k++;
        }
        s++;
    }
    this->quantize = quantize;
    this->quantizeTime.resize(assignedKeys.size());
    
    for( auto & value : this->quantizeTime ) {
        value = quantizeTime;
    }
    
    playStopKey = stopAndPlayKey;
    // now add keyPressed to listeners
    
    ofAddListener( ofEvents().keyPressed, this, &ofxPDSPEngineGraphics::keyPressed);  
}

void ofxPDSPEngineGraphics::keys( std::initializer_list<std::initializer_list<char>> initArray, int stopAndPlayKey, std::initializer_list<double> quantizeArray) {
    
    int s = 0;
    for(const std::initializer_list<char> & list : initArray){
        int k = 0;
        for ( const char & key : list){
            if( k < score->sections[s].getCellsNumber() ){
                assignedKeys[s][k] = key;
            }
            k++;
        }
        s++;
    }

    this->quantize = true;

    this->quantizeTime.resize(assignedKeys.size());

    int q = 0;
    for( const double & quant : quantizeArray ){
        if( q < (int) quantizeTime.size() ){
            quantizeTime[q] = quant;
        }
        q++;
    }
    for ( ; q < (int) quantizeTime.size(); ++q ){
        quantizeTime[q] = 1.0;
    }
    
    playStopKey = stopAndPlayKey;
    // now add keyPressed to listeners
    
    ofAddListener( ofEvents().keyPressed, this, &ofxPDSPEngineGraphics::keyPressed);  
}

void ofxPDSPEngineGraphics::disableKeys() {
    ofRemoveListener( ofEvents().keyPressed, this, &ofxPDSPEngineGraphics::keyPressed);  
}


void ofxPDSPEngineGraphics::keyPressed ( ofKeyEventArgs& eventArgs ) {
    
    for(int s = 0; s < (int) assignedKeys.size(); ++s ){
        for (int k = 0; k< (int) assignedKeys[s].size(); ++k){
            if( eventArgs.key == assignedKeys[s][k] ){
                score->sections[s].launchCell( k, quantize, quantizeTime[s] );
            }
        }
    }
    
    if( eventArgs.key == playStopKey ){
        if( score->isPlaying() ){
            score->stop();
        }else{
            score->play();
        }
    }
    
}
