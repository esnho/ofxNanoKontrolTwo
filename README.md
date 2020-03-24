ofxNanoKontrolTwo
=====================================

Introduction
------------
Expose callbacks and values read from Korg Nanokontrol 2

Installation
------------
Just drop the folder into the `openFrameworks/addons/` folder.

Dependencies
------------
ofxMidi -> https://github.com/danomatika/ofxMidi

Compatibility
------------
Only tested on MacOS Catalina and OF v0.11.0

Available values and callbacks
------------
Checkout the example for a working demo.

```
instancedOfxNanoKontrolTwo.values
or
instancedOfxNanoKontrolTwo.callbacks

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
```
![Image description](https://raw.githubusercontent.com/esnho/ofxNanoKontrolTwo/master/example-app-preview.png)
