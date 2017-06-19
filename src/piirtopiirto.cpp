#include "piirtopiirto.h"

float bound(float val, float min, float max) {
    if (val > max)
        return max;
    else if (val < min)
        return min;
    return val;
}

void piirtopiirto::threadedFunction() {
    while (isThreadRunning()) {
        Viiva::update();
        // pLine.simplify(0.9);
        if (moodi == viivaValmis)
            polyViiva.clear();

        if (moodi == viivaKesken)
            alaPiirraSeuraavaa = 3;

        lampo = (mouse.mouseState.x / ofGetWidth() - 0.5) * 40;


        while (pLine.size() - 2 > polyViiva.size() && pLine.size() > 3) {
            // pisteet:  A   B   C
            // viivat:   AB  BC

            polyViiva.push_back(poly());

            if (polyViiva.size() == 1) {


                ofPoint fromToVec = pLine[0] - pLine[1];

                float angle = atan((pLine[0].y - pLine[1].y) / (pLine[0].x - pLine[1].x));
                ofPoint ul = pLine[0] + fromToVec.getRotated(angle + 90, ofVec3f(0, 0, 1));
                ofPoint dl = pLine[0] + fromToVec.getRotated(angle - 90, ofVec3f(0, 0, 1));
                ofPoint ur = ul + fromToVec;
                ofPoint dr = dl + fromToVec;
                ur = pLine[0] + ur.getNormalized();
                dr = pLine[0] + dr.getNormalized();

                polyViiva.back().ul = ul;
                polyViiva.back().dl = dl;
                polyViiva.back().ur = ur;
                polyViiva.back().dr = dr;
                polyViiva.back().color = currentColor;

                if (fromToVec.length() > 0.1)
                    polyViiva.back().draw = true;

            } else {
                int i = polyViiva.size();
                ofPoint fromToVec = pLine[i - 1] - pLine[i];
                ofPoint lastLine = pLine[i - 2] - pLine[i - 1];

                if (fromToVec.length() > 0.5) {

                    paksuus = bound(otannanOminaisuudet.nopeudenKa * 0.06, 1, 80);


                    float angle = atan((pLine[i - 1].y - pLine[i].y) / (pLine[i - 1].x - pLine[i].x));

                    ofPoint ur = fromToVec.getRotated(angle + 90, ofVec3f(0, 0, 1));
                    ofPoint dr = fromToVec.getRotated(angle - 90, ofVec3f(0, 0, 1));

                    ur = fromToVec + ur;
                    dr = fromToVec + dr;

                    ur = pLine[i - 1] + ur.getNormalized() * paksuus;
                    dr = pLine[i - 1] + dr.getNormalized() * paksuus;


                    polyViiva.back().ul = polyViiva[i - 2].ur;
                    polyViiva.back().dl = polyViiva[i - 2].dr;
                    polyViiva.back().ur = ur;
                    polyViiva.back().dr = dr;
                    polyViiva.back().color = currentColor;

                    if (alaPiirraSeuraavaa) {
                        alaPiirraSeuraavaa--;
                    } else
                        polyViiva.back().draw = true;

                } else {
                    polyViiva.back() = polyViiva[i - 2];
                }

            }

        }
        if (kello.get() > 0.005) {
            tarkistaVari();
            vaihdaVari();
            kello.reset();
        }

        //alaPiirraSeuraavaa = mouse.click;
        //mouse.click = false;

    }
}

void piirtopiirto::setup() {
    startColor = ofColor(0, 0, 0);
    aimColor = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
    currentColor = startColor;
    showData = true;
    startThread(true);
    kello.reset();
}

void piirtopiirto::update() {
    /*
    
       Viiva::update();
       // pLine.simplify(0.9);
       if (moodi == viivaValmis)
           polyViiva.clear();

       lampo = (mouse.mouseState.x / ofGetWidth() - 0.5) * 40;


       while (pLine.size() - 2 > polyViiva.size() && pLine.size() > 3) {
           // pisteet:  A   B   C
           // viivat:   AB  BC

           polyViiva.push_back(poly());

           ofPoint aiempiPiste = pLine[polyViiva.size() - 1];
           ofPoint piste = pLine[polyViiva.size()];

           if (polyViiva.size() == 1) {


               ofPoint fromToVec = pLine[0] - pLine[1];

               float angle = atan((pLine[0].y - pLine[1].y) / (pLine[0].x - pLine[1].x));
               ofPoint ul = pLine[0] + fromToVec.getRotated(angle + 90, ofVec3f(0, 0, 1));
               ofPoint dl = pLine[0] + fromToVec.getRotated(angle - 90, ofVec3f(0, 0, 1));
               ofPoint ur = ul + fromToVec;
               ofPoint dr = dl + fromToVec;
               ur = pLine[0] + ur.getNormalized();
               dr = pLine[0] + dr.getNormalized();

               polyViiva.back().ul = ul;
               polyViiva.back().dl = dl;
               polyViiva.back().ur = ur;
               polyViiva.back().dr = dr;
               polyViiva.back().color = currentColor;

               if (fromToVec.length() > 0.5)
                   polyViiva.back().draw = true;

           } else {
               int i = polyViiva.size();
               ofPoint fromToVec = pLine[i - 1] - pLine[i];
               ofPoint lastLine = pLine[i - 2] - pLine[i - 1];

               paksuus = otannanOminaisuudet.nopeudenKa * 0.4;

               paksuus = bound(paksuus, 1, 100);

               float angle = atan((pLine[i - 1].y - pLine[i].y) / (pLine[i - 1].x - pLine[i].x));

               ofPoint ur = fromToVec.getRotated(angle + 90, ofVec3f(0, 0, 1));
               ofPoint dr = fromToVec.getRotated(angle - 90, ofVec3f(0, 0, 1));

               ur = fromToVec + ur;
               dr = fromToVec + dr;

               ur = pLine[i - 1] + ur.getNormalized() * paksuus;
               dr = pLine[i - 1] + dr.getNormalized() * paksuus;

               polyViiva.back().ul = polyViiva[i - 2].ur;
               polyViiva.back().dl = polyViiva[i - 2].dr;
               polyViiva.back().ur = ur;
               polyViiva.back().dr = dr;
               polyViiva.back().color = currentColor;

               //if (fromToVec.length() > 0.5)
               //if(mouse.click || alaPiirraSeuraavaa)
               //    polyViiva.back().draw = false;
               //else
               polyViiva.back().draw = true;
           }

       }
       tarkistaVari();
       vaihdaVari();
       alaPiirraSeuraavaa = mouse.click;
       mouse.click = false;
     */
}

