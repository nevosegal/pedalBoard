//
//  DelayPedal.cpp
//  pedalBoard
//
//  Created by Nevo Segal on 16/12/2014.
//
//

#include "DelayPedal.h"

DelayPedal::DelayPedal(double x, double y, int id)
:Pedal(x, y, id){
    
}
DelayPedal::DelayPedal(){
    
}

float* effect(float* input){
    cout<<"this is inside delayPedal"<<endl;
    return input;
}

void DelayPedal::draw(){
    //Change the appearance of the pedal;
    cout << "kjsnksf" <<endl;
}