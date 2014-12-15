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
}

Pedal::Pedal(double x, double y){
    this->x = x;
    this->y = y;
    xsize = 120;
    ysize = 200;
    bypass_btn = *new BypassButton(x+(xsize/2),y+(ysize/2));
}

void Pedal::setup(){

}

void Pedal::update(){
}

void Pedal::draw(){
    ofSetHexColor(0xffffff);
    ofRectRounded(x,y,xsize, ysize, 8);
    bypass_btn.draw();
}

BypassButton& Pedal::getBypassButton(){
    return bypass_btn;
}