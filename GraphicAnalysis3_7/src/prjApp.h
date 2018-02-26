//
//  prjApp.hpp
//  GraphicAnalysis3
//
//  Created by Hanna Saito on 2017/10/29.

#pragma once

#include "ofMain.h"
#include <stdio.h>

class prjApp : public ofBaseApp{
    
    public:
        void setup();
        void update();
        void draw();
    
        char fname[100] = ("/Users/hannasaito/Documents/of_v0.9.8_osx_release/apps/myApps/of_forphysarum/frames_m/m00000.png");
        char fname2[100] = ("/Users/hannasaito/Documents/of_v0.9.8_osx_release/apps/myApps/of_forphysarum/frames_m/i00000.png");
    
        ofImage invertedFrame;
        ofImage invertedFrame2;
    
        ofFile fl1;
    
        const int fps = 8; //フレームレート
        const int bn_d = fps*5; //ブラックアウト秒数
    
        int fn = 0;
        int bn = bn_d;
    
    
        bool isBlackframe = false;
        bool isFrame_m = true;
        bool isFrame_i = false;

};
