#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    JsonLoader jsonLoader = JsonLoader("vectorTile.json");
    rootNode = jsonLoader.loadNodeGraph();
    
    ofxJSONElement _jsonMain;
    _jsonMain = jsonLoader.jsonRoot;
    
    ofxJSONElement _jsonBuildings;
    _jsonBuildings = _jsonMain["buildings"]["features"];
    
    for (int i=0; i<_jsonBuildings.size(); i++) {
        ofxJSONElement _jsonBuilding;
        _jsonBuilding = _jsonBuildings[i]["geometry"]["coordinates"][0];
        
        ofMesh _m;
        _m.setMode(OF_PRIMITIVE_LINE_LOOP);
        
        ofPolyline _pl;
        
        _pl.begin();
        
        for (int j=0; j<_jsonBuilding.size(); j++) {
            
            ofxJSONElement _coordinateBuilding;
            _coordinateBuilding = _jsonBuilding[j];
            
            ofVec2f _v;
            _v.x = jsonLoader.lon2x(_coordinateBuilding[0].asFloat()) - rootNode->getX();
            _v.y = jsonLoader.lat2y(_coordinateBuilding[1].asFloat()) - rootNode->getY();
            
            _m.addVertex(_v);
            _m.addColor( ofColor(255) );
            
            _pl.addVertex( _v );
            
        }
        
        buildings.push_back( _m );
        
        _pl.end();
        buildingsPolyline.push_back(_pl);
        
    }
    
    
    
    ofxJSONElement _jsonRoads;
    _jsonRoads = _jsonMain["roads"]["features"];
    
    for (int i=0; i<_jsonRoads.size(); i++) {
        ofxJSONElement _jsonRoad;
        
        
        string _multiString = _jsonRoads[i]["geometry"]["type"].asString();
        
        if (_multiString != "MultiLineString") {
            
            _jsonRoad = _jsonRoads[i]["geometry"]["coordinates"];
            ofMesh _m;
            _m.setMode(OF_PRIMITIVE_LINE_STRIP);
            
            
            for (int j=0; j<_jsonRoad.size(); j++) {
                
                ofxJSONElement _coordinateRoad;
                _coordinateRoad = _jsonRoad[j];

                ofVec2f _v;
                _v.x = jsonLoader.lon2x(_jsonRoad[j][0].asFloat()) - rootNode->getX();
                _v.y = jsonLoader.lat2y(_jsonRoad[j][1].asFloat()) - rootNode->getY();
                
                _m.addVertex(_v);
                _m.addColor( ofColor(255) );
            }
            
            roads.push_back( _m );
            
        } else {
            
            _jsonRoad = _jsonRoads[i]["geometry"]["coordinates"][0];
            ofMesh _m;
            _m.setMode(OF_PRIMITIVE_LINE_STRIP);
            
            
            for (int j=0; j<_jsonRoad.size(); j++) {
                
                ofxJSONElement _coordinateRoad;
                _coordinateRoad = _jsonRoad[j];
                
                ofVec2f _v;
                _v.x = jsonLoader.lon2x(_jsonRoad[j][0].asFloat()) - rootNode->getX();
                _v.y = jsonLoader.lat2y(_jsonRoad[j][1].asFloat()) - rootNode->getY();
                
                _m.addVertex(_v);
                _m.addColor( ofColor(255) );
            }
            
            roads.push_back( _m );
            
        }
        
    }
    
    
    
    rootNode->setPosition(0, 0, 0);
    
    ofBackground(0, 0, 0);
    ofSetFrameRate(60);
    ofEnableDepthTest();
    
    camera = ofEasyCam();
    camera.setPosition(rootNode->getGlobalPosition());
    camera.move(0, 0, 300);
    camera.setTarget(rootNode->getGlobalPosition());
    
    mainLight = ofLight();
    mainLight.setPointLight();
    mainLight.setGlobalPosition(-100, 0, 500);
    mainLight.setDiffuseColor(ofColor(35, 35, 35));
    mainLight.setSpecularColor(ofColor(170, 170, 170));
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}


//--------------------------------------------------------------
void ofApp::draw(){
    
    //    ofEnableLighting();
    
    camera.begin();
    
    //    mainLight.enable();
    
    
    for (int i=0; i<buildings.size(); i++) {
        buildings[i].draw();
    }

    ofPushStyle();
    ofSetColor(255, 160);

    for (int i=0; i<buildings.size(); i++) {
        vector<ofVec3f> & _v = buildings[i].getVertices();
        for (int j=0; j<_v.size(); j++) {
            ofDrawLine( _v[j] - ofVec3f(0, 0, 0), _v[j] + ofVec3f(0, 0, 100) );
        }
    }
    ofPopStyle();
    
    
    for (int i=0; i<roads.size(); i++) {
        roads[i].draw();
    }
    
    
    ofPushStyle();
    ofSetColor(255, 180);
    for (int i=0; i<buildingsPolyline.size(); i++) {

        buildingsPolyline[i].draw();
        
        ofBeginShape();
        vector<ofVec3f>& vertices = buildingsPolyline[i].getVertices();
        for(int j = 0; j < vertices.size(); j++) {
            ofVertex(vertices[j]);
        }
        ofEndShape();

        ofBeginShape();
        vector<ofVec3f>& verticesUp = buildingsPolyline[i].getVertices();
        for(int j = 0; j < verticesUp.size(); j++) {
            ofVec3f _v = verticesUp[j] + ofVec3f(0, 0, 100);
            ofVertex(_v);
        }
        ofEndShape();
    }
    ofPopStyle();
    
    
    
    //    mainLight.disable();
    
    camera.end();
    
    //    ofDisableLighting();
    
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
