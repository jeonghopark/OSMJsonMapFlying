// http://vector.mapzen.com/osm/all/16/33975/22294.json

// http://www.maptiler.org/google-maps-coordinates-tile-bounds-projection/



#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0, 0, 0);
    ofSetFrameRate(60);
    ofEnableDepthTest();
    
    buildingsMesh_top = buildingsMesh("vectorTile_16_33975_22294.json");
    roadsPolyline_top = roadsPolyline("vectorTile_16_33975_22294.json");

    buildingsMesh_left = buildingsMesh("vectorTile_16_33974_22294.json");
    roadsPolyline_left = roadsPolyline("vectorTile_16_33974_22294.json");

    buildingsMesh_right = buildingsMesh("vectorTile_16_33976_22294.json");
    roadsPolyline_right = roadsPolyline("vectorTile_16_33976_22294.json");

    buildingsMesh_front = buildingsMesh("vectorTile_16_33975_22295.json");
    roadsPolyline_front = roadsPolyline("vectorTile_16_33975_22295.json");

    buildingsMesh_back = buildingsMesh("vectorTile_16_33975_22293.json");
    roadsPolyline_back = roadsPolyline("vectorTile_16_33975_22293.json");

    
    
    camera = ofEasyCam();
//    camera.setPosition(_rootNode_33975_22294->getGlobalPosition());
//    camera.move(0, 0, 300);
//    camera.setTarget(_rootNode_33975_22294->getGlobalPosition());
    
    mainLight = ofLight();
    mainLight.setPointLight();
    mainLight.setGlobalPosition(-100, 0, 500);
    mainLight.setDiffuseColor(ofColor(35, 35, 35));
    mainLight.setSpecularColor(ofColor(170, 170, 170));
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    roadMovingFactor_top = roadMovingFactor_top + 1;
    roadMoving_top = sin( ofDegToRad(roadMovingFactor_top) ) * 0.5 + 0.5;
}


//--------------------------------------------------------------
void ofApp::draw(){
    
    //    ofEnableLighting();
    
    camera.begin();
    
    //    mainLight.enable();
    
    
    drawBuildingsMesh(buildingsMesh_top, ofVec3f(0, 0, 0), ofVec3f(0, 0, 0));

    drawBuildingsMesh(buildingsMesh_left, ofVec3f(-540, 0, -270), ofVec3f(0, 90, 0));

    drawBuildingsMesh(buildingsMesh_right, ofVec3f(540, 0, -270), ofVec3f(0, -90, 0));

    drawBuildingsMesh(buildingsMesh_front, ofVec3f(0, 540, -270), ofVec3f(90, 0, 0));

    drawBuildingsMesh(buildingsMesh_back, ofVec3f(0, -540, -270), ofVec3f(-90, 0, 0));

    
    for (int i=0; i<roadsPolyline_top.size(); i++) {
        roadsPolyline_top[i].draw();
    }

    for (int i=0; i<roadsPolyline_top.size(); i++) {
        ofDrawCircle(roadsPolyline_top[i].getPointAtPercent( roadMoving_top ) , 2);
    }
    
    
    //    mainLight.disable();
    
    camera.end();
    
    //    ofDisableLighting();
    
}

//--------------------------------------------------------------
void ofApp::drawBuildingsMesh(vector< ofMesh > _mesh, ofVec3f _position, ofVec3f _rotation){
    
    ofPushMatrix();
    
    ofTranslate( _position );

    ofRotateX(_rotation.x);
    ofRotateY(_rotation.y);
    ofRotateZ(_rotation.z);
    
    
    for (int i=0; i<_mesh.size(); i++) {
        _mesh[i].draw();
    }
    
    ofPushStyle();
    ofSetColor(255, 160);
    
    for (int i=0; i<_mesh.size(); i++) {
        vector<ofVec3f> & _v = _mesh[i].getVertices();
        for (int j=0; j<_v.size(); j++) {
            ofDrawLine( _v[j] - ofVec3f(0, 0, 0), _v[j] + ofVec3f(0, 0, 100) );
        }
        
        ofBeginShape();
        vector<ofVec3f>& vertices = _mesh[i].getVertices();
        for(int j = 0; j < vertices.size(); j++) {
            ofVertex(vertices[j]);
        }
        ofEndShape();
        
        ofBeginShape();
        vector<ofVec3f>& verticesUp = _mesh[i].getVertices();
        for(int j = 0; j < verticesUp.size(); j++) {
            ofVec3f _v = verticesUp[j] + ofVec3f(0, 0, 100);
            ofVertex(_v);
        }
        ofEndShape();
        
    }
    ofPopStyle();
    
    
    ofPopMatrix();

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
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}



