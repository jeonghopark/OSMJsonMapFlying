#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
    
    
    ofGLFWWindowSettings settings;
    
    settings.setSize(1280, 720);
    settings.resizable = true;
    settings.setPosition( ofVec2f(0, 0 ));
    //    settings.windowMode = OF_FULLSCREEN;
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
    
    shared_ptr<ofApp> mainApp(new ofApp);
    
    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();
    
    
}
