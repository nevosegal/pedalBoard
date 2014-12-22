
//
//  InputOutput.h
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
    InputOutput(string type,double x, double y);
    
    void disconnect();
    bool isConnected();
    void draw();
    bool isInBounds(int x, int y);
    InputOutput& getConnection();
    double getX();
    double getY();
    void setConnection(InputOutput &inOut);
    bool connected;
    string type;
    InputOutput *inputOutput;

    double x,y;
    int radius;
};


#endif /* defined(__pedalBoard__InputOutput__) */