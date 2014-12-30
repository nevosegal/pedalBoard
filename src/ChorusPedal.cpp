//
//  ChrousPedal.cpp
//  pedalBoard
//
//  Created by Nevo Segal on 29/12/2014.
//
//

#include "ChorusPedal.h"

ChorusPedal::ChorusPedal(double x, double y, int id)
:Pedal(x, y, id){
    numKnobs = 4;
    knobs = new Knob[numKnobs];
    knobs[0] = *new Knob(x+(xsize/4), y+(ysize/4), 1000, "Delay Time");
    knobs[1] = *new Knob(x+3*(xsize/4), y+(ysize/4), 1, "Feedback");
    knobs[2] = *new Knob(x+(xsize/4), y+(ysize/1.9), 10, "LFO Speed");
    knobs[3] = *new Knob(x+3*(xsize/4), y+(ysize/1.9), 1, "Depth");
}
ChorusPedal::ChorusPedal(){
    numKnobs = 4;
    knobs = new Knob[numKnobs];
}

float* ChorusPedal::effect(float* input, int bufferSize){
    if(!bypass_btn.bypassed){
        for(int i = 0; i < bufferSize; i++){
            //flange params:
            //input
            //delay time: tbd
            //feedback: 0-1
            //lfo speed: 0-10
            //depth: 0-1
            input[i] = chorus.chorus((double)input[i], knobs[0].getValue(), knobs[1].getValue(), knobs[2].getValue(), knobs[3].getValue());
        }
    }
    return input;
}

void ChorusPedal::draw(){
    ofFill();
    ofSetHexColor(0x885300);
    ofRectRounded(x,y,xsize, ysize, 8);
    bypass_btn.draw();
    input.draw();
    output.draw();
    for(int i = 0; i < numKnobs; i++){
        knobs[i].draw();
    }
}