//
//  ofxSenselMorph.cpp
//  simpleExample
//
//  Created by Blair Neal on 9/28/15.
//
//

#include "ofxSenselMorph.h"

void ofxSenselMorph::setup(){
    if (senselOpenConnection(0)) {
        cout<<"Unable to open Sensel Sensor!"<<endl;
    }else{
        cout<<"Sensel connection established"<<endl;
    }
    
    senselSetFrameContentControl(SENSEL_FRAME_CONTACTS_FLAG);
    senselStartScanning();
    
    numContacts = 0;
    
}

void ofxSenselMorph::update(){
    numContacts = senselReadContacts(contacts);
    
    senselContacts.clear();
    
    for(int i=0; i< numContacts; i++){
        int force = contacts[i].total_force;
        float x_mm = contacts[i].x_pos_mm;
        float y_mm = contacts[i].y_pos_mm;
        //Read out shape information (ellipses)
        float major = contacts[i].major_axis_mm;
        float minor = contacts[i].minor_axis_mm;
        float orientation = contacts[i].orientation_degrees;
        
        int id = contacts[i].id;
        int event_type = contacts[i].type;
        
        char* event;
        switch (event_type)
        {
            case SENSEL_EVENT_CONTACT_INVALID:
                event = "invalid";
                break;
            case SENSEL_EVENT_CONTACT_START:
                event = "start";
                break;
            case SENSEL_EVENT_CONTACT_MOVE:
                event = "move";
                break;
            case SENSEL_EVENT_CONTACT_END:
                event = "end";
                break;
            default:
                event = "error";
        }
        
        printf("Contact ID %d, event=%s, mm coord: (%f, %f), force=%d, " \
               "major=%f, minor=%f, orientation=%f\n",
               id, event, x_mm, y_mm, force, major, minor, orientation);
        
        
        SenselContact tempContact;
        tempContact.total_force = force;
        tempContact.x_pos = x_mm;
        tempContact.y_pos = y_mm;
        
    }
}

void ofxSenselMorph::draw(){
    
    ofSetCircleResolution(60);
    for (int i=0; i< numContacts; i++){
        ofSetColor(255, ofMap(i, 0, numContacts, 0, 255), 0);
        ofPoint curPoint = ofPoint(ofMap(contacts[i].x_pos_mm, 0, getSensorWidth(), 0, ofGetWidth()), ofMap(contacts[i].y_pos_mm, 0, getSensorHeight(), 0, ofGetHeight()));
        
        //ofPoint prevPoint = ofPoint(ofMap(contacts[i].dx, 0, getSensorWidth(), 0, ofGetWidth()), ofMap(contacts[i].dy, 0, getSensorHeight(), 0, ofGetHeight()));
        
        //cout<<prevPoint<<endl;
        
        //ofLine(curPoint.x, curPoint.y, curPoint.x-prevPoint.x, curPoint.y-prevPoint.y);
        
        ofSetColor(255, ofMap(i, 0, numContacts, 0, 255), 0);
        ofFill();
        ofPushMatrix();
        ofTranslate(curPoint.x, curPoint.y);
        ofRotateZ(contacts[i].orientation_degrees);
        ofEllipse(0,0, ofMap(contacts[i].minor_axis_mm, 0, 30, 0, 200),  ofMap(contacts[i].major_axis_mm, 0, 30, 0, 200));
        ofSetColor(255);
        ofLine(0,0, ofMap(contacts[i].minor_axis_mm, 0, 30, 0, 200)/2, 0);
        ofSetColor(0);
        ofLine(0,0, 0, -ofMap(contacts[i].major_axis_mm, 0, 30, 0, 200)/2);
        ofPopMatrix();
        ofDrawBitmapStringHighlight(ofToString(i), curPoint.x +10, curPoint.y+10);
        
        ofNoFill();
        ofSetColor(255);
        ofCircle(ofMap(contacts[i].x_pos_mm, 0, getSensorWidth(), 0, ofGetWidth()), ofMap(contacts[i].y_pos_mm, 0, getSensorHeight(), 0, ofGetHeight()), ofMap(contacts[i].total_force, 0, 65536, 0, 200));

    }
    
}

void ofxSenselMorph::close(){
    cout<<"Closing Sensel Connection"<<endl;
    senselStopScanning();
    senselCloseConnection();
}