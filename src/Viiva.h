#pragma once

#include "ofMain.h"
#include "dClock.h"

enum ViivanMoodi {uusiViiva, piirtaa, viivaKesken,viivaValmis};



struct hiiri {
    ofPoint mouseState;
    bool click;
    void moved(int x,int y) {mouseState = ofPoint(x,y,mouseState.z);}
    void released(int x,int y){mouseState = ofPoint(x,y,0);}
    void pressed(int x, int y){mouseState = ofPoint(x,y,1);click = true;}
    
};

struct viivanOminaisuudet {
    float nopeudenKa;
    float nopeudenKh;
    float maksimiNopeus;
    float kulmanKa;
    float kulmanKh;
    float pintaala;
    
    void nollaa() {nopeudenKa = 0; nopeudenKh = 0; kulmanKa = 0; kulmanKh = 0;pintaala = 0;maksimiNopeus = 0;}
};

class Viiva {
public:
    ViivanMoodi moodi;
    hiiri mouse;
    int sample,tauko;
    bool viivaKasvoi;
    dClock viivaKello;
    
    
    ofPolyline pLine;
    std::vector<ofPoint> otanta;
    std::vector<float> nopeudet;
    viivanOminaisuudet kalibrointi;
    viivanOminaisuudet otannanOminaisuudet;
    viivanOminaisuudet verratut;
    
    void setup();
    void update();
    
    void valitseMoodi();
    void kalibroi();
    void tallennaViiva();
    void laskeOtannanOminaisuudet();
    void vertaa();
private:

};