//--------------------------------------------------------------
vector< ofMesh > ofApp::buildingsMesh(string _fileName){

    vector< ofMesh > _return;
    
    FeatureNode * _rootNode;
    
    JsonLoader _jsonLoader = JsonLoader(_fileName);
    _rootNode = _jsonLoader.loadNodeGraph();
    
    ofxJSONElement _jsonMain;
    _jsonMain = _jsonLoader.jsonRoot;
    
    ofxJSONElement _jsonBuildings;
    _jsonBuildings = _jsonMain["buildings"]["features"];
    
    
    for (int i=0; i<_jsonBuildings.size(); i++) {
        ofxJSONElement _jsonBuilding;
        _jsonBuilding = _jsonBuildings[i]["geometry"]["coordinates"][0];
        
        ofMesh _m;
        _m.setMode(OF_PRIMITIVE_LINE_LOOP);
        
        for (int j=0; j<_jsonBuilding.size(); j++) {
            
            ofxJSONElement _coordinateBuilding;
            _coordinateBuilding = _jsonBuilding[j];
            
            ofVec2f _v;
            _v.x = _jsonLoader.lon2x(_coordinateBuilding[0].asFloat()) - _rootNode->getX();
            _v.y = _jsonLoader.lat2y(_coordinateBuilding[1].asFloat()) - _rootNode->getY();
            
            _m.addVertex(_v);
            _m.addColor( ofColor(255) );
            
        }
        
        _return.push_back( _m );
    
    }
    
    _rootNode->setPosition(0, 0, 0);
//    _rootNode->printPosition("");
    
    return _return;
    
}


//--------------------------------------------------------------
vector< ofPolyline > ofApp::roadsPolyline(string _fileName){
    
    vector< ofPolyline > _return;
    
    FeatureNode * _rootNode;
    
    JsonLoader _jsonLoader = JsonLoader(_fileName);
    _rootNode = _jsonLoader.loadNodeGraph();
    
    ofxJSONElement _jsonMain;
    _jsonMain = _jsonLoader.jsonRoot;

    ofxJSONElement _jsonRoads;
    _jsonRoads = _jsonMain["roads"]["features"];
    
    
    for (int i=0; i<_jsonRoads.size(); i++) {
        ofxJSONElement _jsonRoad;
        
        
        string _multiString = _jsonRoads[i]["geometry"]["type"].asString();
        
        ofPolyline _pl;
        
        if (_multiString != "MultiLineString") {
            
            _jsonRoad = _jsonRoads[i]["geometry"]["coordinates"];
            
            for (int j=0; j<_jsonRoad.size(); j++) {
                
                ofxJSONElement _coordinateRoad;
                _coordinateRoad = _jsonRoad[j];
                
                ofVec2f _v;
                _v.x = _jsonLoader.lon2x(_jsonRoad[j][0].asFloat()) - _rootNode->getX();
                _v.y = _jsonLoader.lat2y(_jsonRoad[j][1].asFloat()) - _rootNode->getY();
                
                _pl.addVertex(_v);
                
            }
            
            _return.push_back( _pl );
            
            
        } else {
            
            _jsonRoad = _jsonRoads[i]["geometry"]["coordinates"][0];
            
            for (int j=0; j<_jsonRoad.size(); j++) {
                
                ofxJSONElement _coordinateRoad;
                _coordinateRoad = _jsonRoad[j];
                
                ofVec2f _v;
                _v.x = _jsonLoader.lon2x(_jsonRoad[j][0].asFloat()) - _rootNode->getX();
                _v.y = _jsonLoader.lat2y(_jsonRoad[j][1].asFloat()) - _rootNode->getY();
                
                _pl.addVertex(_v);
                
            }
            
            _return.push_back( _pl );
            
        }
        
    }
    
    
    _rootNode->setPosition(0, 0, 0);
    //    _rootNode->printPosition("");
    
    return _return;
    
}



