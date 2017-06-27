#include "ofApp.h"

//--------------------------------------------------------------

void ofApp::setup() {
    ofBackground(ofColor::white);
    ofHideCursor();
    Viiva::setup();
    piirtopiirto::setup();
    sender.setup("127.0.0.1", 9998);
    clk.reset();
}

//--------------------------------------------------------------

void ofApp::update() {

    // piirtopiirto::update();
    if (mouse.mouseState.z && clk.get() > 0.1) {
        lock();
        ofxOscMessage msg;
        msg.setAddress("/nopeus");
        msg.addFloatArg(ylitys);
        sender.sendMessage(msg, false);
        unlock();
        clk.reset();
    }
}
//--------------------------------------------------------------

void ofApp::draw() {
    piirtopiirto::draw();

}

//--------------------------------------------------------------

void ofApp::keyPressed(int key) {
    if (key == ' ')
        showData = !showData;
}

//--------------------------------------------------------------

void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------

void ofApp::mouseMoved(int x, int y) {
    lock();
    mouse.moved(x, y);
    unlock();
}

//--------------------------------------------------------------

void ofApp::mouseDragged(int x, int y, int button) {
    //mousePos.set(x, y);
    lock();
    mouse.click = false;
    mouse.moved(x, y);
    unlock();
}

//--------------------------------------------------------------

void ofApp::mousePressed(int x, int y, int button) {
    //mousePos.set(x, y);
    //mPressed = true;
    //pLine.clear();
    lock();
    mouse.click = true;
    piirtopiirto::pressed(x, y);
    unlock();
}

//--------------------------------------------------------------

void ofApp::mouseReleased(int x, int y, int button) {
    //mousePos.set(x, y);
    //mPressed = false;

    //pLine.simplify(0.8);
    lock();
    mouse.released(x, y);
    unlock();

}

//--------------------------------------------------------------

void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------

void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------

void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------

void ofApp::gotMessage(ofMessage msg) {
}

//--------------------------------------------------------------

void ofApp::dragEvent(ofDragInfo dragInfo) {

}