//
//  DelayPedal.h
//  pedalBoard
//
//  Created by Nevo Segal on 16/12/2014.
//
//

#ifndef __pedalBoard__DelayPedal__
#define __pedalBoard__DelayPedal__

#include <stdio.h>
#include "ofMain.h"
#include "Pedal.h"
#include "ofxMaxim.h"

//This class inherits class Pedal and overrides some of its methods.
class DelayPedal: public Pedal{

public:
    
    //constructors
    DelayPedal(double x, double y, int id);
    DelayPedal();
    
    //overriden methods
    void draw();
    float* effect(float* input, int bufferSize);
    
    //effect
    maxiDelayline mdl;
};


#endif /* defined(__pedalBoard__DelayPedal__) */