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
    delayTime = *new Knob(20000);
    feedback = *new Knob(1);
}
DelayPedal::DelayPedal(){
    
}

float* DelayPedal::effect(float* input, int bufferSize){
    if(!bypass_btn.bypassed){
        for(int i = 0; i < bufferSize; i++){
            //params:
                //delay time
                //feedback
            input[i] = (input[i] + (float)mdl.dl((double)input[i], delayTime.getValue(), feedback.getValue()))/2;
        }
    }
    return input;
}

void DelayPedal::draw(){
    ofSetHexColor(0x00ff00);
    ofRectRounded(x,y,xsize, ysize, 8);
    bypass_btn.draw();
    input.draw();
    output.draw();
    delayTime.draw(x+(xsize/4), y+(ysize/4));
    feedback.draw(x+3*(xsize/4), y+(ysize/4));
}