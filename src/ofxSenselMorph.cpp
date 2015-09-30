//
//  ofxSenselMorph.cpp
//  simpleExample
//
//  Created by Blair Neal on 9/28/15.
//
//

#include "ofxSenselMorph.h"

int ofxSenselMorph::touchIdCounter = 0;

void ofxSenselMorph::setup(){
    if (senselOpenConnection(0)) {
        cout<<"Sensel connection established"<<endl;
    }else{
        cout<<"Unable to establish Sensel connection"<<endl;
    }
    
    senselSetFrameContentControl(SENSEL_FRAME_CONTACTS_FLAG);
    senselStartScanning();
    
    numContacts = 0;
    
    //Note (MR): Trying to get touchid similiar to iOS
    startTouchId = false;

    
}

void ofxSenselMorph::update(){
    
    
    numContacts = senselReadContacts(contacts);
    
    senselContacts.clear();
    
    for(int i=0; i< numContacts; i++){
        
        //LEAVING THIS ALL FOR DEBUG RIGHT NOW!!
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
        
       // printf("Contact ID %d, event=%s, mm coord: (%f, %f), force=%d, " \
               "major=%f, minor=%f, orientation=%f\n",
       //        id, event, x_mm, y_mm, force, major, minor, orientation);
        
        
        //Note (MR): Trying to get touchid similiar to iOS
        if (i > 0) {
            
            startTouchId = true;
        
        } else {
            
            startTouchId = false;
        }
        
        if (startTouchId) {
            touchIdCounter++;

        } else {
            touchIdCounter = 0;
        }
        
        //Note (MR) End
        
        SenselContact tempContact;
        tempContact.id = contacts[i].id;
        tempContact.force = ofMap(force,0, 65536,0,1);
        tempContact.position.x = ofMap(x_mm, 0, getSensorWidth(), 0, 1);
        tempContact.position.y = ofMap(y_mm, 0, getSensorHeight(), 0, 1);
        tempContact.majorAxis = contacts[i].major_axis_mm;
        tempContact.minorAxis = contacts[i].minor_axis_mm;
        tempContact.orientation = contacts[i].orientation_degrees;
        //Note (MR)//
        tempContact.touchId = touchIdCounter; //Touch Id Similiar to iOS
        
        senselContacts.push_back(tempContact);

    }
    
    
}

void ofxSenselMorph::draw(){
    
    //This is ugly below...just threw it together...will refactor later
    
    ofSetCircleResolution(60);
    for (int i = 0; i < numContacts; i++){
        
        ofSetColor(255, ofMap(i, 0, numContacts, 0, 255), 0);
        ofPoint curPoint = ofPoint(ofMap(contacts[i].x_pos_mm, 0, getSensorWidth(), 0, ofGetWidth()), ofMap(contacts[i].y_pos_mm, 0, getSensorHeight(), 0, ofGetHeight()));
        
        //ofPoint prevPoint = ofPoint(ofMap(contacts[i].dx, 0, getSensorWidth(), 0, ofGetWidth()), ofMap(contacts[i].dy, 0, getSensorHeight(), 0, ofGetHeight()));
        
        //cout<<prevPoint<<endl;
        
        //ofLine(curPoint.x, curPoint.y, curPoint.x-prevPoint.x, curPoint.y-prevPoint.y);
        
        ofSetColor(255, ofMap(contacts[i].total_force, 0, 65536, 255, 0), 0);
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