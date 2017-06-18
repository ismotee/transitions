#pragma once
#include "variPiirto.h"
#include "Viiva.h"
#include "ofMain.h"

struct poly {
    bool draw;
    ofPoint ul, dl, ur, dr;
    ofColor color;


    std::string print() {
        return ofToString(ul) + " : " + ofToString(dl) + " : " + ofToString(ur) + " : " + ofToString(dr) + " : ";
    }

};

class piirtopiirto : public Viiva {
public:
    int timer;
    float paksuus;
    std::vector<poly> polyViiva;
    bool alaPiirraSeuraavaa;

    ofColor currentColor, startColor, aimColor;
    float currentHue;
    float aimX, aimY, aimZ;
    ofVec3f suunta;
    float lampo;
    float speed;


    bool showData;


    void setup();
    void update();
    void draw();

    void pressed(int x, int y);

    void vaihdaVari();
    void tarkistaVari();



private:

};

