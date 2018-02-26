//  Interaction.cpp 
//
//  Created by Hanna Saito on 2017/10/08.

#include "Interaction.hpp"

void Interaction::imgSetup(ofImage img_p, ofImage img_c){
    img_p.resize(w,h);
    img_c.resize(w,h);
    
    img_p.setImageType(OF_IMAGE_GRAYSCALE);
    img_c.setImageType(OF_IMAGE_COLOR);
    
    img_p.mirror(true, true); //カメラの位置によっては反転
    
    //粘菌画像と映画フレームのピクセルを配列に格納
    pix_p = img_p.getPixels().getData();
    pix_c = img_c.getPixels().getData();
}

//---------------------------------------------------------------------------------------------------------------------------------------------
ofImage Interaction::makeLabel(int th){
    gray1.allocate(w, h);
    img_b.setFromPixels(pix_p, w, h, OF_IMAGE_GRAYSCALE); //二値画像反転済み表示用に配列→ofImage
    
    gray1.setFromPixels(img_b.getPixels()); //ofImage → ofxCvGrayscaleImage
    
    gray1.blur();
    gray1.blur();
    gray1.threshold(th);
    
    //二値画像輪郭拡張
    for(int i = 0; i<1; i++){
        gray1.erode();
    }
    
    
    img_b.setFromPixels(gray1.getPixels()); //ofxCvGrayscaleImage → ofImage
    
    //sprintf(fname_m, "/Users/hannasaito/Documents/of_v0.9.8_osx_release/apps/myApps/of_forphysarum/frames_b/b%05d.png", n2);
    //img_b.save(fname_m);
    
    img_b.setImageType(OF_IMAGE_COLOR); //グレースケール → RGB （RGB画像と配列長を同じにするため）
    pix_b = img_b.getPixels().getData(); //二値化ofImage → 配列
    

    //RGB画像の選択部分のRGBそれぞれの合計値取得
    for(int y = 0; y < h; y++){
        for(int x = 0; x < w; x++){
            if(pix_b[y*3*w + x*3]==0){
                //黒pixel計上
                bnum++;
                //赤計上
                total_R += pix_c[y*3*w + x*3];
                
                //緑計上
                total_G += pix_c[y*3*w + x*3+1];
                
                //青計上
                total_B += pix_c[y*3*w + x*3+2];
                
            }
        }
    }
    
    //RGB平均計算
    if(bnum > 0){
        average_R = total_R/bnum;
        average_G = total_G/bnum;
        average_B = total_B/bnum;
    }
    
    /*cout << "bnum = " << bnum << endl;
     
     cout << "total_R = " << total_R << endl;
     cout << "total_G = " << total_G << endl;
     cout << "total_B = " << total_B << endl;
     
     cout << "average_R = " << average_R << endl;
     cout << "average_G = " << average_G << endl;
     cout << "average_B = " << average_B << endl;*/
    
    
    
    //二値化、拡張した画像を内〜外領域に分け、色分けして結果を確認
    
    int ln = 254; //仮
    
    //二値画像を配列長を合わせるためにRGBにしてあるだけなので見るピクセルは赤のみ
    do{
        bnum2 = 0; //未ラベリング黒ピクセル数リセット
        for(int y = 0; y < h; y++){
            for(int x = 0; x < w; x++){
                if(pix_b[y*3*w + x*3]==0){ //ピクセルが黒の場合
                    //私が画面の端でない場合
                    if(x>0 && x<w-1 && y>0 && y<h-1){
                        if(!(pix_b[(y-1)*3*w + x*3]<=ln&&pix_b[(y+1)*3*w + x*3]<=ln&&pix_b[y*3*w + (x-1)*3]<=ln&&pix_b[y*3*w + (x+1)*3]<=ln)){ //上下左右のピクセルのすべてがln以下（lnか黒）でないならば
                            pix_b[y*3*w + x*3] = ln; //内〜外分類のラベル代入
                        }
                        else{
                            bnum2++; //このループの未ラベリング黒ピクセル計上
                        }
                    }
                    //私が画面の上端の場合
                    if(x>0 && x<w-1 && y==0){
                        if(!(pix_b[(y+1)*3*w + x*3]<=ln&&pix_b[y*3*w + (x-1)*3]<=ln&&pix_b[y*3*w + (x+1)*3]<=ln)){ //上下左右のピクセルのすべてがln以下（lnか黒）でないならば
                            pix_b[y*3*w + x*3] = ln; //内〜外分類のラベル代入
                        }
                        else{
                            bnum2++; //このループの未ラベリング黒ピクセル計上
                        }
                    }
                    //私が画面の下端の場合
                    else if(x>0 && x<w-1 && y==h-1){
                        if(!(pix_b[(y-1)*3*w + x*3]<=ln&&pix_b[y*3*w + (x-1)*3]<=ln&&pix_b[y*3*w + (x+1)*3]<=ln)){ //上下左右のピクセルのすべてがln以下（lnか黒）でないならば
                            pix_b[y*3*w + x*3] = ln; //内〜外分類のラベル代入
                        }
                        else{
                            bnum2++; //このループの未ラベリング黒ピクセル計上
                        }
                    }
                    //私が画面左端の場合
                    else if(x == 0 && y>0 && y<h-1){
                        if(!(pix_b[(y-1)*3*w + x*3]<=ln&&pix_b[(y+1)*3*w + x*3]<=ln&&pix_b[y*3*w + (x+1)*3]<=ln)){ //上下右のピクセルのすべてがln以下（lnか黒）でないならば(Thread 1: EXC_BAD_ACCESS (code=1, address=0x10d7f0000)原因不明)
                            pix_b[y*3*w + x*3] = ln; //内〜外分類のラベル代入
                        }
                        else{
                            bnum2++; //このループの未ラベリング黒ピクセル計上
                        }
                    }
                    //私が画面右端の場合
                    else if(x==w-1 && y>0 && y<h-1){
                        if(!(pix_b[(y-1)*3*w + x*3]<=ln&&pix_b[(y+1)*3*w + x*3]<=ln&&pix_b[y*3*w + (x+1)*3]<=ln)){ //上下左のピクセルのすべてがln以下（lnか黒）でないならば
                            pix_b[y*3*w + x*3] = ln; //内〜外分類のラベル代入
                        }
                        else{
                            bnum2++; //このループの未ラベリング黒ピクセル計上
                        }
                    }
                    //私が画面右上端の場合
                    else if(x==w-1 && y==0){
                        if(!(pix_b[(y+1)*3*w + x*3]<=ln&&pix_b[y*3*w + (x-1)*3]<=ln)){ //下左のピクセルのすべてがln以下（lnか黒）でないならば
                            pix_b[y*3*w + x*3] = ln; //内〜外分類のラベル代入
                        }
                        else{
                            bnum2++; //このループの未ラベリング黒ピクセル計上
                        }
                    }
                    
                    //私が画面左上端の場合
                    else if(x==0 && y==0){
                        if(!(pix_b[(y+1)*3*w + x*3]<=ln&&pix_b[y*3*w + (x+1)*3]<=ln)){ //下右のピクセルのすべてがln以下（lnか黒）でないならば
                            pix_b[y*3*w + x*3] = ln; //内〜外分類のラベル代入
                        }
                        else{
                            bnum2++; //このループの未ラベリング黒ピクセル計上
                        }
                    }
                    
                    //私が画面右下端の場合
                    else if(x==w-1 && y==h-1){
                        if(!(pix_b[(y-1)*3*w + x*3]<=ln&&pix_b[y*3*w + (x-1)*3]<=ln)){ //上左のピクセルのすべてがln以下（lnか黒）でないならば
                            pix_b[y*3*w + x*3] = ln; //内〜外分類のラベル代入
                        }
                        else{
                            bnum2++; //このループの未ラベリング黒ピクセル計上
                        }
                    }
                    
                    //私が画面左下端の場合
                    else if(x==0 && y==h-1){
                        if(!(pix_b[y*3*w + (x+1)*3]<=ln)&&(pix_b[(y-1)*3*w + x*3]<=ln)){ //上右のピクセルのすべてがln以下（lnか黒）でないならば
                            pix_b[y*3*w + x*3] = ln; //内〜外分類のラベル代入
                        }
                        else{
                            bnum2++; //このループの未ラベリング黒ピクセル計上
                        }
                    }
                }
            }
        }
        //cout << "ln = " << ln << endl;
        //cout << "bnum2 = " << bnum2 << endl; //未ラベリング黒ピクセルの数出力
        ln = ln-1; //ラベル更新
        if(ln<0){break;} //ラベルが０以下になった場合はループを抜ける
    }while(!(bnum2==0)); //未ラベリングの黒ピクセルが残っている限りfor文を繰り返す

    return img_b;
    //cout << "ln = " << ln+1 << endl; //とりあえずラベルの種類数を出力

}

