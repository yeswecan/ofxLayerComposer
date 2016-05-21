#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
//    ofToggleFullscreen();
    
    layerComposer.addLayer(layer2 = new LCLayer(ofGetWidth(), ofGetHeight()));
    layerComposer.addLayer(layer3 = new LCLayer(ofGetWidth(), ofGetHeight()));
    layerComposer.addLayer(layer1 = new LCLayer(ofGetWidth(), ofGetHeight()));
    layerComposer.addLayer(layer4 = new LCLayer(ofGetWidth(), ofGetHeight()));
    
    masked1.load("waterfall_1.jpg");
    masked2.load("waterfall_2.jpg");
    masked3.load("waterfall_3.jpg");
    masked4.load("waterfall_4.jpg");
    
    layer1->visible = true;
    layer2->visible = true;
    layer3->visible = true;
    layer4->visible = true;
    
    layer1->addMaskedImage(&masked1.getTexture());
//    layer2->addMaskedImage(&masked2.getTexture());
//    layer3->addMaskedImage(&masked3.getTexture());
//    layer4->addMaskedImage(&masked4.getTexture());
    
    fbo.allocate(ofGetScreenWidth(), ofGetScreenHeight());
    fbo.begin();
        ofClear(0);
        ofSetColor(255);
        float time = ofGetElapsedTimef();
        int freq = 5;
        for (int j = 0; j < freq; j++) {
            for (int i = 0; i < freq; i++) {
                ofSetColor(255 * sin((float)i / 20 + time),
                           255 * cos((float)i / 5 + time * 2),
                           255 * sin((float)i / 2 + time), 255 * ofNoise(i, j, time * 2));
                float xsize = (float)ofGetScreenWidth() / freq;
                float ysize = (float)ofGetScreenHeight() / freq;
                float x = xsize * j;
                float y = ysize * i;
                ofDrawRectangle(x, y, xsize, ysize);
            }
        }
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::update(){
    float time = ofGetElapsedTimef();
    
    layer1->blurRadius = 1.5;
    layer1->begin();
        ofClear(0);
        ofSetColor(255);
        for (int j = 0; j < 25; j++) {
            for (int i = 0; i < 25; i++) {
                ofSetColor(255 * sin(i / 20 + time), 0, 0, 150 + 100 * sin(ofGetElapsedTimef() * 2 + i + j * 2));
                ofDrawCircle(ofNoise(i + time) *  ofGetWidth(),
                             ofNoise(i + time * 2) *  ofGetHeight(), ofNoise(i + time / 2) * 190);
                
            }
        }
    layer1->end();


    layer2->begin();
        ofClear(0);
        ofSetColor(255);
        int freq = 15;
        for (int j = 0; j < freq; j++) {
            for (int i = 0; i < freq; i++) {
                ofSetColor(255 * sin((float)i / 20 + time),
                           255 * cos((float)i / 5 + time * 2),
                           255 * sin((float)i / 2 + time), 255 * ofNoise(i, j, time * 2));
                float xsize = (float)ofGetWidth() / freq;
                float ysize = (float)ofGetHeight() / freq;
                float x = xsize * j;
                float y = ysize * i;
                ofDrawRectangle(x, y, xsize, ysize);
            }
        }
    layer2->end();
    
    
    layer3->begin();
        ofSetColor(255);
            ofPushMatrix();
                ofTranslate(300, 50);
                ofBeginShape();
                    ofVertex(200, 200);
                    ofVertex(270, 210);
                    ofVertex(300, 320);
                    ofVertex(200, 280);
                ofEndShape();
            ofPopMatrix();
            ofPushMatrix();
                ofTranslate(300, 350);
                ofBeginShape();
                    ofVertex(200, 200);
                    ofVertex(270, 210);
                    ofVertex(300, 320);
                    ofVertex(200, 280);
                ofEndShape();
            ofPopMatrix();
    
    layer3->end();
    
    layer4->begin();
        ofSetColor(ofRandom(255));
        ofDrawRectangle(200, 200, 75 + sin(ofGetElapsedTimef() * 2) * 175,
                        80 + cos(ofGetElapsedTimef() * 4) * 75);
        ofDrawRectangle(600, 200, 75 + sin(ofGetElapsedTimef() * 2) * 175,
                    80 + cos(ofGetElapsedTimef() * 4) * 75);
        ofDrawRectangle(500, 600, 75 + sin(ofGetElapsedTimef() * 2) * 175,
                    80 + cos(ofGetElapsedTimef() * 4) * 75);
    layer4->end();

    
    layerComposer.update(); // rendering the frames
}

//--------------------------------------------------------------
void ofApp::draw(){
    rr = sin(ofGetElapsedTimef() * 3) * 125 + 125;
    ofClear(0);
    ofSetColor(255);
//    ofDrawRectangle(0, 0, 320, 240);
    
//    shader.update();
//    shader.getTexture().draw(0, 0, 400, 350);
    
    layerComposer.draw(0, 0, ofGetWidth(), ofGetHeight());
    ofDrawBitmapString(ofToString(ofGetFrameRate()), 10, 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
