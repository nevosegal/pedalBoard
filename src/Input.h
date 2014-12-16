//
//  Input.h
//  pedalBoard
//
//  Created by Nevo Segal on 16/12/2014.
//
//

#ifndef __pedalBoard__InputOutput__
#define __pedalBoard__InputOutput__

#include <stdio.h>
#include "ofMain.h"

class Pedal;

class InputOutput{
public:
    InputOutput();
    InputOutput(string type);
    
    void setConnection(Pedal& p);
    void disconnect();
    bool isConnected();
    void draw(double x, double y, double pedalSizeX, double pedalSizeY);
    
    bool connected;
    string type;
    Pedal *pedalConnected;
};


#endif /* defined(__pedalBoard__InputOutput__) */
