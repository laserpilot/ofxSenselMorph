//
//  lineDrawer.cpp
//  oscillators_draw
//
//  Created by Blair Neal on 11/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "snakeCharmer.h"
snakeCharmer::snakeCharmer(){
    
}

//-------------------------------------------------------------
void snakeCharmer::setup(int _vecSize){
    drawLine = true;
    drawHead = false;
    drawSpikes = true; //draw ribs between lines
    drawSkin = true; //draw outer lines
    drawMesh = true; //draw meaty center
    scale = 40;
    stepSize =1;
    vecSize = _vecSize;
    
    cout<< "Created a snake this long:" + ofToString(vecSize)<<endl;
    //this->pts.assign(vecSize, ofVec3f(ofGetWidth()/2,ofGetHeight()/2,0.0));
    pts.clear();
    pos = ofVec2f(0,0);
    oscillate = 0.0;
    
    noiseScale = 0.15;
    noiseSpeed = 0.3;
    maxVelScale = 80;
    prevVecSize=0;
    
    snakeID = -1;
    activated = false;
    
}

//-------------------------------------------------------------
void snakeCharmer::update(ofPoint _pt, float widthPt, int _snakeID, bool _activated){
    //cout<<prevPt.distance(_pt)<<endl;
    //scale = ofMap(prevPt.distance(_pt),0,500,2, 40);
    
    snakeID = _snakeID;
    activated = _activated;
    
    pts.push_back(_pt);
    if(pts.size()>vecSize){
        pts.erase(pts.begin(), pts.begin()+1);//(vecSize-prevVecSize));
    }

    widthPts.push_back(widthPt);
    if(widthPts.size()>vecSize){
        widthPts.erase(widthPts.begin(), widthPts.begin()+1);//(vecSize-prevVecSize));
    }
    
    prevVecSize = vecSize;
    prevPt = _pt;
    
    forcePt = widthPt;
}

