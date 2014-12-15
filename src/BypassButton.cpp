//
//  BypassButton.cpp
//  pedalBoard
//
//  Created by Nevo Segal on 15/12/2014.
//
//

#include "BypassButton.h"


BypassButton::BypassButton(){
    this->x = 0;
    this->y = 0;
    radius = 0;
    bypassed = true;
}
BypassButton::BypassButton(double x, double y){
    this->x = x;
    this->y = y;
    radius = 20;
    bypassed = true;
}

void BypassButton::setup(){
    
}

void BypassButton::update(){
}

void BypassButton::draw(){

    if(bypassed){
        ofSetHexColor(0xff0000);
    }else{
        ofSetHexColor(0x00ff00);
    }
    ofCircle(x, y, radius);
}

void BypassButton::toggle(){
    bypassed = !bypassed;
}

double BypassButton::getX(){
    return this->x;
}

double BypassButton::getY(){
    return this->y;
}