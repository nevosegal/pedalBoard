//
//  ChrousPedal.h
//  pedalBoard
//
//  Created by Nevo Segal on 29/12/2014.
//
//

#ifndef __pedalBoard__ChrousPedal__
#define __pedalBoard__ChrousPedal__

#include <stdio.h>
#include "ofMain.h"
#include "Pedal.h"
#include "ofxMaxim.h"

//This class inherits class Pedal and overrides some of its methods.
class ChorusPedal: public Pedal{
public:
    
    //constructors
    ChorusPedal(double x, double y, int id);
    ChorusPedal();
    
    //overriden methods
    void draw();
    float* effect(float* input, int bufferSize);
    
    //effect
    maxiChorus chorus;
};

#endif /* defined(__pedalBoard__ChrousPedal__) */
