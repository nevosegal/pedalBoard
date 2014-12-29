//
//  DistortionPedal.h
//  pedalBoard
//
//  Created by Nevo Segal on 29/12/2014.
//
//

#ifndef __pedalBoard__DistortionPedal__
#define __pedalBoard__DistortionPedal__

#include <stdio.h>
#include "ofMain.h"
#include "Pedal.h"
#include "ofxMaxim.h"


class DistortionPedal: public Pedal{
public:
    DistortionPedal(double x, double y, int id);
    DistortionPedal();
    void draw();
    float* effect(float* input, int bufferSize);
    maxiDistortion distortion;
};


#endif /* defined(__pedalBoard__DistortionPedal__) */
