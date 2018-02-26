#include "ofMain.h"
#include "ofApp.h"
#include "vidApp.h"
#include "prjApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
    ofGLFWWindowSettings settings;
    
    //iPadサイズのウィンドウ
    //settings.width = 2048;
    //settings.height = 1536;
    settings.width = 512;
    settings.height = 384;
    //settings.width = 5;
    //settings.height = 3;
    settings.setPosition(ofVec2f(0,0));
    settings.resizable = true;
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
    
    //webcamサイズのウィンドウ
    //settings.width = 1920;
    //settings.height = 1080;
    settings.width = 848;
    settings.height = 480+240;
    settings.setPosition(ofVec2f(384,0));
    settings.resizable = false;
    shared_ptr<ofAppBaseWindow> vidWindow = ofCreateWindow(settings);
    
    //プロジェクター用ウィンドウ
    //settings.width = 1920;
    //settings.height = 1080;
    settings.width = 320;
    settings.height = 240;
    settings.setPosition(ofVec2f(384,0));
    settings.resizable = true;
    shared_ptr<ofAppBaseWindow> prjctrWindow = ofCreateWindow(settings);
    
    shared_ptr<ofApp> mainApp(new ofApp);
    shared_ptr<vidApp> subApp(new vidApp);
    shared_ptr<prjApp> sub2App(new prjApp);
    mainApp->vid = subApp;
    ofRunApp(vidWindow, subApp);
    ofRunApp(mainWindow, mainApp);
    ofRunApp(prjctrWindow, sub2App);
    ofRunMainLoop();
}
