//
//  Pedal.cpp
//  pedalBoard
//
//  Created by Nevo Segal on 15/12/2014.
//
//

#include "Pedal.h"


//default constructor
Pedal::Pedal(){
    id = 100;
    knobs = new Knob[numKnobs];
}

//constructor
Pedal::Pedal(double x, double y, int id){
    
    this->x = x;
    this->y = y;
    xsize = 150;
    ysize = 250;
    
    //new bypass button
    bypass_btn = *new BypassButton(x+(xsize/2),y+(2.2*ysize/3));
    
    //by default, not engaged.
    engaged = false;
    
    //new input and out for the pedal.
    input = *new InputOutput("Input",x,y+ysize/2);
    output = *new InputOutput("Output",x+xsize,y+ysize/2);
    
    this->id = id;
    
    //font for the header.
    header.loadFont("Lobster-Regular.ttf", 16);
}

void Pedal::draw(){
    //default pedal, this will be overriden in each child class.
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

InputOutput& Pedal::getInput(){
    return input;
}

InputOutput& Pedal::getOutput(){
    return output;
}

//getters
int Pedal::getId(){
    return id;
}

Knob& Pedal::getKnob(int index){
    return knobs[index];
}

int Pedal::getNumKnobs(){
    return numKnobs;
}

//setters
void Pedal::setInput(InputOutput in){
    input = in;
}

void Pedal::setOutput(InputOutput out){
    output = out;
}

//the moving function.
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

//a default effect, will be overriden by each child class.
float* Pedal::effect(float* input, int bufferSize){
    if(!bypass_btn.bypassed){
        for (int i = 0; i< bufferSize; i++) {
            input[i] /= 2;
        }
    }
    return input;
}

//checking if the pedal is in bounds of an x and y passed to it.
bool Pedal::isInBounds(int x, int y){
    if(x > this->x && x < (this->x + xsize) && y > this->y && y < (this->y + ysize)){
        return true;
    }
    return false;
}

//checking if the pedal is engaged.
bool Pedal::isEngaged(){
    return engaged;
}

