#include "variPiirto.h"

void variPiirto::setup() {

    ofBackground(ofColor::white);

    speed = 0.5;
}

void variPiirto::update() {
    if (mouseState.z) {
        if (pLine.size() != 0) {
            if (pLine[pLine.size() - 1] != mouseState) {


                pLine.addVertex(mouseState);
                //pLine.simplify(0.1);
                //pisteet.push_back(mouseState);

                //pisteiden keskiarvo


                nopeus = 0;

                if (pLine.size() > 1) {
                    int maara = 0;
                    std::vector<float> nopeudet;
                    for (int i = pLine.size() - 1; i > 0 && maara < 100; i--) {
                        ofVec3f vec = pLine[i] - pLine[i - 1];
                        nopeudet.push_back(vec.lengthSquared());
                        nopeus += nopeudet.back();
                        maara++;
                    }
                    if (maara)
                        nopeus /= maara;
                    
                    nopeudenKeskihajonta = 0;
                    
                    for(int i = 0; i < nopeudet.size();i++) {
                        nopeudenKeskihajonta = pow(nopeudet[i]-nopeus,2);
                    }
                    
                    nopeudenKeskihajonta = sqrt(1/maara + nopeudenKeskihajonta);
                    

                    nopeus *= 0.03;
                }


                paino = laskeKeskiarvo();

                reviiri.paikka = paino - pLine.getBoundingBox().getCenter();
                reviiri.koko = reviiri.paikka.length();

                if (pLine.size() > 2) {
                    kulmat.push_back(pLine.getNormalAtIndex(pLine.size() - 2));
                }

                // kulmien mediaani
                if (!kulmat.empty()) {
                    yleinenKulma = ofVec2f::zero();
                    int maara = 0;
                    for (int i = kulmat.size() - 1; i >= 0 && maara < 50; i--) {
                        if (kulmat[i].length() > 0.1) {
                            yleinenKulma += kulmat[i] * kulmat[i].length()*0.1;
                            maara++;
                        }
                        //cout << "KulmaLength: " << ofToString(pLine.getLengthAtIndex(pLine.size()-1)) << "\n";
                    }
                    //yleinenKulma.normalize();
                    yleinenKulma.rotate(90);
                }

            } else {
                nopeus -=1;
            }

        } else {
          pLine.addVertex(mouseState);
        }
    }
}

void variPiirto::draw() {
}

void variPiirto::pressed(int x, int y) {
    setMouse(x, y, 1);
    pLine.clear();
    kulmat.clear();
}

void variPiirto::moved(int x, int y) {
    setMouse(x, y);
}

void variPiirto::released(int x, int y) {
    setMouse(x, y, 0);


}

void variPiirto::setMouse(int x, int y, int button) {
    if (button == -1)
        button = mouseState.z;
    mouseState = ofPoint(x, y, button);
}


ofPoint variPiirto::laskeKeskiarvo() {
    ofPoint ka;

    for (int i = 0; i < pLine.size(); i++) {
        ka.x += pLine[i].x;
        ka.y += pLine[i].y;
    }

    ka.y /= pLine.size();
    ka.x /= pLine.size();
    return ka;
}