#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	ofSetVerticalSync(true);
	ofBackgroundHex(0xfdefc2);
	ofSetLogLevel(OF_LOG_NOTICE);
	
	box2d.init();
	box2d.setGravity(0, 10);
	box2d.createBounds();
	box2d.setFPS(60.0);
	box2d.registerGrabbing();
	
    sensel.setup();
}

//--------------------------------------------------------------
void testApp::update() {
	box2d.update();
    sensel.update();
    
    for (int i=0; i<sensel.getContacts().size(); i++) {
        
        ofPoint curPos = ofPoint(ofMap(sensel.getContacts()[i].position.x,0,1,0,ofGetWidth()), ofMap(sensel.getContacts()[i].position.y,0,1,0,ofGetHeight()));
        if(sensel.getContacts()[i].contactType=="Start"){
            if (i%2==0) {
                circles.push_back(shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle));
                circles.back().get()->setPhysics(3.0, 0.53, 0.1);
                circles.back().get()->setup(box2d.getWorld(),curPos.x, curPos.y, sensel.getContacts()[i].force*500);
            }else{
                boxes.push_back(shared_ptr<ofxBox2dRect>(new ofxBox2dRect));
                boxes.back().get()->setPhysics(3.0, 0.53, 0.1);
                boxes.back().get()->setup(box2d.getWorld(), curPos.x, curPos.y, sensel.getContacts()[i].force*500,sensel.getContacts()[i].force*500 );
            }
            
        }else if(sensel.getContacts()[i].contactType=="Move"){
            //My grabbing logic is a little goofy...just tossed it together, so it's not great
            box2d.enableGrabbing();
            box2d.grabShapeDown(curPos.x, curPos.y);
            box2d.grabShapeDragged(curPos.x, curPos.y);
        }else{
            box2d.disableGrabbing();
            box2d.grabShapeUp(curPos.x, curPos.y);
        }
        
    }
}


//--------------------------------------------------------------
void testApp::draw() {
	
	
	for(int i=0; i<circles.size(); i++) {
		ofFill();
		ofSetHexColor(0xf6c738);
		circles[i].get()->draw();
	}
	
	for(int i=0; i<boxes.size(); i++) {
		ofFill();
		ofSetHexColor(0xBF2545);
		boxes[i].get()->draw();
	}

	// draw the ground
	box2d.drawGround();
	
	
	
	string info = "";
	info += "Press [c] for circles\n";
	info += "Press [b] for blocks\n";
	info += "Total Bodies: "+ofToString(box2d.getBodyCount())+"\n";
	info += "Total Joints: "+ofToString(box2d.getJointCount())+"\n\n";
	info += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n";
	ofSetHexColor(0x444342);
	ofDrawBitmapString(info, 30, 30);
    
    //sensel.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
	
	if(key == 'c') {
		float r = ofRandom(4, 20);
		circles.push_back(shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle));
		circles.back().get()->setPhysics(3.0, 0.53, 0.1);
		circles.back().get()->setup(box2d.getWorld(), mouseX, mouseY, r);
		
	}
	
	if(key == 'b') {
		float w = ofRandom(4, 20);
		float h = ofRandom(4, 20);
		boxes.push_back(shared_ptr<ofxBox2dRect>(new ofxBox2dRect));
		boxes.back().get()->setPhysics(3.0, 0.53, 0.1);
		boxes.back().get()->setup(box2d.getWorld(), mouseX, mouseY, w, h);
	}
	
	if(key == 't') ofToggleFullscreen();
    
    if(key==' '){
        circles.clear();
        boxes.clear();
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) {
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::resized(int w, int h){
}

