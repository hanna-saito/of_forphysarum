#pragma once

#include "ofMain.h"
#include "Timelapse.hpp"
#include "ofxGui.h"

class vidApp: public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void keyPressed(int key);
    void keyReleased(int key);
    
    const int maccam_w = 848;
    const int maccam_h = 480; //16:9
    
    const int webcam_w = 1920;
    const int webcam_h = 1080; //16:9
    
    int rx = 100;
    int ry = 20;
    int rw = 600;
    int rh = rw/4*3;
    
    char fname_test[100];
    char fname_b_sample[100];
    
    ofVideoGrabber cam;
    ofImage img_p;
    ofImage img_p_sample;
    ofImage img_b_sample;
    
    ofxCvColorImage cv_p;
    ofxCvGrayscaleImage cv_b;
    
    ofxIntSlider th;
    ofxPanel gui;
    
    Timelapse tl;
    
    ofFile fl2;
    
    bool wh;
    
};

