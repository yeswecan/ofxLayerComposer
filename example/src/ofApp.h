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
		
    ofxLayerComposer layerComposer;
    ShaderProcessor shader;
    
    LCLayer *layer1, *layer2, *layer3, *layer4;
    ofFbo fbo, fbo2;
    
    ofImage masked1, masked2, masked3, masked4;
    
    float rr = 0;
};
