#pragma once

#include "ofMain.h"
#include "ofxCsv.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void mousePressed(int x, int y, int button);

    void generateRandomNames();
    void saveCombinations();

private:
    ofTrueTypeFont font;
    ofxCsv csv;
    string filename;
    vector<string> importedList;
    vector<string> selectedNames;
    int numberOfNames; // Variable to store the fixed number of names to select
    string filePath;
    string outFile;
    bool selectionStarted;
};
