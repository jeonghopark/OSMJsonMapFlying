// http://vector.mapzen.com/osm/all/16/33975/22294.json

// http://www.maptiler.org/google-maps-coordinates-tile-bounds-projection/


#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0, 0, 0);
    ofSetFrameRate(60);
    ofEnableDepthTest();

    
    cam.setNearClip(0.0001f);
    cam.setFarClip(10000.0f);
    cam.toggleControl();
    cam.setPosition(0, 0, 700);

    
    FeatureNode* _rootNode_33975_22294;
    
    JsonLoader _jsonLoader_33975_22294 = JsonLoader("OSMJSON.json");
    _rootNode_33975_22294 = _jsonLoader_33975_22294.loadNodeGraph();
    
    ofxJSONElement _jsonMain;
    _jsonMain = _jsonLoader_33975_22294.jsonRoot;
    
    ofxJSONElement _jsonBuildings;
    _jsonBuildings = _jsonMain["features"];
    
    
    
    
    for (int i=0; i<_jsonBuildings.size(); i++) {
        
        string _way = _jsonBuildings[i]["id"].asString();
        
        if (_way.at(0) == 'w') {
            ofxJSONElement _jsonBuilding;
            _jsonBuilding = _jsonBuildings[i]["geometry"]["coordinates"][0];
            
            ofMesh _m;
            _m.setMode(OF_PRIMITIVE_LINE_LOOP);
            
            ofPolyline _pl;
            _pl.setClosed(false);
            _pl.begin();
            
            string _polygon = _jsonBuildings[i]["geometry"]["type"].asString();
            
            if (_polygon == "Polygon") {
                
                for (int j=0; j<_jsonBuilding.size(); j++) {
                    
                    ofxJSONElement _coordinateBuilding;
                    _coordinateBuilding = _jsonBuilding[j];
                    
                    
                    glm::vec3 _v;
                    _v.x = _jsonLoader_33975_22294.lon2x(_coordinateBuilding[0].asFloat()) - 740603;
                    _v.y = _jsonLoader_33975_22294.lat2y(_coordinateBuilding[1].asFloat()) - 6.40447e+06;
                    
                    
                    _m.addVertex(_v);
                    _m.addColor( ofColor(255) );
                    
                    _pl.addVertex( _v );
                    
                }
                
                
                buildings_33975_22294.push_back( _m );
                
                _pl.end();
                buildingsPolyline_33975_22294.push_back(_pl);
            }
            
        }
        
        
    }
    
    
    
    ofxJSONElement _jsonRoads;
    _jsonRoads = _jsonMain["features"];
    
    for (int i=0; i<_jsonRoads.size(); i++) {
        ofxJSONElement _jsonRoad;
        
        
        string _way = _jsonRoads[i]["id"].asString();
        
        if (_way.at(0) == 'w') {
            
            ofMesh _m;
            _m.setMode(OF_PRIMITIVE_LINE_STRIP);
            
            ofPolyline _pl;
            
            string _LineString = _jsonRoads[i]["geometry"]["type"].asString();
            
            if (_LineString == "LineString") {
                
                _jsonRoad = _jsonRoads[i]["geometry"]["coordinates"];
                
                for (int j=0; j<_jsonRoad.size(); j++) {
                    
                    ofxJSONElement _coordinateRoad;
                    _coordinateRoad = _jsonRoad[j];
                    
                    glm::vec3 _v;
                    _v.x = _jsonLoader_33975_22294.lon2x(_jsonRoad[j][0].asFloat()) - 740603;
                    _v.y = _jsonLoader_33975_22294.lat2y(_jsonRoad[j][1].asFloat()) - 6.40447e+06;
                    
                    _m.addVertex(_v);
                    _m.addColor( ofColor(255) );
                    
                    _pl.addVertex(_v);
                    
                    
                }
                
                roads_33975_22294.push_back( _m );
                roadsPolyline_33975_22294.push_back( _pl );
                
                
            } else {
                
                //                _jsonRoad = _jsonRoads[i]["geometry"]["coordinates"][0];
                //
                //                for (int j=0; j<_jsonRoad.size(); j++) {
                //
                //                    ofxJSONElement _coordinateRoad;
                //                    _coordinateRoad = _jsonRoad[j];
                //
                //                    ofVec2f _v;
                //                    _v.x = _jsonLoader_33975_22294.lon2x(_jsonRoad[j][0].asFloat()) - 740603;
                //                    _v.y = _jsonLoader_33975_22294.lat2y(_jsonRoad[j][1].asFloat()) - 6.40447e+06;
                //
                //                    _m.addVertex(_v);
                //                    _m.addColor( ofColor(255) );
                //
                //                    _pl.addVertex(_v);
                //
                //                }
                //
                //                roads_33975_22294.push_back( _m );
                //                roadsPolyline_33975_22294.push_back( _pl );
                
            }
            
        }
        
    }
    
    
    
    _rootNode_33975_22294->setPosition(0, 0, 0);
    _rootNode_33975_22294->printPosition("");
    
    
    // camera = ofEasyCam();
    camera.setPosition(_rootNode_33975_22294->getGlobalPosition());
    camera.move(0, 0, 300);
    camera.setTarget(_rootNode_33975_22294->getGlobalPosition());
    
    mainLight = ofLight();
    mainLight.setPointLight();
    mainLight.setGlobalPosition(-100, 0, 500);
    mainLight.setDiffuseColor(ofColor(35, 35, 35));
    mainLight.setSpecularColor(ofColor(170, 170, 170));
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    auto pushed = in.keyPushed;
    auto holded = in.keyHolded;
    auto pulled = in.keyPulled;
    
    if( pushed[GLFW_KEY_LEFT_SHIFT] ) cam.movespeed = 7.0f;
    if( pulled[GLFW_KEY_LEFT_SHIFT] ) cam.movespeed = 1.0f;
    
    if( pushed[GLFW_MOUSE_BUTTON_LEFT] ) paint.push_back( ofPolyline() );
    if( holded[GLFW_MOUSE_BUTTON_LEFT] ) paint.back().addVertex( cam.getPosition() + (cam.getLookAtDir() * 50.0f) );
    
    if( pushed[GLFW_MOUSE_BUTTON_RIGHT] ) cam.toggleControl();

    
    roadMovingFactor_33975_22294 = roadMovingFactor_33975_22294 + 1;
    roadMoving_33975_22294 = sin( ofDegToRad(roadMovingFactor_33975_22294) ) * 0.5 + 0.5;
    
    
}


