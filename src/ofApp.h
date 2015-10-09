#pragma once

#include "ofMain.h"
#include "GuiApp.h"
#include "BaseArch.h"

#include "ofxImmediateModeInput.h"
#include "ofxFirstPersonCamera.h"


#include "FeatureNode.h"

#include "JsonLoader.h"

#include "ofxJSON.h"

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
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    
    shared_ptr<GuiApp> gui;
    
    BaseArch baseArch;
    
    ofEasyCam camera;
    ofLight mainLight;
    
    vector< ofMesh > buildings_33975_22294;
    vector< ofMesh > roads_33975_22294;
    
    vector< ofPolyline > buildingsPolyline_33975_22294;
    vector< ofPolyline > roadsPolyline_33975_22294;
    
    float roadMoving_33975_22294;
    float roadMovingFactor_33975_22294;
    
    
    double y2lat(double y) { return ofRadToDeg(2 * atan(exp(ofDegToRad(y))) - PI / 2); }
    double x2lon(double x) { return ofRadToDeg(x / R_EARTH); }
    double lat2y(double lat) { return R_EARTH * log(tan(PI / 4 + ofDegToRad(lat) / 2)); }
    double lon2x(double lon) { return ofDegToRad(lon) * R_EARTH; }
    
    
    float mainOffSetXPos, mainOffSetYPos;


    // Flying
    ofxImmediateModeInput in;
    ofxFirstPersonCamera cam;
    vector<ofPolyline> paint;

};
