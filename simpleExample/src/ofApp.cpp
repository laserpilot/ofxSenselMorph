#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    sensel.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    sensel.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    sensel.draw();

    for (int i = 0; i < sensel.getContacts().size(); i++) {
        
        
        string objectId = "Object: " + ofToString(sensel.getContacts().at(i).touchId);
        
        ofDrawBitmapString(objectId, 50, 50 + i * 15);
        cout << objectId << endl;
        
    }
}

void ofApp::exit(){
    sensel.close();
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
