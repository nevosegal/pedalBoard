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
    
}
DelayPedal::DelayPedal(){
    
}

float* DelayPedal::effect(float* input, int bufferSize){
    if(!bypass_btn.bypassed){
        for(int i = 0; i < bufferSize; i++){
            input[i] = (input[i] + (float)mdl.dl((double)input[i], 10000, 0.6))/2;
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
}