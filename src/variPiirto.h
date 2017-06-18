#pragma once

#include "ofMain.h"


struct Reviiri {

    float koko;
    ofPoint paikka;
    Reviiri():koko(-1){}
};

class variPiirto {
public:

    ofPolyline pLine;
    std::vector<ofVec2f> kulmat;
    double nopeus;
    float nopeudenKeskihajonta;
    ofPoint paino;
    ofVec2f yleinenKulma;
    float speed;
    
    
    Reviiri reviiri;

    virtual void setup();
    virtual void update();
    virtual void draw();

    void pressed(int x, int y);
    void moved(int x, int y);
    void released(int x, int y);

    ofColor ofRandomColor() {
        return ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
    }
    ofVec3f colHsv2vec3(const ofColor col) {
        return ofVec3f(col.getHue(),col.getSaturation(),col.getBrightness());
    }
    ofColor vec32colHsv(const ofVec3f vec) {
        ofColor col(255,255,255);
        col.setSaturation(vec.y);
        col.setBrightness(vec.z);
        col.setHueAngle(vec.x);
        return col;
    }

    
protected:
    ofPoint mouseState;
    void setMouse(int x, int y, int button = -1);
    ofPoint laskeKeskiarvo();
};
