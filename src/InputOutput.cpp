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
    col = 120;
}

void InputOutput::setConnection(InputOutput& inOut){
    inputOutput = &inOut;
    connected = true;
}

InputOutput& InputOutput::getConnection(){
    return *inputOutput;
}

void InputOutput::disconnect(){
    connected = false;
}

bool InputOutput::isConnected(){
    return connected;
}

void InputOutput::draw(){
    ofFill();
    ofSetColor(col, 120, 120);
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

void InputOutput::setColor(int col){
    this->col = col;
}

int InputOutput::getColor(){
    return col;
}


