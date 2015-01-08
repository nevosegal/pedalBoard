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
    ~ofApp();
    
    //basic openframeworks functions
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
    void audioRequested(float * input, int bufferSize, int nChannels); /* output method */
    void audioReceived(float * input, int bufferSize, int nChannels); /* input method */
    
    int	initialBufferSize;
    int	sampleRate;
    
    //used for the previous mouse position.
    double prevx, prevy;
    
    //number of pedals.
    int numPedals;
    
    //A vector that stores the pedals.
    std::vector<Pedal*> pedals;
    
    //All the individual pedals with their type.
    DelayPedal dp;
    DistortionPedal distortion;
    FlangerPedal flanger;
    ChorusPedal chorus;
    
    //array to store the mic input.
    float *myInput;
    
    //variables for drawing the temporary line between pedals.
    double startX, startY, targetX, targetY;
    bool drawLine = false;
    int cableColor;
    
    //Audio in and out.
    InputOutput audioIn, audioOut;
    
    //background image
    ofImage background;
    ofxMaxiMix mymix;
    
    double outputs[2];
    
};
