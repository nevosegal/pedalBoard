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
    
    distortion = *new DistortionPedal(250,70,7);
    dp = *new DelayPedal(50,70,6);
    flanger = *new FlangerPedal(450,70,8);
    chorus = *new ChorusPedal(650,70,9);
    
    pedals.push_back(&dp);
    pedals.push_back(&distortion);
    pedals.push_back(&flanger);
    pedals.push_back(&chorus);

    cableHoverColor = 150;
    audioIn = *new InputOutput("input", 0, (double)ofGetHeight()/2);
    audioOut = *new InputOutput("output", ofGetWidth(), (double)ofGetHeight()/2);
    ofSoundStreamSetup(1,1,this, sampleRate, initialBufferSize, 4);/* Call this last ! */
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    for (int i = 0; i < numPedals; i++) {
        pedals.at(i)->draw();
    }

    if(drawLine){
        ofLine(startX, startY, targetX, targetY);
    }
    
    ofSetColor(cableHoverColor);
    for(int i = 0; i < numPedals ; i++){
        if(pedals.at(i)->getInput().isConnected()){
            ofLine(pedals.at(i)->getInput().getConnection().getX(), pedals.at(i)->getInput().getConnection().getY(), pedals.at(i)->getInput().getX(), pedals.at(i)->getInput().getY());
        }
        if(audioOut.isConnected()){
            ofLine(audioOut.getConnection().getX(), audioOut.getConnection().getY(), audioOut.getX(), audioOut.getY());
        }
    }
    audioIn.draw();
    audioOut.draw();
}

//--------------------------------------------------------------
bool chainFound = false;
int lastPedal = 0;
int counter = 0;
void ofApp::audioRequested 	(float * output, int bufferSize, int nChannels){

    chainFound = false;
    if(audioIn.isConnected()){
        for(int i = 0 ; i < numPedals; i++) {
            if(&pedals.at(i)->getInput() == &audioIn.getConnection()){
                lastPedal = i;
                myInput = pedals.at(i)->effect(myInput, bufferSize);
                break;
            }
        }
    }
    
    while(!chainFound){
        for(int i = 0; i < numPedals; i++){
            if(&pedals.at(i)->getInput().getConnection() == &pedals.at(lastPedal)->getOutput()){
                myInput = pedals.at(i)->effect(myInput, bufferSize);
                lastPedal = i;
            }
        }
        if(counter > 50){
            counter = 0;
            chainFound = true;
        }
        counter++;
    }
    
    if(audioOut.isConnected() && &pedals.at(lastPedal)->getOutput().getConnection() == &audioOut){
        for (int i = 0; i < bufferSize; i++){
            output[i] = myInput[i];
        }
    }
    else{
        for (int i = 0; i < bufferSize; i++){
            output[i] = 0;
        }
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
        if(pedals.at(i)->isInBounds(x, y)){
            //TBD: act when hovered
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    for(int i = 0; i < numPedals; i++){
        if(pedals.at(i)->isEngaged() && pedals.at(i)->isInBounds(x,y)){
            double deltax = x-prevx;
            double deltay = y-prevy;
            pedals.at(i)->move(deltax, deltay);
            prevx = x;
            prevy = y;
        }
        else{
            float mouseRange = 200;
            for(int j = 0 ; j < pedals.at(i)->getNumKnobs() ; j++){
                if(pedals.at(i)->getKnob(j).isEngaged()){
                    double deltay = prevy-y;
                    float currValue = pedals.at(i)->getKnob(j).getValue();
                    float currRange = pedals.at(i)->getKnob(j).range;
                    pedals.at(i)->getKnob(j).setValue(currValue + deltay*currRange/mouseRange);
//                    cout << pedals.at(i)->getKnob(j).getValue() << endl;
                }
            }
        }
    }
    if(drawLine){
        targetX = x;
        targetY = y;
    }
}

int tempPedal;
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    bool found = false;
    for(int i = 0; i < numPedals; i++){
        if(pedals.at(i)->isInBounds(x, y) && !pedals.at(i)->getOutput().isInBounds(x, y)){
            prevx = x;
            prevy = y;
            if(pedals.at(i)->getNumKnobs() != 0){
                for(int j = 0; j < pedals.at(i)->getNumKnobs(); j++){
                    if(pedals.at(i)->getKnob(j).isHovered(x,y)){
                        found = true;
//                        cout << pedals.at(i)->getKnob(j).range << endl;
                        pedals.at(i)->getKnob(j).engaged = true;
                    }
                }
            }
            if(!found){
                pedals.at(i)->engaged = true;
            }
        }
        else if(pedals.at(i)->getOutput().isInBounds(x,y) && !pedals.at(i)->getOutput().isConnected()){
            tempPedal = i;
            startX = x;
            startY = y;
            targetX = x;
            targetY = y;
            drawLine = true;
        }
        else if(audioIn.isInBounds(x, y)){
            tempPedal = 100;
            startX = x;
            startY = y;
            targetX = x;
            targetY = y;
            drawLine = true;
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    for(int i = 0; i < numPedals; i++){
        BypassButton & bb = pedals.at(i)->getBypassButton();
        if(bb.isInBounds(x, y)){
            bb.toggle();
            break;
        }
        else if (tempPedal != 100 && (!pedals.at(i)->getInput().isConnected() || !audioOut.isConnected()) && drawLine){
            if(pedals.at(i)->getInput().isInBounds(x, y)){
                pedals.at(i)->getInput().setConnection(pedals.at(tempPedal)->getOutput());
                pedals.at(tempPedal)->getOutput().setConnection(pedals.at(i)->getInput());
                break;
            }
            else if(audioOut.isInBounds(x, y)){
                audioOut.setConnection(pedals.at(tempPedal)->getOutput());
                pedals.at(tempPedal)->getOutput().setConnection(audioOut);
                break;
            }
        }
        else if (tempPedal == 100 && !audioIn.isConnected() && drawLine && pedals.at(i)->getInput().isInBounds(x, y)){
            pedals.at(i)->getInput().setConnection(audioIn);
            audioIn.setConnection(pedals.at(i)->getInput());
            break;
        }
        pedals.at(i)->engaged = false;
        if(pedals.at(i)->getNumKnobs() != 0){
            for(int j = 0; j < pedals.at(i)->getNumKnobs(); j++){
                if(pedals.at(i)->getKnob(j).isEngaged()){
                    pedals.at(i)->getKnob(j).engaged = false;
                }

            }
        }
    }
    tempPedal == 100;
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

void ofApp::drawInOut(){
    int h = ofGetHeight();
    int w  = ofGetWidth();
}