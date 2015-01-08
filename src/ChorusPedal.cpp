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
    
    //creating the knobs
    numKnobs = 4;
    knobs = new Knob[numKnobs];
    knobs[0] = *new Knob(x+(xsize/4), y+(ysize/4), 1000, "Delay Time");
    knobs[1] = *new Knob(x+3*(xsize/4), y+(ysize/4), 1, "Feedback");
    knobs[2] = *new Knob(x+(xsize/4), y+(ysize/2), 10, "LFO Speed");
    knobs[3] = *new Knob(x+3*(xsize/4), y+(ysize/2), 1, "Depth");
}
ChorusPedal::ChorusPedal(){
    numKnobs = 4;
    knobs = new Knob[numKnobs];
}

//as this is a chorusPedal, I use a chorus effect :P.
float* ChorusPedal::effect(float* input, int bufferSize){
    if(!bypass_btn.bypassed){
        for(int i = 0; i < bufferSize; i++){
            //I pass the knobs values directly to the chorus function.
            input[i] = chorus.chorus((double)input[i], knobs[0].getValue(), knobs[1].getValue(), knobs[2].getValue(), knobs[3].getValue());
        }
    }
    return input;
}

//chrousPedal specific draw function.
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
    ofRectangle headerRect = header.getStringBoundingBox(ofToString("Chorus"), 0, 0);
    header.drawString("Chorus", this->x + (this->xsize/2) - (headerRect.width/2) , this->y+this->ysize - 20);
}