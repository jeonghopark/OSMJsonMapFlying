#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
    
    
    ofGLFWWindowSettings settings;
    
    settings.width = 1280;  // 1920
    settings.height = 720;  // 1080
    settings.resizable = true;
    settings.setPosition( ofVec2f(settings.width, 0 ));
    //    settings.windowMode = OF_FULLSCREEN;
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
    
    shared_ptr<ofApp> mainApp(new ofApp);
    
    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();
    
    
}
