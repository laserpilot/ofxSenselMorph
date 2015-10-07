#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"
#include "ofxSenselMorph.h"

//Took this Sensel example entirely from the ofxBox2d example-simple and added sensel stuff to it


#define N_SOUNDS 4

class SoundData {
public:
    int	 soundID;
    bool bHit;
};

class PlayerData{
public:
    int radius;
};



// -------------------------------------------------

class testApp : public ofBaseApp {
	
public:
	
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void resized(int w, int h);
	
    
	ofxBox2d                            box2d;			  //	the box2d world
	vector    <shared_ptr<ofxBox2dCircle> >	circles;		  //	default box2d circles
	vector	  <shared_ptr<ofxBox2dRect> >	boxes;			  //	defalut box2d rects
    	vector	  <shared_ptr<ofxBox2dRect> >	musicBoxes;			  //	defalut box2d rects
    
    ofxSenselMorph sensel;
    
    int maxSize = 0;
	
    // this is the function for contacts
    void contactStart(ofxBox2dContactArgs &e);
    void contactEnd(ofxBox2dContactArgs &e);
    
    // when the ball hits we play this sound
    ofSoundPlayer  sound[N_SOUNDS];
};

