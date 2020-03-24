//
//  ofxNanoKontrolTwo_hpp.hpp
//  ofxNanoKontrolTwo_hpp
//
//  Created by Luca Moroni on 21/03/2020.
//

#ifndef ofxNanoKontrolTwo_hpp
#define ofxNanoKontrolTwo_hpp

#include "ofMain.h"
#include <ofxMidi.h>

class ofxNanoKontrolTwo : public ofxMidiListener{

struct trackCallbacks {
    ofEvent<bool> left;
    ofEvent<bool> right;
};

struct playerCallbacks {
    ofEvent<bool> rewind;
    ofEvent<bool> forward;
    ofEvent<bool> stop;
    ofEvent<bool> play;
    ofEvent<bool> rec;
};

struct markerCallbacks {
    ofEvent<bool> set;
    ofEvent<bool> left;
    ofEvent<bool> right;
};

struct controlsCallbacks {
    ofEvent<float> knob;
    ofEvent<float> slider;
    ofEvent<bool> solo;
    ofEvent<bool> mute;
    ofEvent<bool> rec;
};

struct callbacksStruct {
    ofEvent<bool> cycle;
    trackCallbacks track;
    playerCallbacks player;
    markerCallbacks marker;
    vector<controlsCallbacks> ctrl;
};

struct trackValues {
    bool left;
    bool right;
};
struct playerValues {
    bool rewind;
    bool forward;
    bool stop;
    bool play;
    bool rec;
};

struct markerValues {
    bool set;
    bool left;
    bool right;
};

struct controlsValues {
    float knob;
    float slider;
    bool solo;
    bool mute;
    bool rec;
};

struct valuesStruct {
    bool cycle;
    trackValues track;
    playerValues player;
    markerValues marker;
    vector<controlsValues> ctrl;
};

public:
    void setup();
    void update();
    void close();

    void newMidiMessage(ofxMidiMessage& eventArgs);

    callbacksStruct callbacks;
    valuesStruct values;

    std::size_t maxMessages = 10; //< max number of messages to keep track of

private:
    ofxMidiIn midiIn;
    std::vector<ofxMidiMessage> midiMessages;


};

#endif /* ofxNanoKontrolTwo_hpp */
