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
    BypassButton getBypassButton();
    
    //variables
    double x, y, xsize, ysize;
    BypassButton bypass_btn;
};

#endif /* defined(__pedalBoard__Pedal__) */
