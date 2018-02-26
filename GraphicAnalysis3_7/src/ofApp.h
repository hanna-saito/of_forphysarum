#pragma once
#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"
#include "Timelapse.hpp"
#include "vidApp.h"
#include "Interaction.hpp"

#include <string>
using namespace std;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        int w = 320;
        int h = 240;
    
        int pn = -1;
    
        int rx = 100;
        int ry = 100;
    
        int pileNum = 100; //画像の変化した部分を重ねる枚数・Convert()引数用
    
        //int th = 155; //粘菌画像二値化スレッショルド
    
        bool labelismade = false;
    
        Interaction itr;
    
        ofTexture invertedTexture;
        ofxCvGrayscaleImage testimg;
        ofImage invertedImg;
    
        ofImage img_c;
        ofImage img_c2; //編集後部分を重ねた画像
        ofImage img_b;
        ofImage img_i_loaded;
    
    
    
        char fname_i[100];
        char fname_b[100];
        shared_ptr<vidApp> vid;
};
