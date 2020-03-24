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

                {
                    // the ctrlModulo identifies all right controls except for sliders which default midi number is >120 and need to be modulated with 120
                    // controlIdentifier check which control of the right control groups has been touched
                    int ctrlModulo = message.control % 16;
                    ctrlModulo = message.control % 120 < 8 ? message.control % 120 : ctrlModulo;

                    if (ctrlModulo < 8) {
                        int controlIdentifier = floor(message.control / 16.0f);

                        switch (controlIdentifier) {
                            case 1:
                                ofNotifyEvent(callbacks.ctrl[ctrlModulo].knob, value);
                                values.ctrl[ctrlModulo].knob = value;
                                break;
                            case 2:
                                ofNotifyEvent(callbacks.ctrl[ctrlModulo].solo, booleanValue);
                                values.ctrl[ctrlModulo].solo = booleanValue;
                                break;
                            case 3:
                                ofNotifyEvent(callbacks.ctrl[ctrlModulo].mute, booleanValue);
                                values.ctrl[ctrlModulo].mute = booleanValue;
                                break;
                            case 4:
                                ofNotifyEvent(callbacks.ctrl[ctrlModulo].rec, booleanValue);
                                values.ctrl[ctrlModulo].rec = booleanValue;
                                break;
                            default:
                                ofNotifyEvent(callbacks.ctrl[ctrlModulo].slider, value);
                                values.ctrl[ctrlModulo].slider = value;
                                break;
                        }
                    }
                }

                if (message.control == 46) {
                    ofNotifyEvent(callbacks.cycle, booleanValue);
                    values.cycle = booleanValue;
                }

                if (message.control == 58) {
                    ofNotifyEvent(callbacks.track.left, booleanValue);
                    values.track.left = booleanValue;
                }

                if (message.control == 59) {
                    ofNotifyEvent(callbacks.track.right, booleanValue);
                    values.track.right = booleanValue;
                }

                if (message.control == 43) {
                    ofNotifyEvent(callbacks.player.rewind, booleanValue);
                    values.player.rewind = booleanValue;
                }

                if (message.control == 44) {
                    ofNotifyEvent(callbacks.player.forward, booleanValue);
                    values.player.forward = booleanValue;
                }

                if (message.control == 42) {
                    ofNotifyEvent(callbacks.player.stop, booleanValue);
                    values.player.stop = booleanValue;
                }

                if (message.control == 60) {
                    ofNotifyEvent(callbacks.marker.set, booleanValue);
                    values.marker.set = booleanValue;
                }

                if (message.control == 61) {
                    ofNotifyEvent(callbacks.marker.left, booleanValue);
                    values.marker.left = booleanValue;
                }

                if (message.control == 62) {
                    ofNotifyEvent(callbacks.marker.right, booleanValue);
                    values.marker.right = booleanValue;
                }

            }
        }
    }

    midiMessages.clear();

}
