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

InputOutput::InputOutput(string type){
    connected = false;
    this->type = type;
    radius = 6;
}

void InputOutput::setConnection(Pedal& pedal){
    pedalConnected = &pedal;
    connected = true;
}

void InputOutput::disconnect(){
    connected = false;
}

bool InputOutput::isConnected(){
    return connected;
}

void InputOutput::draw(double x, double y){
    this->x = x;
    this->y = y;
    ofSetHexColor(0xaaaaaa);
    ofCircle(x, y, radius);
}

bool InputOutput::isInBounds(int x, int y){
    if(x > (this->x - radius) && x < (this->x + radius) && y > (this->y - radius) && y < (this->y + radius)){
        return true;
    }
    return false;
}

