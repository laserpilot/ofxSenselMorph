#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
        sensel.setup();
    int numSnakes = 16;
    for (int i = 0; i<numSnakes; i++) {
        snakeCharmer tempSnake;
        
        
        tempSnake.setup(200+ofRandom(-10,20));
        tempSnake.setNoiseSpeed(ofRandom(0.001, 0.15));
        tempSnake.setNoiseScale(1);
        snakes.push_back(tempSnake);
    }
    
    bDebug = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    sensel.update();
    
    for (int i=0; i<sensel.getContacts().size(); i++) {
        ofPoint curPos = ofPoint(ofMap(sensel.getContacts()[i].position.x,0,1,0,ofGetWidth()), ofMap(sensel.getContacts()[i].position.y,0,1,0,ofGetHeight()));
        //snakes[i].setMaxVelScale(ofMap(sensel.getContacts()[i].force, 0, 1, 0,700));
        //cout<<sensel.getContacts()[i].force<<endl;
        
        
        //if there is a snake that doesn't exist with that contact ID - create it and update it
        //if a snake already exists - update it
        //if the snake doesn't match an existing contact ID - remove it
        
        //Not the smartest way to do this
        
        bool bContactApplied = false;
        
        for (int j=0; j<snakes.size(); j++) {
            
            if (sensel.getContacts()[i].contactType=="Start" && !snakes[j].activated && !bContactApplied) {
                snakes[j].update(curPos, sensel.getContacts()[i].force, sensel.getContacts()[i].contactID, true);
                bContactApplied = true; //make sure we only use each contact once...
            }
            
            if (sensel.getContacts()[i].contactType=="Move" && sensel.getContacts()[i].contactID== snakes[j].getSnakeID() && !bContactApplied) {
                snakes[j].update(curPos, sensel.getContacts()[i].force, sensel.getContacts()[i].contactID, true);
                bContactApplied = true;
            }
            
            if (sensel.getContacts()[i].contactType=="End" && sensel.getContacts()[i].contactID== snakes[j].getSnakeID() && !bContactApplied) {
                snakes[j].resetSnake();
                snakes[j].update(ofPoint(-1,-1), 1, -1, false);
                bContactApplied = true;
            }
            
            if(!snakes[j].activated){
                snakes[j].update(ofPoint(-1,-1), 1, -1, false);
            }
            
            
        }
        
        
    }
    
for (int j=0; j<snakes.size(); j++) {
    if(!snakes[j].activated){
        snakes[j].update(ofPoint(-1,-1), 1, -1, false);
    }
}
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor::gray, ofColor::black);
    
    for (int i=0; i<snakes.size(); i++) {
    
        snakes[i].draw(0, 0, ofColor(255, ofMap(i, 0, sensel.getContacts().size(), 0, 255), 0), ofColor(255, ofMap(i, 0, sensel.getContacts().size(), 0, 255), 0));
        //snakes[i].drawDebug(i);
    }
    
    if (bDebug) {
        sensel.draw();
    }
}

void ofApp::exit(){
    sensel.close();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key=='d'){
        bDebug = !bDebug;
    }
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
