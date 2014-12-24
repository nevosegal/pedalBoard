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


class DelayPedal: public Pedal{
public:
    DelayPedal(double x, double y, int id);
    DelayPedal();
    void draw();
    float* effect(float* input, int bufferSize);
};


#endif /* defined(__pedalBoard__DelayPedal__) */