//
//  Pedal.h
//  pedalBoard
//
//  Created by Nevo Segal on 15/12/2014.
//
//

#ifndef __pedalBoard__Pedal__
#define __pedalBoard__Pedal__

#include <stdio.h>
#include "ofMain.h"
#include "BypassButton.h"
#include "InputOutput.h"

class Pedal{
    
public:
    
    //constructor
    Pedal();
    Pedal(double x, double y, int id);
    
    //methods
    void setup();
    void update();
    void draw();
    BypassButton& getBypassButton();
    void move(double x, double y);
    virtual float* effect(float* input);
    bool isInBounds(int x, int y);
    bool isEngaged();
    InputOutput& getInput();
    InputOutput& getOutput();
    void setInput(InputOutput in);
    void setOutput(InputOutput out);
    int getId();
    
    //members
    double x, y, xsize, ysize;
    BypassButton bypass_btn;
    bool engaged;
    InputOutput input;
    InputOutput output;
    int id;

};

#endif /* defined(__pedalBoard__Pedal__) */
