#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "page_replacement.h"

using namespace std;

// Function to read test file
bool readTestFile(string filename, int &frames, vector<int> &refString) {
    ifstream file(filename);
    
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return false;
    }
    
    string line;
    
    // Read frames line
    getline(file, line);
    size_t colonPos = line.find(':');
    frames = stoi(line.substr(colonPos + 1));
    
    // Read reference string line
    getline(file, line);
    colonPos = line.find(':');
    string refStr = line.substr(colonPos + 1);
    
    // Parse the reference string (space-separated numbers)
    stringstream ss(refStr);
    int pageNum;
    while (ss >> pageNum) {
        refString.push_back(pageNum);
    }
    
    file.close();
    return true;
}

// FIFO class definition
class FIFO : public PageReplacement {
private:
    int nextFrameToReplace;

public:
    FIFO(int numFrames) : PageReplacement(numFrames, "FIFO") {
        nextFrameToReplace = 0;
    }
    
    int replacePage(int pageNumber) override {
        int emptyFrame = findEmptyFrame();
        
        if (emptyFrame != -1) {
            frames[emptyFrame] = pageNumber;
            return emptyFrame;
        }
        
        int frameToReplace = nextFrameToReplace;
        frames[frameToReplace] = pageNumber;
        nextFrameToReplace = (nextFrameToReplace + 1) % numberOfFrames;
        
        return frameToReplace;
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: ./page_replacement <test_file>" << endl;
        return 1;
    }
    
    int numFrames;
    vector<int> referenceString;
    
    // Read test file
    if (!readTestFile(argv[1], numFrames, referenceString)) {
        return 1;
    }
    
    cout << "========================================" << endl;
    cout << "Page Replacement Simulation" << endl;
    cout << "Test File: " << argv[1] << endl;
    cout << "Frames: " << numFrames << endl;
    cout << "Reference String Length: " << referenceString.size() << endl;
    cout << "========================================" << endl;
    
    // Test FIFO algorithm
    FIFO fifo(numFrames);
    fifo.setReferenceString(referenceString);
    fifo.simulate();
    fifo.displayResults();
    
    return 0;
}