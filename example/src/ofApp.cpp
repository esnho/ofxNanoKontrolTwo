#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofClear(0.75, 1);

    nanoK.setup();

    /*
     available nanoK.values and nanoK.callbacks:
        cycle -> bool
        track
            left -> bool
            right -> bool
        player
            rewind -> bool
            forward -> bool
            stop -> bool
            play -> bool
            rec -> bool
        marker
            set -> bool
            left -> bool
            right -> bool
        ctrl is a vector from 0 to 7
            knob -> float value 0.0 to 1.0
            slider -> float value 0.0 to 1.0
            solo -> bool
            mute -> bool
            rec -> bool
    */

    ofAddListener(nanoK.callbacks.cycle, this, &ofApp::onCycle);
    ofAddListener(nanoK.callbacks.player.stop, this, &ofApp::onStop);
    ofAddListener(nanoK.callbacks.ctrl[0].slider, this, &ofApp::onSliderOne);

    ofSetBackgroundAuto(false);
}

//--------------------------------------------------------------
void ofApp::update(){
    nanoK.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofDrawBitmapStringHighlight("Move the knobs", 20, 20);
    ofDrawBitmapStringHighlight("Move the first slider", 20, 40);
    ofDrawBitmapStringHighlight("Press the CYCLE button", 20, 60);
    ofDrawBitmapStringHighlight("Press the STOP button", 20, 80);
    for (int i = 0; i < 8; i++) {
        ofDrawBitmapStringHighlight(ofToString(nanoK.values.ctrl[i].knob, 3), (100 * i) + 20, 100);
    }
}

void ofApp::exit() {
    nanoK.close();
}

//--------------------------------------------------------------
void ofApp::onCycle(bool & state) {
    if (state) {
        ofSetColor( 255, 0, 0, 255 );
    } else {
        ofSetColor( 0, 255, 0, 255 );
    }

    int x = (int)ofRandom(0, ofGetWindowWidth());
    int y = (int)ofRandom(0, ofGetWindowHeight());
    ofDrawRectangle(x,y,ofRandom(100),ofRandom(100));
}

//--------------------------------------------------------------
void ofApp::onStop(bool & state) {
    ofClear(0.75, 1);
}

//--------------------------------------------------------------
void ofApp::onSliderOne(float & value) {
    ofSetColor( ofRandom(255), ofRandom(255), ofRandom(255), 255 );
    ofDrawCircle(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2, value * ofGetWindowHeight());
}
