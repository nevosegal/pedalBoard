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

//getters

//getting the input/output its connected to.
InputOutput& InputOutput::getConnection(){
    return *inputOutput;
}

double InputOutput::getX(){
    return x;
}

double InputOutput::getY(){
    return y;
}

int InputOutput::getColor(){
    return col;
}

//setters
void InputOutput::setColor(int col){
    this->col = col;
}

//setting the input/output its connected to.
void InputOutput::setConnection(InputOutput& inOut){
    inputOutput = &inOut;
    connected = true;
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

//checking if the input/output is hovered.
bool InputOutput::isInBounds(int x, int y){
    if(x > (this->x - radius) && x < (this->x + radius) && y > (this->y - radius) && y < (this->y + radius)){
        return true;
    }
    return false;
}



