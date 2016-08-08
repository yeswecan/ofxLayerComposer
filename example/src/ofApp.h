#pragma once

#include "ofMain.h"
#include "ofxLayerComposer.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void draw1() {
        ofSetColor(255);
        for (int j = 0; j < 50; j++) {
            for (int i = 0; i < 50; i++) {
                ofSetColor(255 * sin(i / 20 + time * 1.2),
                           0,
                           0,
                           150 + 100 * sin(ofGetElapsedTimef() * 2 + i + j * 2));
                ofDrawCircle(ofNoise(i + time * 1.2) *  ofGetWidth(),
                             ofNoise(i + time * 2.4) *  ofGetHeight(), ofNoise(i + time / 2.5) * 190);
                
            }
        }
    }
    
    void draw2() {
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
    }
    
    void draw3() {
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
    }
    
    void draw4() {
        ofSetColor(ofRandom(255));
        ofDrawRectangle(200, 200, 75 + sin(ofGetElapsedTimef() * 2) * 175,
                        80 + cos(ofGetElapsedTimef() * 4) * 75);
        ofDrawRectangle(600, 200, 75 + sin(ofGetElapsedTimef() * 2) * 175,
                        80 + cos(ofGetElapsedTimef() * 4) * 75);
        ofDrawRectangle(500, 600, 75 + sin(ofGetElapsedTimef() * 2) * 175,
                        80 + cos(ofGetElapsedTimef() * 4) * 75);
    }
    
    float time;
		
    ofxLayerComposer layerComposer;
    ShaderProcessor shader;
    
    LCLayer *layer1, *layer2, *layer3, *layer4;
    ofFbo fbo, fbo2;
    
    ofImage masked1, masked2, masked3, masked4;
    
    float rr = 0;
};
