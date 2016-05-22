//
//  ShaderProcessor.h
//
//  Created by zebra on 12/06/15.
//

#ifndef ShaderProcessor_h
#define ShaderProcessor_h

#include "ofMain.h"

#define GLSL120(shader)  "#version 120 \n #extension GL_ARB_texture_rectangle : enable \n" #shader
#define GLSL150(shader)  "#version 150 \n" #shader

//#define SHADER_DEBUG_MODE_ON // undefine to disable shader live-editing,
                               // which worked good a while ago, on poco

class ShaderProcessor: ofShader {
public:
    ShaderProcessor(): ofShader() {
        singular.allocate(1, 1, GL_RGB8);
        clearEveryFrame = true;
    }
    
    void reloadShader() {
        load(shaderName);
    }
    
    void setup (int width, int height, string shaderName) {
        result.allocate(width, height, GL_RGBA);
        result.begin();
            ofClear(0,0);
        result.end();
        
        load(shaderName);
        this->shaderName = shaderName;
        ofFile file;
        file.open(shaderName + ".frag");
        file.close();
    }
    
    void setupFromString (int width, int height, string shader) {
        result.allocate(width, height, GL_RGBA32F);
        result.begin();
            ofClear(0,0);
        result.end();

        setupShaderFromSource(GL_VERTEX_SHADER, GLSL120(
            varying vec2 texCoordVarying;
            attribute vec2 texcoord;

            void main() {
            
                gl_TexCoord[0] = gl_MultiTexCoord0; \n
                gl_TexCoord[1] = gl_MultiTexCoord1; \n
                gl_TexCoord[2] = gl_MultiTexCoord2; \n
                texCoordVarying = texcoord;
                vec4 eyeCoord  = gl_ModelViewMatrix * gl_Vertex; \n
                gl_Position    = gl_ProjectionMatrix * eyeCoord; \n
                gl_FrontColor  = gl_Color;
                
            
            }
                                                       
                                                       ));
        
        setupShaderFromSource(GL_FRAGMENT_SHADER, shader);
        linkProgram();
        this->shaderName = shaderName;
//        ofFile file;
//        file.open(shaderName + ".frag");
//        file.close();
    }
    
    
    void addInputTexture(ofTexture *texture, string name) {
        inputTextures.push_back(texture);
        inputTextureNames.push_back(name);
    }
    
    void clearBlack() {
        result.begin();
            ofClear(0);
        result.end();
    }
    
    void update() {
        result.begin();
//            if (clearEveryFrame)
                ofClear(255, 0);
        
            ofSetColor(255);
            begin();
                if (inputTextures.size() > 0)
                for (int i = 0; i < inputTextures.size(); i++) {
                    setUniformTexture(inputTextureNames[i], *inputTextures[i], i + 1);
                    setUniform2f(inputTextureNames[i] + "Resolution", inputTextures[i]->getWidth(), inputTextures[i]->getHeight());
                }
        
                if (parameters.size() > 0) {
                    map<string, ShaderParameterType>::const_iterator it;
                    for (it = parameters.begin(); it != parameters.end(); it++) {
                        ShaderParameterType *parameter = &parameters[it->first];
                        if (parameter->kind == 1) {
                            setUniform1f(parameter->name, parameter->floatParam);
                        }
                        if (parameter->kind == 2) {
                            setUniform2f(parameter->name, parameter->vec2Param.x,parameter->vec2Param.y);
                        }
                        if (parameter->kind == 3) {
                            setUniform3f(parameter->name, parameter->vec3Param.x,parameter->vec3Param.y, parameter->vec4Param.y);
                        }
                    }
                }
                //printActiveUniforms();
                //printActiveAttributes();
                singular.draw(0, 0, result.getWidth(), result.getHeight());
            end();
        result.end();
        
        
        /* // worked on poco
#ifdef SHADER_DEBUG_MODE_ON
        ofFile file;
        file.open(shaderName + ".frag");
            if (file.getPocoFile().getLastModified() != shaderModifiedTime) {
                reloadShader();
            }
        file.close();
#endif
        */
    }
    
    ofTexture& getTexture() {
        return result.getTextureReference();
    }
    
    ofTexture& getTextureReference() {
        return result.getTextureReference();
    }

    ofPixels* getPixels() {
        result.readToPixels(pixels);
        return &pixels;
    }
    
    void resize(int width, int height) {
        resolution = ofPoint(width, height);
        result.allocate(width, height);
    }
    
    class ShaderParameterType {
    public:
        int kind; // 1 for float, 2 for vec2, 3 for vec3, 4 for vec4
        float floatParam;
        ofPoint vec2Param, vec3Param, vec4Param;
        string name;
        
        void operator= (float value) {
            floatParam = value;
        }
        void operator= (ofVec2f value) {
            vec2Param = value;
        }
        void operator= (ofVec3f value) {
            vec3Param = value;
        }
        void operator= (ofVec4f value) {
            vec4Param = value;
        }
    };
    
    ShaderParameterType& operator[] (string parameterName) {
        return parameters[parameterName];
    }
    
    void addFloatParameter(string name, float value = 0.) {
        ShaderParameterType param;
        param.name = name;
        param.kind = 1;
        parameters[name] = param;
        parameters[name].floatParam = value;
    }
    
    void addVec2fParameter(string name, ofVec2f value = ofVec2f(0)) {
        ShaderParameterType param;
        param.name = name;
        param.kind = 2;
        parameters[name] = param;
        parameters[name].vec2Param = value;
    }

    void addVec3fParameter(string name, ofVec3f value = ofVec3f(0)) {
        ShaderParameterType param;
        param.name = name;
        param.kind = 2;
        parameters[name] = param;
        parameters[name].vec3Param = value;
    }
    
    void clear() {
        result.begin();
            ofClear(255, 0);
        result.end();
    }
    
    bool clearEveryFrame;
    
private:
    
    std::map<string, ShaderParameterType> parameters;
    
    ofFbo singular; // little fbo used here to setup drawing easily
    ofFbo result;
    ofPoint resolution;
    ofPixels pixels;
    
    vector<ofTexture*> inputTextures;
    vector<string> inputTextureNames;
    
    string shaderName;

//    Poco::Timestamp shaderModifiedTime;
};

#endif
