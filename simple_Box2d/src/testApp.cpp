#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	ofSetVerticalSync(true);
	//ofBackgroundHex(0xfdefc2);
	ofSetLogLevel(OF_LOG_NOTICE);
	
	box2d.init();
	box2d.setGravity(0, 10);
	box2d.createBounds();
	box2d.setFPS(60.0);
	box2d.registerGrabbing();
	
    sensel.setup();
    
    
    //add sounds
    sound[0].loadSound("perc1.mp3");
    sound[0].setLoop(false);
    sound[0].setMultiPlay(true);
    sound[1].loadSound("perc2.mp3");
    sound[1].setLoop(false);
    sound[1].setMultiPlay(true);
    sound[2].loadSound("perc3.mp3");
    sound[2].setLoop(false);
    sound[2].setMultiPlay(true);
    sound[3].loadSound("perc4.mp3");
    sound[3].setLoop(false);
    sound[3].setMultiPlay(true);
    
    //other things to explore would be having the size of the circle effect which note is sounded, not just volume - small notes could be higher pitched and low notes would be lower
    
    //create boxes for the circles to collide with
    
    for (int i=0; i<N_SOUNDS*3; i++) {
        shared_ptr <ofxBox2dRect> m = shared_ptr <ofxBox2dRect>(new ofxBox2dRect);
        
        
        m.get()->setup(box2d.getWorld(),50+i*(100+ofRandom(25,50)), ofRandom(500,550), 50,50);
        m.get()->setData(new SoundData());
        SoundData * sd = (SoundData*)m.get()->getData();
        sd->soundID = i%N_SOUNDS;
        sd->bHit	= false;
        musicBoxes.push_back(m);
    }


    // register the listener so that we get the events
    box2d.enableEvents();
    ofAddListener(box2d.contactStartEvents, this, &testApp::contactStart);
    ofAddListener(box2d.contactEndEvents, this, &testApp::contactEnd);
    
    //circles.push_back(shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle));
    //boxes.back().get()->setPhysics(3.0, 0.53, 0.1);
    //circles.back().get()->setup(box2d.getWorld(), 300, 300, 50 );
    
}

//--------------------------------------------------------------
void testApp::update() {
	box2d.update();
    sensel.update();
}


//--------------------------------------------------------------
void testApp::draw() {
    
    ofBackgroundGradient(ofColor::white, ofColor::black);
    

    int forceMult = 500;
    
    for (int i=0; i<sensel.getContacts().size(); i++) {
        
        ofPoint curPos = ofPoint(ofMap(sensel.getContacts()[i].position.x,0,1,0,ofGetWidth()), ofMap(sensel.getContacts()[i].position.y,0,1,0,ofGetHeight()));
        if(sensel.getContacts()[i].contactType=="Start"){

            //if (i%2==0) {
                maxSize = 0;
                shared_ptr <ofxBox2dCircle> c = shared_ptr <ofxBox2dCircle>(new ofxBox2dCircle);

                c.get()->setPhysics(3.0, 0.53, 0.1);
                c.get()->setup(box2d.getWorld(),curPos.x, curPos.y, sensel.getContacts()[i].force*forceMult);
                //c.get()->setData(new PlayerData());
                //PlayerData * pd = (PlayerData*)c.get()->getData();
                //pd->radius =sensel.getContacts()[i].force*forceMult;
                circles.push_back(c);
                
            /*}else{
                boxes.push_back(shared_ptr<ofxBox2dRect>(new ofxBox2dRect));
                boxes.back().get()->setPhysics(3.0, 0.53, 0.1);
                boxes.back().get()->setup(box2d.getWorld(), curPos.x, curPos.y, sensel.getContacts()[i].force*forceMult,sensel.getContacts()[i].force*forceMult );
            }*/
            
        }else if(sensel.getContacts()[i].contactType=="Move"){
            ofSetColor(127,255, 0);
            if (maxSize<sensel.getContacts()[i].force*forceMult) {
                maxSize =sensel.getContacts()[i].force*forceMult;
            }
            circles.back().get()->setData(new PlayerData());
            PlayerData * pd = (PlayerData*)circles.back().get()->getData();
            pd->radius =maxSize;
            circles.back().get()->setData(pd);
            circles.back().get()->setRadius(maxSize);
            //My grabbing logic is a little goofy...just tossed it together, so it's not great
            box2d.enableGrabbing();
            box2d.grabShapeDown(curPos.x, curPos.y);
            box2d.grabShapeDragged(curPos.x, curPos.y);
        }else{
            
            box2d.grabShapeUp(curPos.x, curPos.y);
            box2d.disableGrabbing();
        }
        
    }
	
	
	for(int i=0; i<circles.size(); i++) {
        ofFill();
        SoundData * data = (SoundData*)circles[i].get()->getData();
        
        if(data && data->bHit) ofSetHexColor(0xff0000);
        else ofSetHexColor(0x4ccae9);
        
		circles[i].get()->draw();
	}
	
	for(int i=0; i<boxes.size(); i++) {
		ofFill();
		ofSetHexColor(0xBF2545);
		boxes[i].get()->draw();
	}
    
    for(int i=0; i<musicBoxes.size(); i++) {
        ofFill();
        ofSetColor(100,255,100);
        musicBoxes[i].get()->draw();
    }

	// draw the ground
	box2d.drawGround();
	
	
	
	string info = "";
    info += "Press harder for larger circles - the larger they are, the louder they are\n";
    info += "Press space to clear\n";
	info += "Press [c] for circles\n";
	info += "Press [b] for blocks\n";
	info += "Total Bodies: "+ofToString(box2d.getBodyCount())+"\n";
	info += "Total Joints: "+ofToString(box2d.getJointCount())+"\n\n";
	info += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n";
	ofDrawBitmapStringHighlight(info, 30, 30);
    
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
void testApp::contactStart(ofxBox2dContactArgs &e) {
    if(e.a != NULL && e.b != NULL) {
        
        // if we collide with the ground we do not
        // want to play a sound. this is how you do that
        //cout<<"A: "<<e.a->GetType()<<endl;
        //cout<<"B: "<<e.b->GetType()<<endl;
       
        
        
        if((e.a->GetType() == 2 && e.b->GetType() == 0) ||(e.a->GetType() == 0 && e.b->GetType() == 2) ) {
            
            SoundData * aData = (SoundData*)e.a->GetBody()->GetUserData();
            PlayerData * bData = (PlayerData*)e.b->GetBody()->GetUserData();
            
            if (bData == NULL) {
                PlayerData tempData;
                tempData.radius = 50;
                bData = &tempData;
            }
            
            if(aData) {
                aData->bHit = true;
                //cout<<ofMap(bData->radius, 0, 200, 0, 1)<<endl;
                sound[aData->soundID].setVolume(ofMap(bData->radius, 0, 200, 0, 1));
                sound[aData->soundID].play();
            }
            
            if(bData) {
                //bData->bHit = true;
                //sound[bData->soundID].play();
            }
        }
    }
}

//--------------------------------------------------------------
void testApp::contactEnd(ofxBox2dContactArgs &e) {
    if(e.a != NULL && e.b != NULL) {
        
        SoundData * aData = (SoundData*)e.a->GetBody()->GetUserData();
        SoundData * bData = (SoundData*)e.b->GetBody()->GetUserData();
        
        if(aData) {
            aData->bHit = false;
        }
        
        if(bData) {
            bData->bHit = false;
        }
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

