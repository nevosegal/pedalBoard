//
//  BypassButton.h
//  pedalBoard
//
//  Created by Nevo Segal on 15/12/2014.
//
//

#ifndef __pedalBoard__BypassButton__
#define __pedalBoard__BypassButton__

#include <stdio.h>
#include "ofMain.h"

class BypassButton{

public:
    BypassButton();
    BypassButton(double x, double y);
    
    //methods
    void setup();
    void update();
    void draw();
    double getX();
    double getY();
    void toggle();
    
    bool bypassed;
    double x, y, radius;
    
};



#endif /* defined(__pedalBoard__BypassButton__) */
