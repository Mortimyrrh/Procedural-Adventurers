
// ExtSequencer.h
// ofxPDSP
// Nicola Pisanti, MIT License, 2016

#ifndef PDSP_MESSAGES_EXTSEQUENCER_H_INCLUDED
#define PDSP_MESSAGES_EXTSEQUENCER_H_INCLUDED

namespace pdsp{
/*!
    @cond HIDDEN_SYMBOLS
*/ 
class MessageBuffer;

class ExtSequencer{
    
public:
    virtual void linkToMessageBuffer(MessageBuffer &messageBuffer) = 0;
    virtual void unlinkMessageBuffer(MessageBuffer &messageBuffer) = 0;
    
    virtual void process( int bufferSize ) = 0;
    virtual void close() = 0;
};
/*!
    @endcond
*/ 
}
#endif // PDSP_MESSAGES_EXTSEQUENCER_H_INCLUDED
