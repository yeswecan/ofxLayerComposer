#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
//    ofToggleFullscreen();
    
    layerComposer.addLayer(layer2 = new LCLayer(ofGetWidth(), ofGetHeight(), 0));
    layerComposer.addLayer(layer3 = new LCLayer(ofGetWidth(), ofGetHeight(), 0));
    layerComposer.addLayer(layer1 = new LCLayer(ofGetWidth(), ofGetHeight(), 0));
    layerComposer.addLayer(layer4 = new LCLayer(ofGetWidth(), ofGetHeight(), 0));
    
    masked1.load("waterfall_1.jpg");
    masked2.load("waterfall_2.jpg");
    masked3.load("waterfall_3.jpg");
    masked4.load("waterfall_4.jpg");
    
    layer1->visible = true;
    layer2->visible = true;
    layer3->visible = true;
    layer4->visible = true;
    
    layer1->addMaskedImage(&masked1.getTexture());
    layer2->addMaskedImage(&masked2.getTexture());
    layer3->addMaskedImage(&masked3.getTexture());
    layer4->addMaskedImage(&masked4.getTexture());
    
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

}

//--------------------------------------------------------------
void ofApp::draw(){
    time = ofGetElapsedTimef() / 4;
    
    ofClear(0);

    if (!ofGetKeyPressed('z')) {
        layer1->blurRadius = 0.5;
        layer1->begin();
            draw1();
        layer1->end();
        
        
        layer2->blurRadius = 0.7;
        layer2->begin();
            draw2();
        layer2->end();
        
        
        layer3->blurRadius = 0.9;
        layer3->begin();
            draw3();
        layer3->end();
        
        layer4->blurRadius = 2.5;
        layer4->begin();
            draw4();
        layer4->end();
        
        
        layerComposer.update(); // rendering the frames
        
        ////////////////////////////////////////////////////////
        
        rr = sin(ofGetElapsedTimef() * 3) * 125 + 125;
        ofSetColor(255);
        
//        layer4->draw();
//        layer4->getSourceTexture()->draw(0, 0);
        layerComposer.draw(0, 0, ofGetWidth(), ofGetHeight());
    } else {
        ofEnableAlphaBlending();
        draw2();
        draw3();
        draw1();
        draw4();
    }
    
    
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
