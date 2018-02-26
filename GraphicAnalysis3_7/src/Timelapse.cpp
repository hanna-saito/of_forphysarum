//  Tmelapse.cpp
//  Created by Hanna Saito on 2017/10/04.

#include "ofMain.h"
#include "Timelapse.hpp"
#include <time.h>

ofImage Timelapse::intervalshoot(int interval, ofVideoGrabber cam, int rx, int ry, int rw, int rh){
    cout<< "Timelapse:n = " << n << endl;
    time_t now = time(NULL);
    struct tm *pnow = localtime(&now);
    
    min = pnow->tm_min;
    sec = pnow->tm_sec;
    
    //xの倍数分0秒に一回webcam撮影＆保存
    //if(sec%5 == 0){ //テスト用
    if(min%interval == 0 && pmin != min ){
        if(sec == 0){
            cout << min << ':' << sec << " pmin = " << pmin << endl; //撮影時間アウトプット
            whiteback = true; //背景白有効
        }
        
        if(sec == 2){   //キャプチャ画像保存
            img_p.setFromPixels(cam.getPixels());
            cv_p.allocate(img_p.getWidth(), img_p.getHeight());
            cv_p.setFromPixels(img_p.getPixels()); //ofImage → ofxCvGrayscaleImage
            cv_p.setROI(rx, ry, rw, rh);
            img_p.setFromPixels(cv_p.getRoiPixels() );
            shooted = true;
            cout << "n = " << n << endl;
            sprintf(fname_p, "/Users/hannasaito/Documents/of_v0.9.8_osx_release/apps/myApps/of_forphysarum/frames_p/p%05d.png", n);
            img_p.save(fname_p);
            cout << fname_p <<  " Saved!\n";
            cout << "whiteback = " << whiteback << endl;
            whiteback = false;
            sprintf(fname_c, "/Users/hannasaito/Documents/of_v0.9.8_osx_release/apps/myApps/of_forphysarum/frames_c/c%05d.png", n+cn);
            cout << fname_c << endl; //ファイルパスを出力
            
            //連番画像ファイル名更新
            n++;
            pmin = pnow->tm_min;
        }
    }
    
    //プロジェクター投影用画像撮影
    if(min%interval == 0 && sec == 30 && pmin2 != min){
        img_m.setFromPixels(cam.getPixels());
        cv_m.allocate(img_m.getWidth(), img_m.getHeight());
        cv_m.setFromPixels(img_m.getPixels()); //ofImage → ofxCvColorImage
        cv_m.setROI(rx, ry, rw, rh);
        img_m.setFromPixels(cv_m.getRoiPixels() );
        sprintf(fname_m, "/Users/hannasaito/Documents/of_v0.9.8_osx_release/apps/myApps/of_forphysarum/frames_m/m%05d.png", n-1);
        img_m.save(fname_m);
        midShooted = true;
        n2++; //連番画像ファイル名更新
        pmin2 = min;
    }
    
    return img_p;
}
