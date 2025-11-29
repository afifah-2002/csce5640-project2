#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <fstream>
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
    
    int replacePage(int pageNumber, int currentIndex) override {
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

// Optimal class definition
class Optimal : public PageReplacement {
public:
    Optimal(int numFrames) : PageReplacement(numFrames, "Optimal") {
    }
    
    // Find when this page will be used next (return -1 if never used again)
    int findNextUse(int pageNumber, int startIndex) {
        for (size_t i = startIndex; i < referenceString.size(); i++) {
            if (referenceString[i] == pageNumber) {
                return i;
            }
        }
        return -1;  // Never used again
    }
    
    int replacePage(int pageNumber, int currentIndex) override {
        int emptyFrame = findEmptyFrame();
        
        if (emptyFrame != -1) {
            frames[emptyFrame] = pageNumber;
            return emptyFrame;
        }
        
        // No empty frame - find page to replace using optimal strategy
        int farthestUse = -1;
        int frameToReplace = 0;
        
        for (int i = 0; i < numberOfFrames; i++) {
            int nextUse = findNextUse(frames[i], currentIndex + 1);
            
            if (nextUse == -1) {
                // This page is never used again - replace it!
                frameToReplace = i;
                break;
            }
            
            if (nextUse > farthestUse) {
                farthestUse = nextUse;
                frameToReplace = i;
            }
        }
        
        frames[frameToReplace] = pageNumber;
        return frameToReplace;
    }
};
// LRU class definition
class LRU : public PageReplacement {
private:
    vector<int> lastUsedTime;  // Track when each frame was last used

public:
    LRU(int numFrames) : PageReplacement(numFrames, "LRU") {
        lastUsedTime.resize(numFrames, -1);
    }
    
    int replacePage(int pageNumber, int currentIndex) override {
        int emptyFrame = findEmptyFrame();
        
        if (emptyFrame != -1) {
            frames[emptyFrame] = pageNumber;
            lastUsedTime[emptyFrame] = currentIndex;
            return emptyFrame;
        }
        
        // No empty frame - find least recently used page
        int lruIndex = 0;
        int oldestTime = lastUsedTime[0];
        
        for (int i = 1; i < numberOfFrames; i++) {
            if (lastUsedTime[i] < oldestTime) {
                oldestTime = lastUsedTime[i];
                lruIndex = i;
            }
        }
        
        // Replace the LRU page
        frames[lruIndex] = pageNumber;
        lastUsedTime[lruIndex] = currentIndex;
        
        return lruIndex;
    }
    
    void onPageHit(int pageNumber, int currentIndex) override {
        // Update the last used time for this page
        for (int i = 0; i < numberOfFrames; i++) {
            if (frames[i] == pageNumber) {
                lastUsedTime[i] = currentIndex;
                break;
            }
        }
    }
};

// LFU class definition
class LFU : public PageReplacement {
private:
    vector<int> frequency;  // Track frequency count for each frame

public:
    LFU(int numFrames) : PageReplacement(numFrames, "LFU") {
        frequency.resize(numFrames, 0);
    }
    
    int replacePage(int pageNumber, int currentIndex) override {
        int emptyFrame = findEmptyFrame();
        
        if (emptyFrame != -1) {
            frames[emptyFrame] = pageNumber;
            frequency[emptyFrame] = 1;
            return emptyFrame;
        }
        
        // No empty frame - find least frequently used page
        int lfuIndex = 0;
        int minFreq = frequency[0];
        
        for (int i = 1; i < numberOfFrames; i++) {
            if (frequency[i] < minFreq) {
                minFreq = frequency[i];
                lfuIndex = i;
            }
        }
        
        // Replace the LFU page
        frames[lfuIndex] = pageNumber;
        frequency[lfuIndex] = 1;
        
        return lfuIndex;
    }
    
    void onPageHit(int pageNumber, int currentIndex) override {
        // Increase frequency for this page
        for (int i = 0; i < numberOfFrames; i++) {
            if (frames[i] == pageNumber) {
                frequency[i]++;
                break;
            }
        }
    }
};
// MFU class definition
class MFU : public PageReplacement {
private:
    vector<int> frequency;  // Track frequency count for each frame

public:
    MFU(int numFrames) : PageReplacement(numFrames, "MFU") {
        frequency.resize(numFrames, 0);
    }
    
    int replacePage(int pageNumber, int currentIndex) override {
        int emptyFrame = findEmptyFrame();
        
        if (emptyFrame != -1) {
            frames[emptyFrame] = pageNumber;
            frequency[emptyFrame] = 1;
            return emptyFrame;
        }
        
        // No empty frame - find MOST frequently used page
        int mfuIndex = 0;
        int maxFreq = frequency[0];
        
        for (int i = 1; i < numberOfFrames; i++) {
            if (frequency[i] > maxFreq) {
                maxFreq = frequency[i];
                mfuIndex = i;
            }
        }
        
        // Replace the MFU page
        frames[mfuIndex] = pageNumber;
        frequency[mfuIndex] = 1;
        
        return mfuIndex;
    }
    
    void onPageHit(int pageNumber, int currentIndex) override {
        // Increase frequency for this page
        for (int i = 0; i < numberOfFrames; i++) {
            if (frames[i] == pageNumber) {
                frequency[i]++;
                break;
            }
        }
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
    fifo.saveResults("results/all_results.csv", argv[1]);

    // Test Optimal algorithm
    Optimal optimal(numFrames);
    optimal.setReferenceString(referenceString);
    optimal.simulate();
    optimal.displayResults();
    optimal.saveResults("results/all_results.csv", argv[1]);

    // Test LRU algorithm
    LRU lru(numFrames);
    lru.setReferenceString(referenceString);
    lru.simulate();
    lru.displayResults();
    lru.saveResults("results/all_results.csv", argv[1]);
    
    // Test LFU algorithm
    LFU lfu(numFrames);
    lfu.setReferenceString(referenceString);
    lfu.simulate();
    lfu.displayResults();
    lfu.saveResults("results/all_results.csv", argv[1]);
   

    // Test MFU algorithm
    MFU mfu(numFrames);
    mfu.setReferenceString(referenceString);
    mfu.simulate();
    mfu.displayResults();
    mfu.saveResults("results/all_results.csv", argv[1]);

    return 0;
}