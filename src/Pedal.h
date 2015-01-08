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
#include "Knob.h"

class Pedal{
    
public:
    
    //constructors
    Pedal();
    Pedal(double x, double y, int id);
    
    //class methods. some are virtual and will be overriden by child class.
    virtual void draw();
    BypassButton& getBypassButton();
    void move(double x, double y);
    virtual float* effect(float* input, int bufferSize);
    bool isInBounds(int x, int y);
    bool isEngaged();
    InputOutput& getInput();
    InputOutput& getOutput();
    void setInput(InputOutput in);
    void setOutput(InputOutput out);
    int getId();
    int getNumKnobs();
    Knob& getKnob(int index);
    
    //class variables
    double x, y, xsize, ysize;
    BypassButton bypass_btn;
    bool engaged;
    InputOutput input;
    InputOutput output;
    int id;
    int numKnobs;
    
    //an array of knobs. the size of this array is changed according to the number of parameters each pedal needs.
    Knob* knobs;
    ofTrueTypeFont header;


};

#endif /* defined(__pedalBoard__Pedal__) */
