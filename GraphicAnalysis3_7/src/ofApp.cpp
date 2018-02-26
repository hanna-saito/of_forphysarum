//iPad画面表示用app
#include "ofApp.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>


using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(255);
    //一枚目のフレームをロード
    sprintf(vid->tl.fname_c, "/Users/hannasaito/Documents/of_v0.9.8_osx_release/apps/myApps/of_forphysarum/frames_c/c%05d.png", vid->tl.cn+vid->tl.n);
    cout << "ofApp:vid->tl.fname_c = " << vid->tl.fname_c << endl;
    img_c.load(vid->tl.fname_c);
    
    //粘菌写真ロード
    sprintf(vid->tl.fname_p, "/Users/hannasaito/Documents/of_v0.9.8_osx_release/apps/myApps/of_forphysarum/frames_p/p%05d.png", vid->tl.n-1);
    cout << "ofApp:vid->tl.fname_c = " << vid->tl.fname_c << endl;
    vid->img_p.load(vid->tl.fname_p);
    //img_b = vid->img_p; //何がしたいのか不明。→これを書くと赤いフレームのエラーが起きる。思い出した。粘菌2値化画像サンプル表示のための初期値でした。
    
    //最初のiPad画面描画・最初の起動時は単なる映画フレーム、2回目以降起動時は編集済みフレーム
    //粘菌画像が一枚も保存されていないなら
    if(vid->tl.n == 0){
    img_c.draw(0,0);
    }
    //粘菌画像が保存されているなら、最後のファイル番号と同じ番号の編集済みフレームを描画
    else{
        sprintf(fname_i, "/Users/hannasaito/Documents/of_v0.9.8_osx_release/apps/myApps/of_forphysarum/frames_i/i%05d.png", vid->tl.n-1);
        img_i_loaded.load(fname_i);
        img_i_loaded.draw(0,0);
    }
}
//--------------------------------------------------------------
void ofApp::update(){
    img_c.load(vid->tl.fname_c);
    itr.imgSetup(vid->img_p, img_c);

    if(vid->tl.shooted == true){
        //新しいラベル作成
        cout << vid->tl.shooted  << endl;
        img_b = itr.makeLabel(vid->th);
        vid->img_b_sample = img_b;
        
        //画像保存　これで気付いたけど、白のとき一瞬映るのは閾値画像。
        //RGBにグレースケールマップしてるから赤くなってる。
        //なので、どこかで不必要に閾値画像の描写コードが入ってるはず　by sw
        sprintf(fname_b, "/Users/hannasaito/Documents/of_v0.9.8_osx_release/apps/myApps/of_forphysarum/frames_b/b%05d.png", vid->tl.n);
        img_b.save(fname_b);
        cout << "Makelabeled!" << endl;
        vid->tl.shooted = false;
        labelismade = true;
        //cout << vid->tl.shooted  << endl;
    }
    
    invertedImg = itr.videoInvert();
    itr.imgConvert(img_c, pileNum);
    
    //編集済みイメージ保存
    if(vid->tl.midShooted == true){
        sprintf(fname_i, "/Users/hannasaito/Documents/of_v0.9.8_osx_release/apps/myApps/of_forphysarum/frames_i/i%05d.png", vid->tl.n-1);
        invertedImg.save(fname_i);
        cout<< fname_i << "is saved." << endl;
        vid->tl.midShooted = false;
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    invertedImg.resize(ofGetWidth(), ofGetHeight());
    invertedImg.draw(0,0); //編集済みフレーム描画
    //img_c.draw(0,0); //単なる映画フレーム描画
    
    //vid->img_p.resize(ofGetWidth(), ofGetHeight());
    //vid->img_p.draw(0,0); //img_p確認
    
    //インターバル撮影時のみ白フレームを描画
    if(vid->wh == true){
        //ofSetColor(255);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
        cout << "whiteback on" << endl;
     }
 }
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
