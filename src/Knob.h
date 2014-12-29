//
//  Knob.h
//  pedalBoard
//
//  Created by Nevo Segal on 16/12/2014.
//
//

#ifndef __pedalBoard__Knob__
#define __pedalBoard__Knob__

#include <stdio.h>
#include "ofMain.h"


class Knob{
    
public:
    Knob(float x, float y, float range);
    Knob();
//    ~Knob();
    
    void setValue(float value);
    float getValue();
    void draw();
    bool isHovered();
    
    float value;
    float range;
    float radius;
    float x, y;
    
};
#endif /* defined(__pedalBoard__Knob__) */
