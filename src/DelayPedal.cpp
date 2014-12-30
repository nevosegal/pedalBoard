//
//  DelayPedal.cpp
//  pedalBoard
//
//  Created by Nevo Segal on 16/12/2014.
//
//

#include "DelayPedal.h"

DelayPedal::DelayPedal(double x, double y, int id)
:Pedal(x, y, id){
    numKnobs = 2;
    knobs = new Knob[numKnobs];
    knobs[0] = *new Knob(x+(xsize/4), y+(ysize/4), 20000, "Delay Time");
    knobs[1] = *new Knob(x+3*(xsize/4), y+(ysize/4), 1, "Feedback");
}

DelayPedal::DelayPedal(){
    numKnobs = 2;
    knobs = new Knob[numKnobs];
}

float* DelayPedal::effect(float* input, int bufferSize){
    if(!bypass_btn.bypassed){
        for(int i = 0; i < bufferSize; i++){
            input[i] = (input[i] + (float)mdl.dl((double)input[i], knobs[0].getValue(), knobs[1].getValue()))/2;
        }
    }
    return input;
}

void DelayPedal::draw(){
    ofFill();
    ofSetHexColor(0x075C00);
    ofRectRounded(x,y,xsize, ysize, 8);
    bypass_btn.draw();
    input.draw();
    output.draw();
    for(int i = 0; i < numKnobs; i++){
        knobs[i].draw();
    }
    ofRectangle headerRect = header.getStringBoundingBox(ofToString("Delay"), 0, 0);
    header.drawString("Delay", this->x + (this->xsize/2) - (headerRect.width/2) , this->y+this->ysize - 20);
}