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
    Knob(float x, float y, float range, string name);
    Knob();
//    ~Knob();
    
    void setValue(float value);
    float getValue();
    void draw();
    bool isHovered(int x, int y);
    bool isEngaged();
    void toggleEngage();
    
    float value;
    float range;
    float radius;
    float x, y;
    bool engaged;
    string name;
    ofTrueTypeFont tf;
    int fontSize;
};
#endif /* defined(__pedalBoard__Knob__) */
