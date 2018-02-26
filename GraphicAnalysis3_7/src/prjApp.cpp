//
//  prjApp.cpp
//  GraphicAnalysis3
//
//  Created by Hanna Saito on 2017/10/29.
//

#include "prjApp.h"

void prjApp::setup(){
    ofSetFrameRate(fps);
    ofSetBackgroundColor(0);
    
}

//--------------------------------------------------------------

void prjApp::update(){
    cout << " fn = " << fn << endl;
    sprintf(fname, "/Users/hannasaito/Documents/of_v0.9.8_osx_release/apps/myApps/of_forphysarum/frames_m/m%05d.png", fn);
    
    if(fl1.doesFileExist(fname) == true){
        invertedFrame.load(fname);
    }
    
    else{
        isBlackframe = true;
        fn = 0;
        sprintf(fname, "/Users/hannasaito/Documents/of_v0.9.8_osx_release/apps/myApps/of_forphysarum/frames_m/m%05d.png", fn);
        invertedFrame.load(fname);
    }
    
    
    invertedFrame.resize(ofGetWidth(),ofGetHeight());
    invertedFrame.mirror(true, true);
}

//--------------------------------------------------------------

void prjApp::draw(){
    cout <<  "isBlackframe = " << isBlackframe << endl;
    
    if(isBlackframe == true){
        bn--;
        cout << "bn = " << bn << endl;
        
        if(bn == 0){
            isBlackframe = false;
            bn = 40;
        }
    }
    else{
        invertedFrame.draw(0,0);
        fn++;
    }
    
}

