
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
    
    void setConnection(Pedal& p);
    void disconnect();
    bool isConnected();
    void draw();
    bool isInBounds(int x, int y);
    Pedal& getConnection();
    double getX();
    double getY();
    
    bool connected;
    string type;
    Pedal *pedalConnected;
    double x,y;
    int radius;
};


#endif /* defined(__pedalBoard__InputOutput__) */