void piirtopiirto::draw() {
    //variPiirto::draw();

    ofEnableAntiAliasing();
    ofSetColor(ofColor::black);
    ofBackground(currentColor);
    //pLine.draw();
    lock();
    if (!mouse.mouseState.z) {
        for (int i = 0; i < polyViiva.size(); i++) {
            if (polyViiva[i].draw) {
                ofSetColor(polyViiva[i].color);
                ofSetPolyMode(OF_POLY_WINDING_ODD);
                ofBeginShape();

                ofVertex(polyViiva[i].ul);
                ofVertex(polyViiva[i].ur);
                ofVertex(polyViiva[i].dr);
                ofVertex(polyViiva[i].dl);

                ofEndShape(true);

            }
        }
    }
    if (showData) {
        ofSetColor(255, 255, 255);
        ofDrawBitmapString(ofToString((int) aimColor.getHue()) + ',' + ofToString((int) aimColor.getSaturation()) + ',' + ofToString((int) aimColor.getBrightness()), 20, 20);
        ofDrawBitmapString(ofToString(paksuus), 20, 40);
    }
    unlock();

}

void piirtopiirto::pressed(int x, int y) {
    mouse.pressed(x, y);
    currentHue = currentColor.getHue();

    //polyViiva.clear();
}

void piirtopiirto::vaihdaVari() {

    currentColor.lerp(aimColor, speed * 0.1);
    //currentColor+= suunta * speed;

}

void piirtopiirto::tarkistaVari() {

    // jos nappi ei ole pohjassa
    if (moodi == viivaValmis) {
        currentHue += 1;
        while (currentHue > 255)
            currentHue -= 255;
        aimX = currentHue;
        //tarkastetaan ollaanko vielä oikeassa suunnassa

        aimZ = bound(aimZ + 2, 0, 255);
        aimY = bound(aimY + 2, 0, 255);

        currentColor.setHsb(aimX, aimY, aimZ);
        aimColor.setHsb(aimX, aimY, aimZ);

    } else if (moodi == viivaKesken) {
        aimColor.setHsb(aimX, 0, 255);
        speed = 0.3;
    } else if (moodi == uusiViiva && mouse.click) {
        aimColor = currentColor;
        startColor = currentColor;

    } else if (pLine.size() > 2 && moodi != uusiViiva) {

        float startSat = startColor.getSaturation();
        float kerroin = (startSat + 1) / kalibrointi.nopeudenKa;
        float paKerroin = kalibrointi.pintaala / otannanOminaisuudet.pintaala;

        speed = 1.0;
        aimX = currentHue;
        float pohja = otannanOminaisuudet.nopeudenKa * kerroin * 8;
        
        aimY = otannanOminaisuudet.nopeudenKa * kerroin;
        float yli = bound(aimY-500,0,150)/400;
        aimY = bound(aimY, 0, 255);
        
        ofColor yliColor;
        yliColor.setHsb(61,137,255);
        
        pohja = bound(pohja, 0, 127);
        //aimZ = 255 - ofMap(mouse.mouseState.y, 0 , ofGetHeight(),0,255);
        aimZ = (pohja + aimY / 2);
        

        ofVec3f vec = pLine[pLine.size() - 1] - pLine.getBoundingBox().getCenter();


        //aimZ = bound(127 + (-cos(ofVec3f(0, 1).angleRad(pLine[pLine.size() - 1] - pLine[0])) *vec.lengthSquared()*0.0001),0,255);


        //aimZ += bound(-cos(ofVec3f(0, 1).angleRad(pLine[pLine.size() - 1] - pLine[0])), -10, 10);

        aimColor.setHsb(aimX, aimY, aimZ);
        
        aimColor.r = bound(aimColor.r - lampo, 0, 255);
        aimColor.b = bound(aimColor.b + lampo, 0, 255);
        aimColor.lerp(yliColor,yli);
        //std::cout << "aimColor: " << ofToString(aimColor) << "\n";
    }
    //suunta = aimColor - currentColor;
    //suunta.normalize();

}
