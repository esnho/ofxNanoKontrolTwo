//
//  ofxNanoKontrolTwo_hpp.cpp
//  ofxNanoKontrolTwo_hpp
//
//  Created by Luca Moroni on 21/03/2020.
//

#include "ofxNanoKontrolTwo.h"

void ofxNanoKontrolTwo::setup() {

    ofSetLogLevel(OF_LOG_VERBOSE);

    for (int i = 0; i < 8; i++) {
        controlsCallbacks controlCallbacksGroup;
        controlsValues controlValuesGroup;
        controlValuesGroup.knob = 0.0f;
        controlValuesGroup.slider = 0.0f;
        callbacks.ctrl.push_back(controlCallbacksGroup);
        values.ctrl.push_back(controlValuesGroup);

    }

    // print input ports to console
    midiIn.listInPorts();

    // open port by number (you may need to change this)
    midiIn.openPort(0);

    // don't ignore sysex, timing, & active sense messages,
    // these are ignored by default
    midiIn.ignoreTypes(false, false, false);

    // add this class as a listener
    midiIn.addListener(this);

    // print received messages to the console
    midiIn.setVerbose(false);
}

void ofxNanoKontrolTwo::newMidiMessage(ofxMidiMessage& msg) {
    // add the latest message to the message queue
    midiMessages.push_back(msg);

    // remove any old messages if we have too many
    while(midiMessages.size() > maxMessages) {
        midiMessages.erase(midiMessages.begin());
    }
}

void ofxNanoKontrolTwo::close() {
    // clean up
    midiIn.closePort();
    midiIn.removeListener(this);
}

void ofxNanoKontrolTwo::update(){
    for(unsigned int i = 0; i < midiMessages.size(); ++i) {
        ofxMidiMessage &message = midiMessages[i];

        if(message.status < MIDI_SYSEX) {
            //text << "chan: " << message.channel << endl;
            if(message.status == MIDI_CONTROL_CHANGE) {

//                cout << "message.control "<< message.control<< endl;
//                cout << "message.value "<< message.value<< endl;

                float value = (float) message.value / 127.0f;
                bool booleanValue = value > 0.0f;

                // the ctrlModulo identifies all right controls except for sliders which default midi number is >120 and need to be modulated with 120
                // controlIdentifier check which control of the right control groups has been touched
                int ctrlModulo = message.control % 120 < 8 ? message.control % 120 : message.control % 16;

                if (ctrlModulo < 8) {
                    int controlIdentifier = floor(message.control / 16.0f);

                    switch (controlIdentifier) {
                        case 1:
                            values.ctrl[ctrlModulo].knob = value;
                            ofNotifyEvent(callbacks.ctrl[ctrlModulo].knob, value);
                            break;
                        case 2:
                            values.ctrl[ctrlModulo].solo = booleanValue;
                            ofNotifyEvent(callbacks.ctrl[ctrlModulo].solo, booleanValue);
                            break;
                        case 3:
                            values.ctrl[ctrlModulo].mute = booleanValue;
                            ofNotifyEvent(callbacks.ctrl[ctrlModulo].mute, booleanValue);
                            break;
                        case 4:
                            values.ctrl[ctrlModulo].rec = booleanValue;
                            ofNotifyEvent(callbacks.ctrl[ctrlModulo].rec, booleanValue);
                            break;
                        default:
                            values.ctrl[ctrlModulo].slider = value;
                            ofNotifyEvent(callbacks.ctrl[ctrlModulo].slider, value);
                            break;
                    }
                } else if (message.control == 46) {
                    values.cycle = booleanValue;
                    ofNotifyEvent(callbacks.cycle, booleanValue);

                } else if (message.control == 58) {
                    values.track.left = booleanValue;
                    ofNotifyEvent(callbacks.track.left, booleanValue);

                } else if (message.control == 59) {
                    values.track.right = booleanValue;
                    ofNotifyEvent(callbacks.track.right, booleanValue);

                } else if (message.control == 43) {
                    values.player.rewind = booleanValue;
                    ofNotifyEvent(callbacks.player.rewind, booleanValue);

                } else if (message.control == 44) {
                    values.player.forward = booleanValue;
                    ofNotifyEvent(callbacks.player.forward, booleanValue);

                } else if (message.control == 42) {
                    values.player.stop = booleanValue;
                    ofNotifyEvent(callbacks.player.stop, booleanValue);

                } else if (message.control == 60) {
                    values.marker.set = booleanValue;
                    ofNotifyEvent(callbacks.marker.set, booleanValue);

                } else if (message.control == 61) {
                    values.marker.left = booleanValue;
                    ofNotifyEvent(callbacks.marker.left, booleanValue);

                } else if (message.control == 62) {
                    values.marker.right = booleanValue;
                    ofNotifyEvent(callbacks.marker.right, booleanValue);
                }

            }
        }
    }

    midiMessages.clear();

}