//-------------------------------------------------------------
void snakeCharmer::draw(int _x ,int _y, ofColor outside, ofColor meshColor){
    
    ofPolyline polyLine;
    
    polyLine.addVertices(pts);
    //if(forcePt>0.1){

        polyLine = polyLine.getSmoothed(ofMap(forcePt, 0, .5, 6, 1));
        cout<<forcePt<<endl;
        pts = polyLine.getVertices();
    //}
    
    
    ofPushMatrix();
    ofTranslate(_x, _y);
    ofSetColor(255);
    ofNoFill();
    ofBeginShape();
    for(int i=0; i<pts.size(); i++){
        if(i==pts.size()-1){
            //ofSetColor(0,0,0);
            //ofCircle(pts[i]+5, 10);
            //ofCircle(pts[i]-5, 10);
        }
        if(i==0){
            //ofSetColor(127);
            //ofCircle(pts[i], 30);
            //ofSetColor(255);
           // ofCircle(pts[i]+1, 10);
        }
        ofSetColor(255);
        //ofVertex(pts[i].x, pts[i].y, pts[i].z);
    }
    ofEndShape(false);
    
    oscillate=1;
    
    ofSetLineWidth(0.2);
    ofSetColor(outside);
    //SPIKES------------
    if(drawSpikes){
        //int stepSize = 2;
        //int scale = 5;
        ofVec3f     a, b, tangent, normal, mappedA, mappedB;
        for (int i=0; i<pts.size()-stepSize; i=i+stepSize){
            
            if (i>2) {
            a = polyLine.getVertices()[i];
            b = polyLine.getVertices()[i+stepSize];
            float newScale;
            if (i>stepSize) {
                //newScale = ofMap(a.distance(b), 0, 500, 5, maxVelScale, true);
                newScale = ofMap(widthPts[i], 0, 1, 0, 400);
            }
            tangent = b-a;
            tangent.getRotated(90, ofVec3f(0,0,1));
            normal = tangent.getRotated(90,ofVec3f(0,0,1));
            normal.normalize();
            
            ofVec3f corner;
            //compute top side
            corner.x = a.x+ofClamp(ofDist(b.x,b.y,a.x,a.y),0,5)+normal.x*newScale+20*sin(noiseScale*ofSignedNoise((i*noiseSpeed)+ofGetElapsedTimef()));
            corner.y = a.y+ofClamp(ofDist(b.x,b.y,a.x,a.y),0,5)+normal.y*newScale+20*sin(noiseScale*ofSignedNoise((i*noiseSpeed)+ofGetElapsedTimef()));
            corner.z = a.z;
            ofLine(a+20*sin(noiseScale*ofSignedNoise((i*noiseSpeed)+ofGetElapsedTimef())),corner);
            normal = tangent.getRotated(-90,ofVec3f(0,0,1));
            normal.normalize();
            
            corner.x = a.x-ofClamp(ofDist(b.x,b.y,a.x,a.y),0,5)+normal.x*newScale-20*sin(-noiseScale*ofSignedNoise((i*noiseSpeed+0.01)+ofGetElapsedTimef()));
            corner.y = a.y-ofClamp(ofDist(b.x,b.y,a.x,a.y),0,5)+normal.y*newScale-20*sin(-noiseScale*ofSignedNoise((i*noiseSpeed+0.01)+ofGetElapsedTimef()));
            corner.z = a.z;

            //ofCircle(a, .5*ofDist(b.x,b.y,a.x,a.y));
            //corner =  a + normal*scale + 5*sin(1+(i*0.05)*ofGetElapsedTimef());
            //corner.x = corner.x * sin(.5*ofGetElapsedTimef())*sin(ofGetElapsedTimef());
            //corner.y = corner.y * cos(.7*ofGetElapsedTimef())*cos(ofGetElapsedTimef());
            ofLine(a+20*sin(noiseScale*ofSignedNoise((i*noiseSpeed)+ofGetElapsedTimef())),corner);
            }
        }
    }
    // SKINNNN
    ofSetLineWidth(2);
    if (drawSkin){
        ofPolyline outLines;
        ofPolyline inLines;
        //int stepSize = 2;
       // int scale = 5;
        ofVec3f     a, b, tangent, normal, mappedA, mappedB;
        //outLines.addVertex(pts[1]);
        //inLines.addVertex(pts[1]);
        for (int i=0; i<pts.size()-stepSize; i=i+stepSize){
            
            if(i>2){ //wonky on the first one...so skip it...need 2 for normalizing anyway
            a = polyLine.getVertices()[i];
            b = polyLine.getVertices()[i+stepSize];
            float newScale;
            if (i>stepSize) {
                //newScale = ofMap(a.distance(b), 0, 500, 5, maxVelScale, true);
                newScale = ofMap(widthPts[i], 0, 1, 0, 400);
            }
            tangent = b-a;
            tangent.getRotated(90, ofVec3f(0,0,1));
            normal = tangent.getRotated(90,ofVec3f(0,0,1));
            normal.normalize();
            
            ofVec3f corner;
            //compute top side
            corner.x = a.x+ofClamp(ofDist(b.x,b.y,a.x,a.y),0,5)+normal.x*newScale+20*sin(noiseScale*ofSignedNoise((i*noiseSpeed)+ofGetElapsedTimef()));
            corner.y = a.y+ofClamp(ofDist(b.x,b.y,a.x,a.y),0,5)+normal.y*newScale+20*sin(noiseScale*ofSignedNoise((i*noiseSpeed)+ofGetElapsedTimef()));
            corner.z = a.z;

            //ofLine(a,corner);
            inLines.addVertex(corner);
            //compute bottom side
            normal = tangent.getRotated(-90,ofVec3f(0,0,1));
            normal.normalize();
            
            corner.x = a.x-ofClamp(ofDist(b.x,b.y,a.x,a.y),0,5)+normal.x*newScale-20*sin(-noiseScale*ofSignedNoise((i*noiseSpeed+0.01)+ofGetElapsedTimef()));
            corner.y = a.y-ofClamp(ofDist(b.x,b.y,a.x,a.y),0,5)+normal.y*newScale-20*sin(-noiseScale*ofSignedNoise((i*noiseSpeed+0.01)+ofGetElapsedTimef()));
            corner.z = a.z;

            //corner.x = corner.x * sin(.5*ofGetElapsedTimef())*sin(ofGetElapsedTimef());
            //corner.y = corner.y * cos(.7*ofGetElapsedTimef())*cos(ofGetElapsedTimef());
            outLines.addVertex(corner);
            //ofLine(a,corner);
            }
        }
        //outLines.addVertex(pts[vecSize-1]);
        //inLines.addVertex(pts[vecSize-1]);
       // ofPolyline outSmooth;
       // outSmooth = outLines.getSmoothed(2);
        //outSmooth.draw();
        //outSmooth.clear();
        ofSetColor(255);
        outLines.draw();
        outLines.clear();
        //outSmooth = inLines.getSmoothed(2);
        //outSmooth.draw();
        inLines.draw();
        inLines.clear();
    }
    
    //filled in mesh
    if (drawMesh) {
        ofEnableAlphaBlending();
        ofMesh mesh;
        mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        
        ofFloatColor meshFColor;
        meshFColor = meshColor;
        
        
        //cout << "------------------------------------NEW MESH with this many verts: " + ofToString(vecSize) <<endl;
        

        ofVec3f     a, b, tangent, normal, mappedA, mappedB;
        for (int i=0; i<polyLine.getVertices().size()-stepSize; i=i+stepSize){
            //a = pts[i];
            //b = pts[i +stepSize];
            
            if (i>polyLine.getVertices().size()-polyLine.getVertices().size()*.95) { //this is a hacky fix because something is happening at the tail end of the line that causes it to shoot off screen - what this does is tells it to only draw 95% of the line

            a = polyLine.getVertices()[i];
            b = polyLine.getVertices()[i+stepSize];
            
            //cout<<i<< " " << polyLine.getVertices()[i] <<endl;
            float newScale;
            if (i>stepSize) {
                //newScale = ofMap(a.distance(b), 0, 500, 5, maxVelScale, true);
                newScale = ofMap(widthPts[i], 0, 1, 0, 400);
            }
            tangent = b-a;
            tangent.getRotated(90, ofVec3f(0,0,1));
            normal = tangent.getRotated(90,ofVec3f(0,0,1));
            normal.normalize();
            
            ofVec3f corner;
            //compute top side
            corner.x = a.x+ofClamp(ofDist(b.x,b.y,a.x,a.y),0,5)+normal.x*newScale+20*sin(noiseScale*ofSignedNoise((i*noiseSpeed)+ofGetElapsedTimef()));
            corner.y = a.y+ofClamp(ofDist(b.x,b.y,a.x,a.y),0,5)+normal.y*newScale+20*sin(noiseScale*ofSignedNoise((i*noiseSpeed)+ofGetElapsedTimef()));
            corner.z = a.z;
            //make tail end fade alpha
            //add top side point
            //mesh.addColor(ofFloatColor(meshColor.r/255,meshColor.g/255,meshColor.b/255,ofMap(i,0,polyLine.getVertices().size(),0.0,1)));
            meshFColor.a =ofMap(i,0,polyLine.getVertices().size(),0.0,1);
            mesh.addColor(meshFColor);
            mesh.addVertex(corner);
            //cout<<"Top Corner: " << ofToString(corner) << endl;
            //compute bottom side
            normal = tangent.getRotated(-90,ofVec3f(0,0,1));
            normal.normalize();

            corner.x = a.x-ofClamp(ofDist(b.x,b.y,a.x,a.y),0,5)+normal.x*newScale-20*sin(-noiseScale*ofSignedNoise((i*noiseSpeed+0.01)+ofGetElapsedTimef()));
            corner.y = a.y-ofClamp(ofDist(b.x,b.y,a.x,a.y),0,5)+normal.y*newScale-20*sin(-noiseScale*ofSignedNoise((i*noiseSpeed+0.01)+ofGetElapsedTimef()));
            corner.z = a.z;
            //mesh.addColor(ofFloatColor(float(meshColor.r/255),float(meshColor.g/255),float(meshColor.b/255),ofMap(i,0,polyLine.getVertices().size(),0.0,1)));
            meshFColor.a =ofMap(i,0,polyLine.getVertices().size(),0.0,1);
            mesh.addColor(meshFColor);
            mesh.addVertex(corner);
           // cout<<"Bottom Corner: " << ofToString(corner) << endl;
            //ofLine(a,corner);
            
            }
        }
        //cout<< vecSize << "  " << meshColor<<endl;
        ofSetColor(255);
        mesh.draw();
    }
    
    ofPopMatrix();
}

void snakeCharmer::resetSnake(){
    pts.clear();
    widthPts.clear();
    
    activated = false;
    snakeID = -1;
}


void snakeCharmer::setMaxVelScale(int _maxVelScale){
    maxVelScale = _maxVelScale;
}
void snakeCharmer::setNoiseSpeed(float _noiseSpeed){
    noiseSpeed = _noiseSpeed;
}
void snakeCharmer::setNoiseScale(float _noiseScale){
    noiseScale = _noiseScale;
};