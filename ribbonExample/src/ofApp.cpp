#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
        sensel.setup();
    int numSnakes = 16;
    for (int i = 0; i<numSnakes; i++) {
        snakeCharmer tempSnake;
        
        tempSnake.setup(50+ofRandom(-10,20));
        tempSnake.setNoiseSpeed(ofRandom(0.001, 0.013));
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
        snakes[i].update(curPos, sensel.getContacts()[i].force);
        cout<<(int)sensel.getContacts()[i].id<<endl;
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor::black, ofColor::gray);
    
    for (int i=0; i<sensel.getContacts().size(); i++) {
    
        snakes[i].draw(0, 0, ofColor(255, ofMap(i, 0, sensel.getContacts().size(), 0, 255), 0), ofColor(255, ofMap(i, 0, sensel.getContacts().size(), 0, 255), 0));
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
