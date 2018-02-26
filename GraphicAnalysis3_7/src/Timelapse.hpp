#pragma once
#include "ofMain.h"
#include "Interaction.hpp"
#include <string>
using namespace std;


class Timelapse{

public:
    ofImage intervalshoot(int interval, ofVideoGrabber cam, int rx, int ry, int rw, int rh);
    ofImage ofImageROI(ofImage img, int rx, int ry, int rw, int rh);
    
    int min;
    int sec;
    int pmin = -10;
    int pmin2 = -10;
    
    int esec;
    int psec = -1;
    int n = 0;
    int cn = 409; //映画フレーム用連番。最初にしたいフレーム番号を書く。
    int n2 = 0;
    
    float wi = 0.1;
    float wh_on;
    
    //char fname_c[100] = ("/Users/hannasaito/Documents/of_v0.9.8_osx_release/apps/myApps/of_forphysarum/frames_c/c10250.png"); //テスト用
    char fname_c[100]; //最初の映画フレームファイル名
    char fname_p[100]; //粘菌画像ファイル名
    char fname_m[100]; //プロジェクター投影用画像ファイル名
    
    bool whiteback = false;
    bool shooted = true;
    bool midShooted = false; //プロジェクタ投影用画像を撮ったらtrue,img_iを保存したらfalse
    
    ofImage img_b;
    ofImage img_p;
    ofImage img_m;
    ofxCvColorImage cv_p;
    ofxCvColorImage cv_m;

};
