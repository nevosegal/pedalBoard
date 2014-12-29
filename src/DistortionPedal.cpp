//
//  DistortionPedal.cpp
//  pedalBoard
//
//  Created by Nevo Segal on 29/12/2014.
//
//

#include "DistortionPedal.h"

DistortionPedal::DistortionPedal(double x, double y, int id)
:Pedal(x, y, id){
    
}
DistortionPedal::DistortionPedal(){
    
}

float* DistortionPedal::effect(float* input, int bufferSize){
    if(!bypass_btn.bypassed){
        for(int i = 0; i < bufferSize; i++){
            //Range of shape should be 1-50
            input[i] = (float)distortion.atanDist((double)input[i], 50);
        }
    }
    return input;
}

void DistortionPedal::draw(){
    ofSetHexColor(0x0000ff);
    ofRectRounded(x,y,xsize, ysize, 8);
    bypass_btn.draw();
    input.draw();
    output.draw();
}