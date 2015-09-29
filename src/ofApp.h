#pragma once

#include "ofMain.h"
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
    
    ofEasyCam camera;
    ofLight mainLight;

    vector< ofMesh > buildingsMesh_top;
    vector< ofMesh > roads_top;

    vector< ofMesh > buildingsMesh_left;
    vector< ofMesh > roads_left;

    vector< ofMesh > buildingsMesh_right;
    vector< ofMesh > roads_right;

    vector< ofMesh > buildingsMesh_front;
    vector< ofMesh > roads_front;

    vector< ofMesh > buildingsMesh_back;
    vector< ofMesh > roads_back;

    vector< ofMesh > buildingsMesh_bottom;
    vector< ofMesh > roads_bottom;

    vector< ofPolyline > buildingsPolyline_top;
    vector< ofPolyline > roadsPolyline_top;

    vector< ofPolyline > buildingsPolyline_left;
    vector< ofPolyline > roadsPolyline_left;

    vector< ofPolyline > buildingsPolyline_right;
    vector< ofPolyline > roadsPolyline_right;

    vector< ofPolyline > buildingsPolyline_front;
    vector< ofPolyline > roadsPolyline_front;

    vector< ofPolyline > buildingsPolyline_back;
    vector< ofPolyline > roadsPolyline_back;

    vector< ofPolyline > buildingsPolyline_bottom;
    vector< ofPolyline > roadsPolyline_bottom;

    
    float roadMoving_top;
    float roadMovingFactor_top;

    float roadMoving_left;
    float roadMovingFactor_left;

    vector< ofMesh > buildingsMesh(string _fileName );
    vector< ofPolyline > roadsPolyline(string _fileName );
    
    void drawBuildingsMesh(vector< ofMesh > _mesh, ofVec3f _position, ofVec3f _rotation);
    void drawRoadPolyLineMoving(vector< ofPolyline > _polyline, ofVec3f _position, ofVec3f _rotation);
  
    void drawEdgeShape();
    ofImage originArchBase;

};