//----------------------------------------------------------------------------------------------------------------------------------------------------------

ofImage Interaction::videoInvert(){
    //videoinvert
    for(int y = 0; y < h; y++){
        for(int x = 0; x < w; x++){
            self_frag = pix_b[y*3*w + x*3];
            self_R = pix_c[y*3*w + x*3]; self_G = pix_c[y*3*w + x*3+1]; self_B = pix_c[y*3*w + x*3+2];
            self_distance = pow((average_R - self_R),2)+pow((average_G - self_G),2)+pow((average_B - self_B),2);
            
            //私が粘菌領域内なら
            if(self_frag < 255){
                
                //私が画像の上端のピクセルでないなら
                if(y > 0){
                    upper_frag = pix_b[(y-1)*3*w + x*3]; upper_R = pix_c[(y-1)*3*w + x*3];
                    upper_R = pix_c[(y-1)*3*w + x*3]; upper_G = pix_c[(y-1)*3*w + x*3+1]; upper_B = pix_c[(y-1)*3*w + x*3+2];
                    upper_distance = pow((average_R - upper_R),2)+pow((average_G - upper_G),2)+pow((average_B - upper_B),2);
                    //上ピクセルが私より外側かつ私より上ピクセルが平均に近いまたは上ピクセルが私より内側かつ上ピクセルより私が平均に近ければ
                    if((self_frag < upper_frag && self_distance > upper_distance)||
                       (self_frag > upper_frag && self_distance < upper_distance)){
                        //私と入れ替える
                        pix_c[(y-1)*3*w + x*3] = self_R; pix_c[(y-1)*3*w + x*3+1] = self_G; pix_c[(y-1)*3*w + x*3+2] = self_B; //上ピクセルに私を代入
                        pix_c[y*3*w + x*3] = upper_R; pix_c[y*3*w + x*3+1] = upper_G; pix_c[y*3*w + x*3+2] = upper_B; //私に上ピクセルを代入
                    }
                }
                
                //私が画像の下端のピクセルでないなら
                if(y < h-1){
                    under_frag = pix_b[(y+1)*3*w + x*3];
                    under_R = pix_c[(y+1)*3*w + x*3]; under_G = pix_c[(y+1)*3*w + x*3+1]; under_B = pix_c[(y+1)*3*w + x*3+2];
                    under_distance = pow((average_R - under_R),2)+pow((average_G - under_G),2)+pow((average_B - under_B),2);
                    //下ピクセルが私より外側かつ私より下ピクセルが平均に近いまたは下ピクセルが私より内側かつ下ピクセルより私が平均に近ければ
                    if((self_frag < under_frag && self_distance > under_distance)||
                       (self_frag > under_frag && self_distance < under_distance)){
                        //私と入れ替える
                        pix_c[(y+1)*3*w + x*3] = self_R; pix_c[(y+1)*3*w + x*3+1] = self_G; pix_c[(y+1)*3*w + x*3+2] = self_B; //上ピクセルに私を代入
                        pix_c[y*3*w + x*3] = under_R; pix_c[y*3*w + x*3+1] = under_G; pix_c[y*3*w + x*3+2] = under_B; //私に上ピクセルを代入
                    }
                }
                
                //私が画像の左端のピクセルでないなら
                if(x > 0){
                    left_frag = pix_b[y*3*w + (x-1)*3];
                    left_R = pix_c[y*3*w + (x-1)*3]; left_G = pix_c[y*3*w + (x-1)*3+1]; left_B = pix_c[y*3*w + (x-1)*3+2];
                    left_distance = pow((average_R - left_R),2)+pow((average_G - left_G),2)+pow((average_B - left_B),2);
                    //左ピクセルが私より外側かつ私より左ピクセルが平均に近いまたは左ピクセルが私より内側かつ左ピクセルより私が平均に近ければ
                    if((self_frag < left_frag && self_distance > left_distance)||
                       (self_frag > left_frag && self_distance < left_distance)){
                        //私と入れ替える
                        pix_c[y*3*w + (x-1)*3] = self_R; pix_c[y*3*w + (x-1)*3+1] = self_G; pix_c[y*3*w + (x-1)*3+2] = self_B; //上ピクセルに私を代入
                        pix_c[y*3*w + x*3] = left_R; pix_c[y*3*w + x*3+1] = left_G; pix_c[y*3*w + x*3+2] = left_B; //私に上ピクセルを代入
                    }
                }
                
                //私が画像の右端のピクセルでないなら
                if(x < w-1){
                    right_frag = pix_b[y*3*w + (x+1)*3];
                    right_R = pix_c[y*3*w + (x+1)*3]; right_G = pix_c[y*3*w + (x+1)*3+1]; right_B = pix_c[y*3*w + (x+1)*3+2];
                    right_distance = pow((average_R - right_R),2)+pow((average_G - right_G),2)+pow((average_B - right_B),2);
                    //xが画像の幅未満かつ右ピクセルが私より外側かつ私より上ピクセルが平均に近いまたは右ピクセルが私より内側かつ上ピクセルより私が平均に近ければ
                    if((self_frag < right_frag && self_distance > right_distance)||
                       (self_frag > right_frag && self_distance < right_distance)){
                        //私と入れ替える
                        pix_c[y*3*w + (x+1)*3] = self_R; pix_c[y*3*w + (x+1)*3+1] = self_G; pix_c[y*3*w + (x+1)*3+2] = self_B; //上ピクセルに私を代入
                        pix_c[y*3*w + x*3] = right_R; pix_c[y*3*w + x*3+1] = right_G; pix_c[y*3*w + x*3+2] = right_B; //私に上ピクセルを代入
                    }
                }
                
                //私が画像の上端でも左端のピクセルでもないなら
                if(x > 0 && y > 0 ){
                    right_frag = pix_b[(y-1)*3*w + (x-1)*3];
                    right_R = pix_c[(y-1)*3*w + (x-1)*3]; right_G = pix_c[(y-1)*3*w + (x-1)*3+1]; right_B = pix_c[(y-1)*3*w + (x-1)*3+2];
                    right_distance = pow((average_R - right_R),2)+pow((average_G - right_G),2)+pow((average_B - right_B),2);
                    //xが画像の幅未満かつ左上ピクセルが私より外側かつ私より左上ピクセルが平均に近いまたは左上ピクセルが私より内側かつ左上ピクセルより私が平均に近ければ
                    if((self_frag < right_frag && self_distance > right_distance)||
                       (self_frag > right_frag && self_distance < right_distance)){
                        //私と入れ替える
                        pix_c[(y-1)*3*w + (x-1)*3] = self_R; pix_c[(y-1)*3*w + (x-1)*3+1] = self_G; pix_c[(y-1)*3*w + (x-1)*3+2] = self_B; //左上ピクセルに私を代入
                        pix_c[y*3*w + x*3] = right_R; pix_c[y*3*w + x*3+1] = right_G; pix_c[y*3*w + x*3+2] = right_B; //私に左上ピクセルを代入
                    }
                }
                
                //私が画像の上端でも右端のピクセルでもないなら
                if(x < w-1 && y > 0){
                    right_frag = pix_b[(y-1)*3*w + (x+1)*3];
                    right_R = pix_c[(y-1)*3*w + (x+1)*3]; right_G = pix_c[(y-1)*3*w + (x+1)*3+1]; right_B = pix_c[(y-1)*3*w + (x+1)*3+2];
                    right_distance = pow((average_R - right_R),2)+pow((average_G - right_G),2)+pow((average_B - right_B),2);
                    //xが画像の幅未満かつ右上ピクセルが私より外側かつ私より右上ピクセルが平均に近いまたは右上ピクセルが私より内側かつ右上ピクセルより私が平均に近ければ
                    if((self_frag < right_frag && self_distance > right_distance)||
                       (self_frag > right_frag && self_distance < right_distance)){
                        //私と入れ替える
                        pix_c[(y-1)*3*w + (x+1)*3] = self_R; pix_c[(y-1)*3*w + (x+1)*3+1] = self_G; pix_c[(y-1)*3*w + (x+1)*3+2] = self_B; //右上ピクセルに私を代入
                        pix_c[y*3*w + x*3] = right_R; pix_c[y*3*w + x*3+1] = right_G; pix_c[y*3*w + x*3+2] = right_B; //私に右上ピクセルを代入
                    }
                }
                
                //私が画像の下端でも左端のピクセルでもないなら
                if(x > 0 && y < h-1 ){
                    right_frag = pix_b[(y+1)*3*w + (x-1)*3];
                    right_R = pix_c[(y+1)*3*w + (x-1)*3]; right_G = pix_c[(y+1)*3*w + (x-1)*3+1]; right_B = pix_c[(y+1)*3*w + (x-1)*3+2];
                    right_distance = pow((average_R - right_R),2)+pow((average_G - right_G),2)+pow((average_B - right_B),2);
                    //xが画像の幅未満かつ左下ピクセルが私より外側かつ私より左下ピクセルが平均に近いまたは左下ピクセルが私より内側かつ左下ピクセルより私が平均に近ければ
                    if((self_frag < right_frag && self_distance > right_distance)||
                       (self_frag > right_frag && self_distance < right_distance)){
                        //私と入れ替える
                        pix_c[(y+1)*3*w + (x-1)*3] = self_R; pix_c[(y+1)*3*w + (x-1)*3+1] = self_G; pix_c[(y+1)*3*w + (x-1)*3+2] = self_B; //左下ピクセルに私を代入
                        pix_c[y*3*w + x*3] = right_R; pix_c[y*3*w + x*3+1] = right_G; pix_c[y*3*w + x*3+2] = right_B; //私に左下ピクセルを代入
                    }
                }
                
                //私が画像の下端でも右端のピクセルでもないなら
                if(x < w-1 && y < h-1 ){
                    right_frag = pix_b[(y+1)*3*w + (x+1)*3];
                    right_R = pix_c[(y+1)*3*w + (x+1)*3]; right_G = pix_c[(y+1)*3*w + (x+1)*3+1]; right_B = pix_c[(y+1)*3*w + (x+1)*3+2];
                    right_distance = pow((average_R - right_R),2)+pow((average_G - right_G),2)+pow((average_B - right_B),2);
                    //xが画像の幅未満かつ右下ピクセルが私より外側かつ私より右下ピクセルが平均に近いまたは右下ピクセルが私より内側かつ右下ピクセルより私が平均に近ければ
                    if((self_frag < right_frag && self_distance > right_distance)||
                       (self_frag > right_frag && self_distance < right_distance)){
                        //私と入れ替える
                        pix_c[(y+1)*3*w + (x+1)*3] = self_R; pix_c[(y+1)*3*w + (x+1)*3+1] = self_G; pix_c[(y+1)*3*w + (x+1)*3+2] = self_B; //右下ピクセルに私を代入
                        pix_c[y*3*w + x*3] = right_R; pix_c[y*3*w + x*3+1] = right_G; pix_c[y*3*w + x*3+2] = right_B; //私に右下ピクセルを代入
                    }
                }
            }
        }
    }
    img_i.setFromPixels(pix_c, w, h, OF_IMAGE_COLOR);

    return img_i;
}

