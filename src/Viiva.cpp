#include "Viiva.h"

void Viiva::setup() {
    sample = 0;
    moodi = viivaValmis;
}

void Viiva::update() {
    viivaKasvoi = false;
    valitseMoodi();
    switch (moodi) {
        case uusiViiva:
            tallennaViiva();
            kalibroi();
            laskeOtannanOminaisuudet();
            break;
        case piirtaa:
            tallennaViiva();
            laskeOtannanOminaisuudet();
            //vertaa();
            break;
        case viivaKesken:
            otannanOminaisuudet.nollaa();
            nopeudet.clear();
            break;
        case viivaValmis:
            // tää on vähän hassu ratkaisu
            pLine.clear();
            nopeudet.clear();
            otannanOminaisuudet.nollaa();
            kalibrointi.nollaa();
            verratut.nollaa();
            sample = 0;
            tauko = 0;
            break;
    }
}

void Viiva::valitseMoodi() {
    if (mouse.mouseState.z) {
        if (sample < 200)
            moodi = uusiViiva;
        else
            moodi = piirtaa;

        sample++;
    } else {
        if (moodi == uusiViiva || moodi == piirtaa) {
            moodi = viivaKesken;
            tauko = 0;
        } else if (tauko < 400)
            tauko++;
        else
            moodi = viivaValmis;
    }
}

void Viiva::kalibroi() {

    kalibrointi.nollaa();

    if (sample > 1) {


        for (int i = 0; i < nopeudet.size(); i++) {
            kalibrointi.nopeudenKa += nopeudet[i];
            kalibrointi.nopeudenKh += pow(nopeudet[i] - kalibrointi.nopeudenKa, 2);
            if (kalibrointi.maksimiNopeus < nopeudet[i])
                kalibrointi.maksimiNopeus = nopeudet[i];
        }
        kalibrointi.nopeudenKa /= nopeudet.size();

        kalibrointi.nopeudenKh = sqrt(1 / pLine.size() * kalibrointi.nopeudenKh);

        ofPolyline line;
        line.addVertices(otanta);
        kalibrointi.pintaala = line.getArea();
        /*TODO: kulman laskut*/
        /*
        for (int i = 1; i < pLine.size(); i++) {
            kalibrointi.kulmanKa += pLine.getAngleAtIndex(i) - pLine.getAngleAtIndex(i);
        }

        kalibrointi.kulmanKa /= pLine.size();
         */
    }
}

void Viiva::tallennaViiva() {
    viivaKasvoi = true;
    pLine.addVertex(mouse.mouseState.x, mouse.mouseState.y);
    otanta.push_back(mouse.mouseState);

    if (otanta.size() == 51)
        otanta.erase(otanta.begin());

    if (pLine.size() == 1 || nopeudet.size() < 2) {
        nopeudet.push_back(0);
    } else if(nopeudet.size() >= 2 ){
        ofVec2f vec = pLine[pLine.size() - 1] - pLine[pLine.size() - 2];
        nopeudet.push_back(vec.lengthSquared());
        if (nopeudet.size() == 51)
            nopeudet.erase(nopeudet.begin());
    }
}

void Viiva::vertaa() {
    verratut.nollaa();
    verratut.nopeudenKa = otannanOminaisuudet.nopeudenKa - kalibrointi.nopeudenKa;
    verratut.nopeudenKh = otannanOminaisuudet.nopeudenKh - kalibrointi.nopeudenKh;
    verratut.kulmanKa = otannanOminaisuudet.kulmanKa - kalibrointi.kulmanKa;
    verratut.kulmanKh = otannanOminaisuudet.kulmanKh - kalibrointi.kulmanKh;
    verratut.maksimiNopeus = otannanOminaisuudet.maksimiNopeus - kalibrointi.maksimiNopeus;
}

void Viiva::laskeOtannanOminaisuudet() {
    otannanOminaisuudet.nollaa();

    if (sample > 1) {

        for (float nopeus : nopeudet)
            otannanOminaisuudet.nopeudenKa += nopeus;

        if (nopeudet.size() != 0)
            otannanOminaisuudet.nopeudenKa /= nopeudet.size();
        otannanOminaisuudet.maksimiNopeus = 0;

        for (int i = 0; i < nopeudet.size(); i++) {
            otannanOminaisuudet.nopeudenKh += pow(nopeudet[i] - otannanOminaisuudet.nopeudenKa, 2);
            if (otannanOminaisuudet.maksimiNopeus < nopeudet[i])
                otannanOminaisuudet.maksimiNopeus = nopeudet[i];
        }
        otannanOminaisuudet.nopeudenKh = sqrt(1 / pLine.size() * otannanOminaisuudet.nopeudenKh);

        ofPolyline line;
        line.addVertices(otanta);
        otannanOminaisuudet.pintaala = line.getArea();


        /*TODO: kulman laskut*/
        /*
        for (int i = 1; i < pLine.size(); i++) {
            otannanOminaisuudet.kulmanKa += pLine.getAngleAtIndex(i) - pLine.getAngleAtIndex(i);
        }

        kalibrointi.kulmanKa /= pLine.size();
         */
    }


}