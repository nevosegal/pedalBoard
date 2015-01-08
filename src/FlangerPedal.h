//
//  FlangerPedal.h
//  pedalBoard
//
//  Created by Nevo Segal on 29/12/2014.
//
//

#ifndef __pedalBoard__FlangerPedal__
#define __pedalBoard__FlangerPedal__

#include <stdio.h>
#include "ofMain.h"
#include "Pedal.h"
#include "ofxMaxim.h"

//This class inherits class Pedal and overrides some of its methods.
class FlangerPedal: public Pedal{
public:
    
    //constructors
    FlangerPedal(double x, double y, int id);
    FlangerPedal();
    
    //overriden methods
    void draw();
    float* effect(float* input, int bufferSize);
    
    //effect
    maxiFlanger flanger;
};


#endif /* defined(__pedalBoard__FlangerPedal__) */
