#include "ofApp.h"
#include "ofxCsv.h"

//--------------------------------------------------------------
void ofApp::setup(){
    font.load("Avenir Next.ttc", 40);
    // Open a system file selector dialog to choose the CSV file
    ofFileDialogResult inFile = ofSystemLoadDialog("select .csv namelist");
    // Check if the user selected a file
    if (inFile.bSuccess) {
        // Load CSV file
        filePath = inFile.getPath();
        if (csv.load(filePath)) {
            // Extract the list from the first column
            for (int i = 0; i < csv.getNumRows(); ++i) {
                string cellValue = csv[i][0]; // Get value from first column
                importedList.push_back(cellValue);
            }
        } else {
            cout << "Error: Unable to load CSV file." << endl;
        }
    } else {
        cout << "No file selected." << endl;
        return;
    }
    
    // Ask the user to input the number of groups
    string inputStr = ofSystemTextBoxDialog("group size", "2");
    numberOfNames = ofToInt(inputStr);
    
    // Ask the user to input the name of the outFile
    outFile = ofSystemTextBoxDialog("output file", "group list");
    size_t found = filePath.find_last_of("/\\");
    string directoryPath = filePath.substr(0, found);
    outFile = directoryPath + "/" + outFile + ".csv";
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    float y = 300;
    for (int i = 0; i < selectedNames.size(); ++i) {
        string text = selectedNames[i];
        int text_width = font.stringWidth(text);
        float x = (ofGetWidth() - text_width) /2;
        font.drawString(text, x, y);
        y += 70;
    }
    
    if(selectedNames.empty()){
        if(!selectionStarted){
            string text = "click to start making groups";
            int text_width = font.stringWidth(text);
            float x = (ofGetWidth() - text_width) /2;
            float y = ofGetHeight() /2;
            font.drawString(text,x, y);
        } else {
            string text = "all groups made";
            int text_width = font.stringWidth(text);
            float x = (ofGetWidth() - text_width) /2;
            float y = ofGetHeight() /2;
            font.drawString(text,x, y);
        }
    }
}

void ofApp::mousePressed(int x, int y, int button){
    generateRandomNames();
}

void ofApp::generateRandomNames(){
    selectedNames.clear(); // Clear previous selections
    
    if (!importedList.empty()) {
        int numToSelect = min(numberOfNames, (int)importedList.size()); // Select minimum of numberOfNames and remaining names
        
        for (int i = 0; i < numToSelect; ++i) {
            // Generate random index
            int randomIndex = ofRandom(importedList.size());
            // Add random name to selectedNames
            selectedNames.push_back(importedList[randomIndex]);
            // Remove selected name from the list
            importedList.erase(importedList.begin() + randomIndex);
        }
    }
    // Save generated combination to file
    saveCombinations();
}

void ofApp::saveCombinations() {
    selectionStarted = true;
    if (!selectedNames.empty()) {
        // Open the file in append mode
        ofstream outputFile(outFile, ios::app);
        
        if (outputFile.is_open()) { // Check if the file is successfully opened
            // Write each name followed by a separator character
            for (int i = 0; i < selectedNames.size(); ++i) {
                outputFile << selectedNames[i] << ";";
            }
            
            // Add an extra newline character after each combination
            outputFile << "\n";
            
            // Close the file
            outputFile.close();
        } else {
            cout << "Error: Unable to open the output file for writing." << endl;
        }
    }
}