//----------------------------------------------------------------------------------------------------------------------------------------------

ofImage Interaction::imgConvert(ofImage img_c, int pileNum){
    pix_c = img_c.getPixels().getData();
    pix_i = img_i.getPixels().getData();
    
    //img_cとimg_iのピクセルが同じ場合には青くする
    for(int y = 0; y < h; y++){
        for(int x = 0; x < w; x++){
            
            if(pix_c[y*3*w + x*3] == pix_i[y*3*w + x*3] && pix_c[y*3*w + x*3+1] == pix_i[y*3*w + x*3+1] && pix_c[y*3*w + x*3+2] == pix_i[y*3*w + x*3+2]){
                
                pix_i[y*3*w + x*3] = 0; //R
                pix_i[y*3*w + x*3+1] = 0; //G
                pix_i[y*3*w + x*3+2] = 255; //B
                
            }
        }
    }
    
    img_im.setFromPixels(pix_i, w, h, OF_IMAGE_COLOR);
    
    //重ねる枚数分だけ画像保存(後で引いていくため)
    if(im_n < pileNum){
        sprintf(fname_im, "/Users/hannasaito/Library/Mobile\\Documents/com\\~apple\\~CloudDocs/Documents/of_v0.9.8_osx_release/apps/myApps/of_forphysarum/frames_im/im%05d.png", im_n);
        img_im.save(fname_im);
        im_n++;
    }
    else{
        im_n == 0;
    }
    
    
    return img_im; //変化した部分以外が青の映画フレーム画像を返す
}

//----------------------------------------------------------------------------------------------------------------------------------------------

ofImage Interaction::imgCombine(ofImage img_c){
    pix_c = img_ci.getPixels().getData();
    pix_im = img_im.getPixels().getData();
    
    //img_imのピクセルが青の場合にはimg_cのピクセルを代入
    for(int y = 0; y < h; y++){
        for(int x = 0; x < w; x++){
            
            if(pix_im[y*3*w + x*3] == 0 && pix_im[y*3*w + x*3+1] == 0 && pix_im[y*3*w + x*3+2] == 255){
                
                pix_im[y*3*w + x*3] = pix_ci[y*3*w + x*3]; //R
                pix_im[y*3*w + x*3+1] = pix_ci[y*3*w + x*3+1]; //G
                pix_im[y*3*w + x*3+2] = pix_ci[y*3*w + x*3+2]; //B
                
            }
        }
    }
    
    img_ci.setFromPixels(pix_im, w, h, OF_IMAGE_COLOR);
    return img_ci;
}
    

