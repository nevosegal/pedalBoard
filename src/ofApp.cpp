#include "ofApp.h"


//-------------------------------------------------------------
ofApp::~ofApp() {

}


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofEnableAlphaBlending();
    ofSetupScreen();
    background.loadImage("background.jpg");
    ofSetVerticalSync(true);

    sampleRate 			= 44100;
    initialBufferSize	= 512;
    myInput = new float[initialBufferSize];
    numPedals = 4;
    
    //creating new pedals
    dp = *new DelayPedal(80,75,6);
    distortion = *new DistortionPedal(310,75,7);
    flanger = *new FlangerPedal(540,75,8);
    chorus = *new ChorusPedal(770,75,9);
    
    //pushing them all to a new array of type Pedal.
    pedals.push_back(&dp);
    pedals.push_back(&distortion);
    pedals.push_back(&flanger);
    pedals.push_back(&chorus);

    cableColor = 80;
    //Creating new audio in and audio out.
    audioIn = *new InputOutput("input", 10, (double)ofGetHeight()/2);
    audioOut = *new InputOutput("output", ofGetWidth() - 10, (double)ofGetHeight()/2);
    ofSoundStreamSetup(2,1,this, sampleRate, initialBufferSize, 4);
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    
    //drawing the wooden floor
    background.draw(0, 0, ofGetWidth(), ofGetHeight());

    //drawing the pedals
    for (int i = 0; i < numPedals; i++) {
        pedals.at(i)->draw();
    }

    ofSetColor(cableColor);
    
    if(drawLine){
        //drawing the line when the user is holding the mouse key.
        ofSetLineWidth(3);
        ofLine(startX, startY, targetX, targetY);
    }
    
    for(int i = 0; i < numPedals ; i++){
        //if there has been a connection between two pedals, draw a line between them
        if(pedals.at(i)->getInput().isConnected()){
            ofLine(pedals.at(i)->getInput().getConnection().getX(), pedals.at(i)->getInput().getConnection().getY(), pedals.at(i)->getInput().getX(), pedals.at(i)->getInput().getY());
        }
        //same goes for audio out.
        if(audioOut.isConnected()){
            ofLine(audioOut.getConnection().getX(), audioOut.getConnection().getY(), audioOut.getX(), audioOut.getY());
        }
    }
    
    //drawing the audio in and audio out.
    audioIn.draw();
    audioOut.draw();
}

//--------------------------------------------------------------

bool chainFound = false;
int lastPedal = 0;
int counter = 0;

