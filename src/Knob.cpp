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
    this->radius = 20;
    this->engaged = false;
    this->name = name;
    fontSize = 8;
    tf.loadFont("Raleway-Bold.ttf", fontSize);
}


//get the value of the knob
float Knob::getValue(){
    return this->value;
}

//set the value of the knob.
void Knob::setValue(float value){
    if(value < this->range && value >= 0){
        this->value = value;
    }
}

void Knob::draw(){
    ofEnableSmoothing();
    ofFill();
    ofSetColor(10,10,10);
    ofCircle(this->x, this->y, this->radius);
    if(isEngaged()){
        //draw red circle around knob when its engaged.
        ofNoFill();
        ofSetColor(255,0,0);
        ofCircle(this->x, this->y, this->radius);
    }
    
    //calculating the rectangle around the text in order to get its width and then center it properly.
    ofRectangle typeRect = tf.getStringBoundingBox(name, 0, 0);
    ofRectangle valueRect = tf.getStringBoundingBox(ofToString(round(this->value*100)/100.0), 0, 0);
    ofSetColor(220,220,220);
    tf.drawString(name, this->x-(typeRect.width/2), this->y-this->radius-5);
    tf.drawString(ofToString(round(this->value*100)/100.0), this->x-(valueRect.width/2), this->y+(fontSize/2));
}

//check when the knob is hovered.
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