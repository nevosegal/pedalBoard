//
//  Knob.cpp
//  pedalBoard
//
//  Created by Nevo Segal on 16/12/2014.
//
//

#include "Knob.h"

Knob::Knob(){
    
}

Knob::Knob(float x, float y, float range){
    this->x = x;
    this->y = y;
    this->range = range;
    this->value = 0;
    this->radius = 25;
}

float Knob::getValue(){
    return this->value;
}

void Knob::setValue(float value){
    this->value = value;
}

void Knob::draw(){
    ofSetColor(255,255,255);
    ofCircle(this->x, this->y, this->radius);
}

bool Knob::isHovered(){
    if(x > (this->x - this->radius) && x < (this->x + this->radius)&&
       y > (this->y - this->radius) && y < (this->y + this->radius)){
        return true;
    }
    return false;
}