//--------------------------------------------------------------
void ofApp::draw(){
    
    //    ofEnableLighting();
    
    cam.begin();
    
    
    
    //    mainLight.enable();
    
    
    //    for (int i=0; i<buildingsPolyline_33975_22294.size(); i++) {
    //        buildingsPolyline_33975_22294[i].draw();
    //    }
    
    //    ofPushStyle();
    //    ofSetColor(255, 160);
    //
    //    for (int i=0; i<buildings_33975_22294.size(); i++) {
    //        vector<ofVec3f> & _v = buildings_33975_22294[i].getVertices();
    //        for (int j=0; j<_v.size(); j++) {
    //            ofDrawLine( _v[j] - ofVec3f(0, 0, 0), _v[j] + ofVec3f(0, 0, 100) );
    //        }
    //    }
    //    ofPopStyle();
    
    
    for (int i=0; i<roadsPolyline_33975_22294.size(); i++) {
        roadsPolyline_33975_22294[i].draw();
    }
    
    
    for (int i=0; i<roadsPolyline_33975_22294.size(); i++) {
        ofDrawCircle(roadsPolyline_33975_22294[i].getPointAtPercent( roadMoving_33975_22294 ) , 2);
    }
    
    
    
    ofPushStyle();
    ofSetColor(255, 180);
    for (int i=0; i<buildingsPolyline_33975_22294.size(); i++) {
        
        buildingsPolyline_33975_22294[i].draw();
        
//                ofBeginShape();
//                vector<ofVec3f>& vertices = buildingsPolyline_33975_22294[i].getVertices();
//                for(int j = 0; j < vertices.size(); j++) {
//                    ofVertex(vertices[j]);
//                }
//                ofEndShape();
//        
//                ofBeginShape();
//                vector<ofVec3f>& verticesUp = buildingsPolyline_33975_22294[i].getVertices();
//                for(int j = 0; j < verticesUp.size(); j++) {
//                    ofVec3f _v = verticesUp[j] + ofVec3f(0, 0, 100);
//                    ofVertex(_v);
//                }
//                ofEndShape();
        
    }
    ofPopStyle();
    
    
    
    //    mainLight.disable();
    
    cam.end();
    
    //    ofDisableLighting();
    
    

    
    ofDrawBitmapString("control : w, s, a, d, r, q, e, c, mouse", 10, 20);
    
    
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
