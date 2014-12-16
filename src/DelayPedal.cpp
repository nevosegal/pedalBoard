//
//  DelayPedal.cpp
//  pedalBoard
//
//  Created by Nevo Segal on 16/12/2014.
//
//

#include "DelayPedal.h"

DelayPedal::DelayPedal(double x, double y)
:Pedal(x, y){
    
}

float* effect(float* input){
    cout<<"this is inside delayPedal"<<endl;
    return input;
}