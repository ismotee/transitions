#include "ofApp.h"

//--------------------------------------------------------------

void ofApp::setup() {
    ofBackground(ofColor::white);
    col = ofColor::white;
    ofHideCursor();
    piirtopiirto::setup();
}

//--------------------------------------------------------------

void ofApp::update() {

    piirtopiirto::update();

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
    mouse.moved(x, y);
}

//--------------------------------------------------------------

void ofApp::mouseDragged(int x, int y, int button) {
    //mousePos.set(x, y);
    mouse.moved(x, y);

}

//--------------------------------------------------------------

void ofApp::mousePressed(int x, int y, int button) {
    //mousePos.set(x, y);
    //mPressed = true;
    //pLine.clear();
    piirtopiirto::pressed(x, y);
}

//--------------------------------------------------------------

void ofApp::mouseReleased(int x, int y, int button) {
    //mousePos.set(x, y);
    //mPressed = false;

    //pLine.simplify(0.8);
    mouse.released(x, y);


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