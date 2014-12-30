//
//  Pedal.cpp
//  pedalBoard
//
//  Created by Nevo Segal on 15/12/2014.
//
//

#include "Pedal.h"


Pedal::Pedal(){
    //TBD
    id = 100;
    knobs = new Knob[numKnobs];
}

Pedal::Pedal(double x, double y, int id){
    this->x = x;
    this->y = y;
    xsize = 150;
    ysize = 250;
    bypass_btn = *new BypassButton(x+(xsize/2),y+(2.2*ysize/3));
    engaged = false;
    input = *new InputOutput("Input",x,y+ysize/2);
    output = *new InputOutput("Output",x+xsize,y+ysize/2);
    this->id = id;
    header.loadFont("Lobster-Regular.ttf", 16);
}

void Pedal::setup(){
}

void Pedal::update(){
}

void Pedal::draw(){
    ofFill();
    ofSetHexColor(0xffffff);
    ofRectRounded(x,y,xsize, ysize, 8);
    bypass_btn.draw();
    input.draw();
    output.draw();
}

BypassButton& Pedal::getBypassButton(){
    return bypass_btn;
}

void Pedal::move(double x, double y){
    this->x += x;
    this->y += y;
    bypass_btn.x = this->x + (xsize/2);
    bypass_btn.y = this->y + (2.2*ysize/3);
    input.x += x;
    input.y += y;
    output.x += x;
    output.y += y;
    for(int i = 0; i < numKnobs; i++){
        knobs[i].x += x;
        knobs[i].y += y;
    }
}

float* Pedal::effect(float* input, int bufferSize){
    if(!bypass_btn.bypassed){
        for (int i = 0; i< bufferSize; i++) {
            input[i] /= 2;
        }
    }
    return input;
}

bool Pedal::isInBounds(int x, int y){
    if(x > this->x && x < (this->x + xsize) && y > this->y && y < (this->y + ysize)){
        return true;
    }
    return false;
}

bool Pedal::isEngaged(){
    return engaged;
}

InputOutput& Pedal::getInput(){
    return input;
}

InputOutput& Pedal::getOutput(){
    return output;
}

void Pedal::setInput(InputOutput in){
    input = in;
}

void Pedal::setOutput(InputOutput out){
    output = out;
}

int Pedal::getId(){
    return id;
}

Knob& Pedal::getKnob(int index){
    return knobs[index];
}

int Pedal::getNumKnobs(){
    return numKnobs;
}



