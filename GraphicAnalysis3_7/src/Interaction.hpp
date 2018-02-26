//  Interaction.hpp
//
//  Created by Hanna Saito on 2017/10/08.
#pragma once
#include <stdio.h>
#include <iostream>
#include <math.h>
#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"

class Interaction{
    
public:
    void imgSetup(ofImage img_p, ofImage img_c);
    ofImage makeLabel(int th);
    ofImage videoInvert();
    ofImage imgConvert(ofImage img_c, int pileNum);
    ofImage imgCombine(ofImage img_c);
    
    ofImage img_b;
    ofImage img_i;
    ofImage img_im;
    ofImage img_ci;

    ofxCvGrayscaleImage gray1;
    
    unsigned char* pix_p;
    unsigned char* pix_c;
    unsigned char* pix_b;
    unsigned char* pix_i;
    unsigned char* pix_im;
    unsigned char* pix_c1;
    unsigned char* pix_c2;
    unsigned char* pix_ci;
    
    /*-------------------imgConvert用--------------------------------*/
    char fname_im[150] = "/Users/hannasaito/Library/Mobile\\Documents/com\\~apple\\~CloudDocs/Documents/of_v0.9.8_osx_release/apps/myApps/of_forphysarum/frames_im/im00000";
    
    int im_n = 0; //ファイルナンバー

    /*---------------------------------------------------------------*/
    
    int w = 480;
    int h = 360;
    
    int total_R = 0;
    int total_G = 0;
    int total_B = 0;
    
    int average_R = 0;
    int average_G = 0;
    int average_B = 0;
    
    int bnum = 0;
    int bnum2 = 0;
    
    int self_frag = 0;
    int upper_frag = 0;
    int under_frag = 0;
    int right_frag = 0;
    int left_frag = 0;
    
    int self_R = 0;
    int upper_R = 0;
    int under_R = 0;
    int right_R = 0;
    int left_R = 0;
    int upright_R = 0;
    int unright_R = 0;
    int upleft_R = 0;
    int unleft_R = 0;
    
    int self_G = 0;
    int upper_G = 0;
    int under_G = 0;
    int right_G = 0;
    int left_G = 0;
    int upright_G = 0;
    int unright_G = 0;
    int upleft_G = 0;
    int unleft_G = 0;
    
    int self_B = 0;
    int upper_B = 0;
    int under_B = 0;
    int right_B = 0;
    int left_B = 0;
    int upright_B = 0;
    int unright_B = 0;
    int upleft_B = 0;
    int unleft_B = 0;
    
    int self_distance;
    int upper_distance;
    int under_distance;
    int right_distance;
    int left_distance;
    
    int mySelf; //定常状態になったか判定用
    
};

