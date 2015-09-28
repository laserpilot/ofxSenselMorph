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
        
        uint32 total_force;
        uid_t  uid;
        uint32 area;  // area multiplied by 65536
        uint16 x_pos;  // raw x position
        uint16 y_pos;  // raw y position
        vel_t dx; // change in x from last frame
        vel_t dy; // change in y from last frame
        int16 orientation; // angle from -90 to 90 multiplied by 256
        uint16 major_axis; // length of the major axis multiplied by 256
        uint16 minor_axis; // length of the minor axis multiplied by 256
        grid_coord_t peak_x;
        grid_coord_t peak_y;
        label_t id; // TODO: The type of this should be something like contact_id
        contact_type_t type;

    };
    
    
    ofxSenselMorph() { };
    ~ofxSenselMorph() { };
    
    contact_t contacts[MAX_CONTACTS];
    int numContacts;
    
    void setup();
    void update();
    void draw();
    
    vector<SenselContact> senselContacts;
    
    vector <SenselContact> getContacts();
    
    
    void close();
};