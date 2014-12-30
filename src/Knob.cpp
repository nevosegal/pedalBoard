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

Knob::Knob(float x, float y, float range, string name){
    this->x = x;
    this->y = y;
    this->range = range;
    this->value = 0;
    this->radius = 25;
    this->engaged = false;
    this->name = name;
    tf.loadFont("Cuprum-Bold.ttf", fontSize);
}

float Knob::getValue(){
    return this->value;
}

void Knob::setValue(float value){
    if(value < this->range && value >= 0){
        this->value = value;
    }
}

void Knob::draw(){
    ofEnableSmoothing();
    ofFill();
    ofSetColor(255,255,255);
    ofCircle(this->x, this->y, this->radius);
    if(isEngaged()){
        ofNoFill();
        ofSetColor(255,0,0);
        ofCircle(this->x, this->y, this->radius);
    }
    ofRectangle typeRect = tf.getStringBoundingBox(name, 0, 0);
    ofRectangle valueRect = tf.getStringBoundingBox(ofToString(value), 0, 0);
    ofSetColor(0,0,0);
    tf.drawString(name, this->x-(typeRect.width/2), this->y-this->radius-5);
    tf.drawString(ofToString(this->value), this->x-(valueRect.width/2), this->y+(fontSize/2));
}

bool Knob::isHovered(int x, int y){
    if(x > (this->x - this->radius) && x < (this->x + this->radius)&&
       y > (this->y - this->radius) && y < (this->y + this->radius)){
        return true;
    }
    return false;
}

bool Knob::isEngaged(){
    return engaged;
}

void Knob::toggleEngage(){
    engaged = !engaged;
}