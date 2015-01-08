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
    
    //creating the knobs.
    numKnobs = 1;
    knobs = new Knob[numKnobs];
    knobs[0] = *new Knob(x+(xsize/2), y+(ysize/4), 50, "Shape");
}
DistortionPedal::DistortionPedal(){
    numKnobs = 1;
    knobs = new Knob[numKnobs];
}

// as this is a distortionPedal, the effect is distortion :P.
float* DistortionPedal::effect(float* input, int bufferSize){
    if(!bypass_btn.bypassed){
        for(int i = 0; i < bufferSize; i++){
            //I pass the values of the knobs directly to the distortion function.
            input[i] = (float)distortion.atanDist((double)input[i], knobs[0].getValue());
        }
    }
    return input;
}

//distortionPedal specific draw function.
void DistortionPedal::draw(){
    ofFill();
    ofSetHexColor(0x262626);
    ofRectRounded(x,y,xsize, ysize, 8);
    bypass_btn.draw();
    input.draw();
    output.draw();
    for(int i = 0; i < numKnobs; i++){
        knobs[i].draw();
    }
    ofRectangle headerRect = header.getStringBoundingBox(ofToString("Distortion"), 0, 0);
    header.drawString("Distortion", this->x + (this->xsize/2) - (headerRect.width/2) , this->y+this->ysize - 20);
}