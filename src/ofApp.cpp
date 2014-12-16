#include "ofApp.h"



//-------------------------------------------------------------
ofApp::~ofApp() {

}


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofEnableAlphaBlending();
    ofSetupScreen();
    ofBackground(0, 0, 0);
    ofSetVerticalSync(true);
    sampleRate 			= 44100; /* Sampling Rate */
    initialBufferSize	= 512;	/* Buffer Size. you have to fill this buffer with sound*/
    myInput = new float[initialBufferSize];
    numPedals = 4;
    for(int i = 0 ; i < numPedals; i++){
        pedals.push_back(*new Pedal(50 + i*200, 70));
    }
    ofSoundStreamSetup(1,1,this, sampleRate, initialBufferSize, 4);/* Call this last ! */
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    for (int i = 0; i < numPedals; i++) {
        pedals.at(i).draw();
        cout << pedals.at(i).getInput().isConnected() <<endl;
    }

    if(drawLine){
        ofLine(startX, startY, targetX, targetY);
    }
    
}

//--------------------------------------------------------------
void ofApp::audioRequested 	(float * output, int bufferSize, int nChannels){

    for (int i = 0; i < bufferSize; i++){
        output[i] = myInput[i];
    }
    
}
//--------------------------------------------------------------
void ofApp::audioReceived (float * input, int bufferSize, int nChannels){
    for (int i = 0; i < bufferSize; i++){
        myInput[i] = input[i];
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    for(int i = 0; i < numPedals; i++){
        if(pedals.at(i).isInBounds(x, y)){
            //TBD: act when hovered
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    for(int i = 0; i < numPedals; i++){
        if(pedals.at(i).isEngaged() && pedals.at(i).isInBounds(x,y) && !pedals.at(i).getOutput().isInBounds(x,y)){
            double deltax = x-prevx;
            double deltay = y-prevy;
            pedals.at(i).move(deltax, deltay);
            prevx = x;
            prevy = y;
        }
    }
    if(drawLine){
        targetX = x;
        targetY = y;
    }
}

Pedal tempPedal;
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    for(int i = 0; i < numPedals; i++){
        if(pedals.at(i).isInBounds(x, y) && !pedals.at(i).getOutput().isInBounds(x, y)){
            prevx = x;
            prevy = y;
        }
        else if(pedals.at(i).getOutput().isInBounds(x,y)){
            drawLine = true;
            startX = x;
            startY = y;
            targetX = x;
            targetY = y;
            tempPedal = pedals.at(i);
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    for(int i = 0; i < numPedals; i++){
        BypassButton & bb = pedals.at(i).getBypassButton();
        if(bb.isInBounds(x, y)){
            bb.toggle();
        }
        else if (drawLine && pedals.at(i).getInput().isInBounds(x, y)){
            pedals.at(i).getInput().setConnection(tempPedal);
        }
        pedals.at(i).engaged = false;
    }
    drawLine = false;
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}


//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
void ofApp::exit(){
    ofSoundStreamClose();
}