#pragma once

#include "ofMain.h"
#include <ofxNanoKontrolTwo.h>

class ofApp : public ofBaseApp{

    public:
        void setup();
        void update();
        void draw();
        void exit();

    void onCycle(bool & state);
    void onStop(bool & state);
    void onSliderOne(float & value);

    ofxNanoKontrolTwo nanoK;

};
