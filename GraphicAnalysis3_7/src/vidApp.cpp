/*
 * vidApp.cpp
 *
 *  Created on: Oct 28, 2014
 *      Author: arturo
 */

#include "vidApp.h"

void vidApp::setup(){
	ofBackground(0);
    //ofSetFrameRate(30);
    
    //camsetup
    cam.setDeviceID(0);
    cam.setDesiredFrameRate(15);
    cam.initGrabber(maccam_w, maccam_h);
    
    //guisetup
    gui.setup();
    gui.add(th.setup("threshold", 200, 0, 255));
    
    cv_b.allocate(320, 240);
    
    //粘菌画像ファイル番号MAXを調べる
    do {
        tl.n++;
        sprintf(fname_test, "/Users/hannasaito/Documents/of_v0.9.8_osx_release/apps/myApps/of_forphysarum/frames_p/p%05d.png", tl.n);
        fl2.doesFileExist(fname_test);
        //cout << tl.n << endl;
     } while (fl2.doesFileExist(fname_test) == true);
    
    //cout << "tl.fname_p = "  << tl.fname_p << endl;
    //cout << "tl.fname_c = "  << tl.fname_c << endl;
}

//--------------------------------------------------------------

void vidApp::update(){
    cam.update();
    img_p = tl.intervalshoot(10, cam, rx, ry, rw, rh); //粘菌写真アップデート
    wh = tl.whiteback;
    rh = rw/4*3;
    
    //サンプルイメージ
    img_p_sample = img_p;
    img_p_sample.resize(320, 240);
    img_p_sample.setImageType(OF_IMAGE_GRAYSCALE);
    cv_b.setFromPixels(img_p_sample);
    cv_b.threshold(th);
    
}

//--------------------------------------------------------------
void vidApp::draw(){
    ofSetColor(255,255,255);
    cam.draw(0,0); //ビデオフレームを描画
    img_p_sample.draw(0,maccam_h);
    cv_b.draw(325,maccam_h);
    gui.draw();
    
    ofSetColor(255,30,100);
    ofNoFill();
    ofDrawRectangle(rx, ry, rw, rh);
}

//--------------------------------------------------------------
void vidApp::mouseDragged(int x, int y, int button){
    rw = x;
}

//--------------------------------------------------------------
void vidApp::mousePressed(int x, int y, int button){
    rx = x;
    ry = y;

}

//--------------------------------------------------------------
void vidApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void vidApp::keyPressed(int key){
    if (key == OF_KEY_UP){
        ry--;
    }
    else if (key == OF_KEY_DOWN){
        ry++; 
    }
    else if (key == OF_KEY_LEFT){
        rx--; 
    }
    else if (key == OF_KEY_RIGHT){
        rx++; 
    }
    else if (key == '+'){
        rw++;
    }
    else if (key == '-'){
        rw--;
    }
    
}

//--------------------------------------------------------------
void vidApp::keyReleased(int key){
    
}

