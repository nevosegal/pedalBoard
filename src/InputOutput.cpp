//
//  InputOutput.cpp
//  pedalBoard
//
//  Created by Nevo Segal on 16/12/2014.
//
//

#include "InputOutput.h"

InputOutput::InputOutput(){
}

InputOutput::InputOutput(string type,double x, double y){
    connected = false;
    this->type = type;
    this->x = x;
    this->y = y;
    radius = 6;
}

void InputOutput::setConnection(Pedal& pedal){
    pedalConnected = &pedal;
    connected = true;
}

Pedal& InputOutput::getConnection(){
    return *pedalConnected;
}

void InputOutput::disconnect(){
    connected = false;
}

bool InputOutput::isConnected(){
    return connected;
}

void InputOutput::draw(){
    ofSetHexColor(0xaaaaaa);
    ofCircle(x, y, radius);
}

bool InputOutput::isInBounds(int x, int y){
    if(x > (this->x - radius) && x < (this->x + radius) && y > (this->y - radius) && y < (this->y + radius)){
        return true;
    }
    return false;
}

double InputOutput::getX(){
    return x;
}

double InputOutput::getY(){
    return y;
}


