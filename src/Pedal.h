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
#include "ofxUI.h"

class Pedal{
    
public:
    
    //constructor
    Pedal();
    Pedal(double x, double y);
    
    //methods
//    void toggleBypass();
    void setup();
    void update();
    void draw();
    BypassButton& getBypassButton();
    void move(double x, double y);
    virtual float* effect(float* input);
    
    //variables
    double x, y, xsize, ysize;
    BypassButton bypass_btn;
    bool engaged;

};

#endif /* defined(__pedalBoard__Pedal__) */
