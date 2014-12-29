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
    
}
ChorusPedal::ChorusPedal(){
    
}

float* ChorusPedal::effect(float* input, int bufferSize){
    if(!bypass_btn.bypassed){
        for(int i = 0; i < bufferSize; i++){
            //flange params:
            //input
            //delay : tbd
            //feedback: 0-1
            //lfo speed: 0-10
            //depth: 0-1
            input[i] = chorus.chorus((double)input[i], 50, 0.8, 2, 0.5);
        }
    }
    return input;
}

void ChorusPedal::draw(){
    ofSetHexColor(0xffff00);
    ofRectRounded(x,y,xsize, ysize, 8);
    bypass_btn.draw();
    input.draw();
    output.draw();
}