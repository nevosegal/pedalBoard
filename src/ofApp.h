#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "Pedal.h"
#include "DelayPedal.h"
#include "DistortionPedal.h"
#include "ChorusPedal.h"
#include "FlangerPedal.h"
#include "InputOutput.h"
#include <vector>


class ofApp : public ofBaseApp{
    
public:
    ~ofApp();/* destructor is very useful */
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void exit();
    void drawInOut();
    void audioRequested 	(float * input, int bufferSize, int nChannels); /* output method */
    void audioReceived 	(float * input, int bufferSize, int nChannels); /* input method */
    
    int		initialBufferSize; /* buffer size */
    int		sampleRate;
    double prevx, prevy;
    int numPedals;
    std::vector<Pedal*> pedals;
    DelayPedal dp;
    DistortionPedal distortion;
    FlangerPedal flanger;
    ChorusPedal chorus;
    float *myInput;
    double startX, startY, targetX, targetY;
    bool drawLine = false;
    int cableHoverColor;
    InputOutput audioIn, audioOut;
    ofImage background;
    
};
