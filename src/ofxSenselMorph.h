//
//  ofxSenselMorph.h
//  simpleExample
//
//  Created by Blair Neal on 9/28/15.
//
//

#pragma once

#include "ofMain.h"
#include "sensel.h"
#include "sensel_serial.h"

class ofxSenselMorph{
public:
    struct SenselContact{
        
        uid_t  uid; //Static unique touch id. Doesn't reset on build. Doesn't seem to wrap.
        //Note (MR): Trying to get touchid similiar to iOS
        int touchId;
        //uint16 x_pos;  // raw x position
        //uint16 y_pos;  // raw y position
        
        ofPoint position; //mapped to sensel area to screen area - probably need to make this 0->1
        float force;
        int contactID;
        int area;// area multiplied by 65536
        int orientation;// angle from -90 to 90 multiplied by 256
        int majorAxis;// length of the major axis multiplied by 256
        int minorAxis;// length of the minor axis multiplied by 256
        //vel_t dx; // change in x from last frame
        //vel_t dy; // change in y from last frame
        label_t id; // TODO: The type of this should be something like contact_id
        contact_type_t type; //start or move

    };
    
    
    ofxSenselMorph() { };
    ~ofxSenselMorph() { };
    
    contact_t contacts[MAX_CONTACTS];
    int numContacts;
    
    void setup();
    void update();
    void draw();
    
    vector<SenselContact> senselContacts;
    
    vector<SenselContact> getContacts(){ return senselContacts;}
    
    
    void close();

//Note (MR): Trying to get touchid similiar to iOS
private:
    static int touchIdCounter;
    bool startTouchId;
};