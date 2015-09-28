//
//  lineDrawer.h
//  oscillators_draw
//
//  Created by Blair Neal on 11/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#pragma once 

#include "ofMain.h"

class snakeCharmer {
public:
    
    snakeCharmer();
    
    void setup(int _vecSize);
    void update(ofPoint _pt, float widthPt);
    void draw( int _x, int _y, ofColor outside, ofColor mesh);
    void setMaxVelScale(int _maxVelScale);
    void setNoiseScale(float _noiseScale);
    void setNoiseSpeed(float _noiseSpeed);
    
    bool drawLine;
    bool drawHead;
    bool drawSpikes;
    bool drawSkin;
    bool drawMesh;
    
    int vecSize;
    int x;
    int y;
    float scale;
    float stepSize;
    
    float maxVelScale;
    float noiseScale;
    float noiseSpeed;
    
    float oscillate;
    
    ofPoint pos;
    ofPoint prevPt;
    
    vector <ofPoint> pts;
    vector <float> widthPts;
    int prevVecSize;
    
    //ofPolyline polyLine;

};