void ofApp::audioRequested 	(float * output, int bufferSize, int nChannels){

    /*In this section I do some logic as to what pedals should I pass the audio to.*/
    chainFound = false;
    if(audioIn.isConnected()){
        for(int i = 0 ; i < numPedals; i++) {
            //I start with the audio in, I check if there is a pedal connected to it and if so, which one.
            if(&pedals.at(i)->getInput() == &audioIn.getConnection()){
                lastPedal = i;
                //I call the effect function of this pedal. (as I'm using morphism, it doesn't matter what pedal it is, they are all of type pedal)
                myInput = pedals.at(i)->effect(myInput, bufferSize);
                break;
            }
        }
    }
    
    //Here I check for the rest of the chain. Every iteration, when I find a match between an output of a pedal and an input of another pedal, I set the index of the last pedal.
    while(!chainFound){
        for(int i = 0; i < numPedals; i++){
            if(pedals.at(i)->getInput().isConnected() && &pedals.at(i)->getInput().getConnection() == &pedals.at(lastPedal)->getOutput()){
                myInput = pedals.at(i)->effect(myInput, bufferSize);
                lastPedal = i;
            }
        }
        counter++;
        //making sure that it doesn't run forever.
        if(counter > numPedals){
            counter = 0;
            chainFound = true;
        }
    }
    //Checking if audio out is connected and that the last pedal in the chain is indeed the pedal that is connected to the output.
    //this helps me avoid incomplete chains.
    if(audioIn.isConnected() && audioOut.isConnected() && &pedals.at(lastPedal)->getOutput() == &audioOut.getConnection()){
        for (int i = 0; i < bufferSize; i++){
            
            //For a better user experience I split the audio to stereo.
            mymix.stereo(myInput[i], outputs, 0.5);
            
            output[i*nChannels] = outputs[0];
            output[i*nChannels+1] = outputs[1];
        }
    }
    else{
        for (int i = 0; i < bufferSize; i++){
            //putting 0s everywhere if there is no complete chain of pedals from audio in to audio out.
            output[i*nChannels] = 0;
            output[i*nChannels+1] = 0;
        }
    }


}
//--------------------------------------------------------------
void ofApp::audioReceived (float * input, int bufferSize, int nChannels){
    //grabbing the mic audio in and putting it in an array.
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
    
    //doing the color changing of the pedals inputs and the audio in/out if they are connected and hovered.
    for(int i = 0; i < numPedals; i++){
        if(pedals.at(i)->getInput().isConnected() && pedals.at(i)->getInput().isInBounds(x, y)){
            if(pedals.at(i)->getInput().getColor() != 255){
                pedals.at(i)->getInput().setColor(255);
            }
        }
        else if(audioOut.isConnected() && audioOut.isInBounds(x, y)){
            if(audioOut.getColor() != 255){
                audioOut.setColor(255);
            }
        }
        else{
            if(pedals.at(i)->getInput().getColor() != 120 || audioOut.getColor() != 120){
                pedals.at(i)->getInput().setColor(120);
                audioOut.setColor(120);
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
    
    for(int i = 0; i < numPedals; i++){
        if(pedals.at(i)->isEngaged() && pedals.at(i)->isInBounds(x,y)){
            //the logic of moving the pedals.
            double deltax = x-prevx;
            double deltay = y-prevy;
            pedals.at(i)->move(deltax, deltay);
            prevx = x;
            prevy = y;
        }
        else{
            //the logic of changing the value of a knob.
            float mouseRange = 200;
            for(int j = 0 ; j < pedals.at(i)->getNumKnobs() ; j++){
                if(pedals.at(i)->getKnob(j).isEngaged()){
                    double deltay = prevy-y;
                    float currValue = pedals.at(i)->getKnob(j).getValue();
                    float currRange = pedals.at(i)->getKnob(j).range;
                    pedals.at(i)->getKnob(j).setValue(currValue + deltay*currRange/mouseRange);
                    prevy = y;
                }
            }
        }
    }
    //if a user is dragging the 'cable' from an input towards an output, the target x and y of this line will be the current x,y mouse values.
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
        //checking if a pedal is being clicked.
        if(pedals.at(i)->isInBounds(x, y) && !pedals.at(i)->getOutput().isInBounds(x, y) &&
           !pedals.at(i)->getInput().isInBounds(x, y) && !pedals.at(i)->bypass_btn.isInBounds(x, y)){
            prevx = x;
            prevy = y;
            if(pedals.at(i)->getNumKnobs() != 0){
                for(int j = 0; j < pedals.at(i)->getNumKnobs(); j++){
                    //checking if a knob whithin this pedal is being clicked.
                    if(pedals.at(i)->getKnob(j).isHovered(x,y)){
                        //if so, I know that the user tried to click the knob and not the pedal.
                        found = true;
                        pedals.at(i)->getKnob(j).engaged = true;
                    }
                }
            }
            //if not, I take the pedal.
            if(!found){
                pedals.at(i)->engaged = true;
            }
        }
        //If the click wasn't in the bounds of the pedal, but in the bounds of an output (and the output is not already connected to anything).
        else if(pedals.at(i)->getOutput().isInBounds(x,y) && !pedals.at(i)->getOutput().isConnected()){
            tempPedal = i;
            startX = x;
            startY = y;
            targetX = x;
            targetY = y;
            drawLine = true;
        }
        //If the click was on an input and this input is connected, disconnect.
        else if(pedals.at(i)->getInput().isInBounds(x,y)){
            pedals.at(i)->getInput().getConnection().disconnect();
            pedals.at(i)->getInput().disconnect();
        }
        //If audio out was clicked and it is connected, disconnect.
        else if(audioOut.isInBounds(x, y)){
            audioOut.disconnect();
            audioOut.getConnection().disconnect();
        }
        //If audio in was clicked.
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
        //if a bypass button was hovered when mouse released, toggle it.
        if(bb.isInBounds(x, y)){
            bb.toggle();
            break;
        }
        //if a pedal input is hovered, set its connection to the output of the pedal that was originally clicked.
        if (tempPedal != 100 && !pedals.at(i)->getInput().isConnected() && drawLine){
            if(pedals.at(i)->getInput().isInBounds(x, y)){
                pedals.at(i)->getInput().setConnection(pedals.at(tempPedal)->getOutput());
                pedals.at(tempPedal)->getOutput().setConnection(pedals.at(i)->getInput());
                break;
            }
        }
        //same goes for audio out.
        if(tempPedal != 100 && !audioOut.isConnected() && drawLine){
            if(audioOut.isInBounds(x, y)){
                audioOut.setConnection(pedals.at(tempPedal)->getOutput());
                pedals.at(tempPedal)->getOutput().setConnection(audioOut);
                break;
            }
        }
        //same goes for audio in.
        if (tempPedal == 100 && !audioIn.isConnected() && drawLine && pedals.at(i)->getInput().isInBounds(x, y)){
            pedals.at(i)->getInput().setConnection(audioIn);
            audioIn.setConnection(pedals.at(i)->getInput());
            break;
        }
        //disengage all pedals.
        pedals.at(i)->engaged = false;
        if(pedals.at(i)->getNumKnobs() != 0){
            for(int j = 0; j < pedals.at(i)->getNumKnobs(); j++){
                //disengage all knobs.
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