
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
    
    //constructors
    InputOutput();
    InputOutput(string type,double x, double y);
    
    //class methods
    void disconnect();
    bool isConnected();
    void draw();
    bool isInBounds(int x, int y);
    InputOutput& getConnection();
    double getX();
    double getY();
    void setConnection(InputOutput &inOut);
    int getColor();
    void setColor(int col);
    
    //class variables
    bool connected;
    string type;
    InputOutput *inputOutput;
    double x,y;
    int radius;
    int col;
};


#endif /* defined(__pedalBoard__InputOutput__) */