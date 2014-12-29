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


class FlangerPedal: public Pedal{
public:
    FlangerPedal(double x, double y, int id);
    FlangerPedal();
    void draw();
    float* effect(float* input, int bufferSize);
    maxiFlanger flanger;
};


#endif /* defined(__pedalBoard__FlangerPedal__) */
