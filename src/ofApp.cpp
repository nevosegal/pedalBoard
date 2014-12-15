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
    numPedals = 3;
    for(int i = 0 ; i < numPedals; i++){
        pedals.push_back(*new Pedal(10 + i*200, 10));
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
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    for(int i = 0; i < numPedals; i++){
        BypassButton & bb = pedals.at(i).getBypassButton();
        if(x > (bb.x - bb.radius) && x < (bb.x + bb.radius) && y > (bb.y - bb.radius) && y < (bb.y + bb.radius)){
            bb.toggle();
        }
    }
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