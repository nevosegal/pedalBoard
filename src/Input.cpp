//
//  Input.cpp
//  pedalBoard
//
//  Created by Nevo Segal on 16/12/2014.
//
//

#include "Input.h"

Input::Input(string type){
    connected = false;
    this->type = type;
}

void Input::setConnection(Pedal& pedal){
    pedalConnected = &pedal;
    connected = true;
}

void InputOutput::disconnect(){
    connected = false;
}

bool InputOutput::isConnected(){
    return connected;
}

void InputOutput::draw(double x, double y, double pedalSizeX, double pedalSizeY){
    ofSetHexColor(0xaaaaaa);
    ofCircle(x, y+pedalSizeY/2, 6);
}
