
#ifndef ofxLayerComposer_h
#define ofxLayerComposer_h

#include "ofMain.h"
#include "ShaderProcessor.h"

class LCLayer: public ofFbo {
public:
    LCLayer(int numsamples = 0) {
        ofDisableArbTex();
        allocate(ofGetScreenWidth(), ofGetScreenHeight(), GL_RGBA, numsamples);
        this->width = ofGetScreenWidth();
        this->height = ofGetScreenHeight();
        
        initShader();
        
        clear();
    }
    
    LCLayer(int width, int height, int numsamples = 0) {
        allocate(width, height, GL_RGBA, numsamples);
        this->width = width;
        this->height = height;
        
        initShader();
        
        clear();
    }
    
    void clear() {
        begin();
            ofClear(255);
        end();
    }
    
    void begin() {
        ((ofFbo*)this)->begin();
        ofClear(255); // 
    }
    
    void end() {
        ((ofFbo*)this)->end();
    }
    
    void initShader() {
        
        
        blurAndMask.setupFromString(width, height,  GLSL120(
                                                                                                        
                    uniform sampler2DRect tex1;
                    uniform sampler2DRect maskedImage;
                    
                    uniform vec2 tex1Resolution;
                    uniform vec2 maskedImageResolution;
                    
//                    uniform vec4 mask;
                                                                                                        
                    uniform float maskSource; // -1 = no mask 0 = r, 1 = g, 2 = b, 3 = a, 4 = V
                                                                                                        
                    uniform float blurRadius;
                                                            
                    vec4 blur(sampler2DRect texture, vec2 st, float offset)
                    {
                        float texOffset = offset;
                        
                        vec2 tc0 = st + vec2(-texOffset, -texOffset);
                        vec2 tc1 = st + vec2(         0.0, -texOffset);
                        vec2 tc2 = st + vec2(+texOffset, -texOffset);
                        vec2 tc3 = st + vec2(-texOffset,          0.0);
                        vec2 tc4 = st + vec2(         0.0,          0.0);
                        vec2 tc5 = st + vec2(+texOffset,          0.0);
                        vec2 tc6 = st + vec2(-texOffset, +texOffset);
                        vec2 tc7 = st + vec2(         0.0, +texOffset);
                        vec2 tc8 = st + vec2(+texOffset, +texOffset);
                        
                        vec4 col0 = texture2DRect(texture, tc0 * tex1Resolution);
                        vec4 col1 = texture2DRect(texture, tc1 * tex1Resolution);
                        vec4 col2 = texture2DRect(texture, tc2 * tex1Resolution);
                        vec4 col3 = texture2DRect(texture, tc3 * tex1Resolution);
                        vec4 col4 = texture2DRect(texture, tc4 * tex1Resolution);
                        vec4 col5 = texture2DRect(texture, tc5 * tex1Resolution);
                        vec4 col6 = texture2DRect(texture, tc6 * tex1Resolution);
                        vec4 col7 = texture2DRect(texture, tc7 * tex1Resolution);
                        vec4 col8 = texture2DRect(texture, tc8 * tex1Resolution);
                        
                        vec4 source = texture2DRect(tex1, st * tex1Resolution);
                        
                        vec4 sum = (1.0 * col0 + 2.0 * col1 + 1.0 * col2 +
                                    2.0 * col3 + 4.0 * col4 + 2.0 * col5 +
                                    1.0 * col6 + 2.0 * col7 + 1.0 * col8) / 16.0;
                        vec4 result = vec4(sum.rgb, sum.a);
                        return result;
                    }
                                                             
                    
                    void main( void )
                    {
                        vec2 st = gl_TexCoord[0].st;
                        
                        
                        vec4 colorTex1 = texture2DRect(tex1, st * tex1Resolution);
                        vec4 colorTex2 = texture2DRect(maskedImage, st * maskedImageResolution);
                        
                        if (blurRadius == 0) {
                            gl_FragColor = colorTex2;
                        }

                        if ((maskSource == -1) && (blurRadius != 0)) { // no mask and blur
                            gl_FragColor = blur(tex1, st, blurRadius) * 0.5 + blur(tex1, st, blurRadius * 1.5) * 0.5; // * 0.5 + colorTex1 * 0.5;//colorTex1;
						}

						if ((maskSource == -1) && (blurRadius == 0)) {
							gl_FragColor = colorTex1;
						}
                        
                        if (maskSource == 3) { // alpha mask + blur
                            vec4 result = blur(tex1, st, blurRadius) * 0.5 + blur(tex1, st, blurRadius * 1.5) * 0.5;
                            result.rgb = colorTex2.rgb;
                            gl_FragColor = result;
                            
						}
                    }
        ));
        blurAndMask.addInputTexture(&getTexture(), "tex1");
        blurAndMask.addFloatParameter("blurRadius");
        blurAndMask.addFloatParameter("maskSource");
    }
    
    void addMaskedImage(ofTexture* maskedImage) {
        this->maskedImage = maskedImage;
        blurAndMask.addInputTexture(maskedImage, "maskedImage");
        maskSource = 3;
    }
    
    void update() {
        updateTexture(0);
        blurAndMask["blurRadius"] = blurRadius / 100.;
        blurAndMask["maskSource"] = maskSource;
        blurAndMask.update();
    }
    
    void draw() {
        blurAndMask.getTexture().draw(0, 0, width, height);
        
    }
    
    void draw(int x, int y, int w, int h) {
        blurAndMask.getTexture().draw(x, y, w, h);

//        getTexture().draw(0, 0);
//        getTexture().draw(0, 0);
    }

    
    ofTexture *maskedImage = nullptr;
    int maskSource = -1; // -1 = no mask 0 = r, 1 = g, 2 = b, 3 = a, 4 = V
    bool visible = true;
    
    // Visual settings
    
    float blurRadius = 0;

    
private:
    ShaderProcessor blurAndMask;
    
    int width, height;
    
};


class ofxLayerComposer {
    
    ofFbo result;
    
    int width, height;
    
    vector<LCLayer*> layers;

public:
    ofxLayerComposer() {
        width = ofGetScreenWidth();
        height = ofGetScreenHeight();
    }
    
    ofxLayerComposer(int width, int height) {
        this->width = width;
        this->height = height;
    }
    
    void update() {
        for (auto i: layers) i->update();
    }
    
    void draw() {
        for (auto i: layers) if (i->visible) i->draw();
    }
    
    void draw(int x, int y, int w, int h) {
        for (auto i: layers) {
            if (i->visible) i->draw(x, y, w, h);
        }
    }
    
    void addLayer(LCLayer* l) {
        layers.push_back(l);
    }
};


#endif /* ofxLayerComposer_h */
