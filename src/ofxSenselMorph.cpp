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
        cout<<"Sensel connection established"<<endl;
    }else{
        cout<<"Unable to establish Sensel connection"<<endl;
    }
    
    senselSetFrameContentControl(SENSEL_FRAME_CONTACTS_FLAG);
    senselStartScanning();
    
    numContacts = 0;
    
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
        
        string event;
        switch (event_type)
        {
            case SENSEL_EVENT_CONTACT_INVALID:
                event = "Invalid";
                break;
            case SENSEL_EVENT_CONTACT_START:
                event = "Start";
                break;
            case SENSEL_EVENT_CONTACT_MOVE:
                event = "Move";
                break;
            case SENSEL_EVENT_CONTACT_END:
                event = "End";
                break;
            default:
                event = "Error";
        }
        
        printf("Contact ID %d, event=%s, mm coord: (%f, %f), force=%d, " \
               "major=%f, minor=%f, orientation=%f\n",
               id, event.c_str(), x_mm, y_mm, force, major, minor, orientation);
        
        
        SenselContact tempContact;
        
        tempContact.contactID = id;
        tempContact.force = ofMap(force,0, 65536,0,1);
        tempContact.position.x = ofMap(x_mm, 0, getSensorWidth(), 0, 1);
        tempContact.position.y = ofMap(y_mm, 0, getSensorHeight(), 0, 1);
        tempContact.majorAxis = contacts[i].major_axis_mm;
        tempContact.minorAxis = contacts[i].minor_axis_mm;
        tempContact.orientation = contacts[i].orientation_degrees;
        tempContact.contactType = event;
        
        
        
        senselContacts.push_back(tempContact);
        
    }
    
    accel_data_t senselAccelData;
    if (senselReadAccelerometerData(&senselAccelData)) {
        accelData.x = senselAccelData.x;
        accelData.y = senselAccelData.y;
        accelData.y = senselAccelData.z;
    }
    
    
}

void ofxSenselMorph::draw(){
    
    //This is ugly below...just threw it together...will refactor later
    
    ofSetCircleResolution(60);
    for (int i=0; i< senselContacts.size(); i++){
        ofSetColor(255, ofMap(i, 0, senselContacts.size(), 0, 255), 0);
        ofPoint curPoint = ofPoint(ofMap(senselContacts[i].position.x, 0, 1, 0, ofGetWidth()), ofMap(senselContacts[i].position.y, 0, 1, 0, ofGetHeight()));
        
        ofSetColor(255, ofMap(senselContacts[i].force, 0, 1, 255, 0), 0);
        ofFill();
        ofPushMatrix();
        ofTranslate(curPoint.x, curPoint.y);
        ofRotateZ(senselContacts[i].orientation);
        ofEllipse(0,0, ofMap(senselContacts[i].minorAxis, 0, 30, 0, 200),  ofMap(senselContacts[i].majorAxis, 0, 30, 0, 200));
        ofSetColor(255);
        ofLine(0,0, ofMap(senselContacts[i].minorAxis, 0, 30, 0, 200)/2, 0);
        ofSetColor(0);
        ofLine(0,0, 0, -ofMap(senselContacts[i].majorAxis, 0, 30, 0, 200)/2);
        ofPopMatrix();
        ofDrawBitmapStringHighlight(ofToString(i), curPoint.x +10, curPoint.y+10);
        ofDrawBitmapStringHighlight(ofToString(senselContacts[i].contactID), curPoint.x +10, curPoint.y+30);
        
        ofNoFill();
        ofSetColor(255);
        ofCircle(curPoint, ofMap(senselContacts[i].force, 0, 65536, 0, 200));

    }
    
    ofDrawBitmapString("Accelerometer data: " + ofToString(accelData,4),  20,20);
    
}

void ofxSenselMorph::close(){
    cout<<"Closing Sensel Connection"<<endl;
    senselStopScanning();
    senselCloseConnection();
}